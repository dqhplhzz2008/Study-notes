
# Linux第七天：exec、回收子进程和进程间通信

## exec函数族

fork创建子进程后执行的是和父进程相同的程序（但有可能执行不同的代码分支），子进程往往要调用一种exec函数**以执行另一个程序**。当进程调用一种exec函数时，该进程的**用户空间代码和数据完全被新程序替换**，从新程序的启动例程开始执行。调用exec并不创建新进程，所以**调用exec前后该进程的id并未改变**。

将当前进程的.text、.data替换为所要加载的程序的.text、.data，然后让进程从新的.text第一条指令开始执行，但进程ID不变，换核不换壳。

该函数族主要有以下六个：
```
int execl(const char *path, const char *arg, ...);
int execlp(const char *file, const char *arg, ...);
int execle(const char *path, const char *arg, ..., char *const envp[]);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execve(const char *path, char *const argv[], char *const envp[]);
```

**execlp函数**
功能：加载一个进程，借助PATH环境变量。
参数说明：参数1：要加载的程序的名字。
返回值：该函数需要配合PATH环境变量来使用，当PATH中所有目录搜索后没有参数1则出错返回。
该函数通常用来调用系统程序。如：ls、date、cp、cat等命令。
该函数的参数数目是不确定的，file指的是传入的文件的名字（可执行参数的文件名），arg就是main(int argc, char*[] argv)里面的argv[0]、argv[1]，argv[2]...以此类推。注意，以**NULL**结尾。

测试代码：
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	pid = fork();
	if(pid == -1)
	{
		perror("Fork error:");
		exit(1);
	}
	else if(pid > 0)
	{
		sleep(2);
		printf("This is parent process.\n");
	}
	else
	{
		execlp("ls","ls","-l",NULL);
	}
	return 0;
}
```
输出结果：
![f5fe0c296efc4876e7d863ed12c83eb3.png](http://tech.yushuai.xyz/wzpt/linuxstudy/day71.png)

**execl函数**

功能：加载一个进程， 通过 路径+程序名 来加载。与`execlp()`函数相比，区别如下：

- execlp("ls", "ls", "-l", "-F", NULL);        使用程序名在PATH中搜索。
- execl("/bin/ls", "ls", "-l", "-F", NULL);    使用参数1给出的绝对路径搜索。

**execle()函数**：引入了环境变量表进行查询。

**execv()函数**：需要构建一个char* crgv[]数组。

**execvp()函数**：相当于`execv()`函数里面还需要借助PATH。

**execve()函数**：引入环境变量表进行查询。

例题：将当前系统中的进程信息，打印到文件中。

在bash中，我们可以执行这样的语句
```
ps aux > out
```
这样就可以把当前进程信息打印到out文件中去了。但是使用exec编程的话就不能直接使用这个语句。

所以这个时候我们需要使用`dup2()`函数。即我们原来执行`ps aux`之后，系统将结果自动去找文件描述符为1的位置（也就是STDOUT），如果我们使用`dup2()`函数，将文件描述符为1的位置指向out的位置呢，那不就是结果会被输出到文件里面了吗。

所以总的来说我们的流程如下：

1. 打开/新建out文件。若打开失败，则输出错误信息并退出，否则进行下一步。
2. 执行dup2(fd,STDOUT_FILENO);
3. 然后执行execlp程序。
4. 最后无需关闭文件，因为execlp执行完就直接退出这个进程了，隐式回收自动把占用的内存回收。

代码如下：
```
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{
	//打开/创建文件
	int fd=open("cenProcess",O_RDWR | O_CREAT|O_TRUNC,0644);
	if(fd == -1)
	{
		perror("file open error:");
		exit(1);
	}
	//dup2
	dup2(fd,STDOUT_FILENO);
	//执行 execlp
	execlp("ps","ps","aux",NULL);
	//如果没有错误就退出了，如果有错误就执行下面的语句
	perror("Execlp error:");
	exit(1);
	return 0;
}
```

**exec函数族一般规律**

exec函数一旦调用成功即执行**新的程序，不返回**。只有**失败才返回，且返回值为-1**。所以通常我们直接在exec函数调用后直接调用perror()和exit()，无需if判断。

exec后面的字符的意思如下：

|参数  |含义  |
| --- | --- |
| l(list) |命令行参数列表  |
| p(path) | 搜索file的PATH变量 |
| v(vector) | 使用命令行参数组（charv()） |
| e(environment) | 使用环境变量数组,不使用进程原有的环境变量，设置新加载程序运行的环境变量 |

只有execve是真正的系统调用，其它五个函数最终都调用execve，所以execve在man手册第2节，其它函数在man手册第3节。这些函数之间的关系如下图所示。

![60b089d3ac230e60e61d539f1aced2a1.png](http://tech.yushuai.xyz/wzpt/linuxstudy/day72.png)

## 回收子进程

**孤儿进程**：孤儿进程: 父进程先于子进程结束，则子进程成为孤儿进程，子进程的父进程成为init进程，称为**init进程领养孤儿进程**。

**僵尸进程**：进程终止，父进程尚未回收，子进程残留资源（PCB）存放于内核中，变成僵尸（Zombie）进程。如下图所示。

![7ba6cd0ac0dfd51fc73ef51879f0b47f.png](http://tech.yushuai.xyz/wzpt/linuxstudy/day73.png)

kill只能终止进程，但是僵尸进程本身就已经终止了，那应该用怎样的方法来清除僵尸进程呢？
使用`wait()`和`waitpid()`函数。

**wait()函数**
一个进程在终止时会关闭所有文件描述符，释放在用户空间分配的内存，但它的PCB还保留着，内核在其中保存了一些信息：如果是正常终止则保存着退出状态，如果是异常终止则保存着导致该进程终止的信号是哪个。这个进程的父进程可以调用wait或waitpid获取这些信息，然后彻底清除掉这个进程。我们知道一个进程的退出状态可以在Shell中用特殊变量$?查看，因为Shell是它的父进程，当它终止时Shell调用wait或waitpid得到它的退出状态同时彻底清除掉这个进程。
父进程调用wait函数可以回收子进程终止信息。该函数有三个功能：
* 阻塞等待子进程退出（父进程回收，如果子进程没死，那么父进程就在这里等着，父进程不做其他事情。）
* 回收子进程残留资源。 
* 获取子进程结束状态(退出原因)。

函数原型：
```
#include <sys/types.h>
#include <sys/wait.h>

pid_t wiat(int *status);
```
返回值：若成功则返回结束的子进程的PID，若失败则返回-1。

status是一个传出参数，它用来保存进程的退出状态。借助宏函数来进一步判断进程终止的具体原因。宏函数可分为如下三组（前两组重点记住）：
1. WIFEXITED(status) 为非0 → 进程正常结束
WEXITSTATUS(status) 如上宏为真，使用此宏 → 获取进程退出状态 (exit的参数)
2. WIFSIGNALED(status) 为非0 → 进程异常终止
WTERMSIG(status) 如上宏为真，使用此宏 → 取得使进程终止的那个信号的编号。

3. WIFSTOPPED(status) 为非0 → 进程处于暂停状态
WSTOPSIG(status) 如上宏为真，使用此宏 → 取得使进程暂停的那个信号的编号。
WIFCONTINUED(status) 为真 → 进程暂停后已经继续运行

Linux中所有程序的终止都是接收到某个信号才会终止，父进程需要通过信号知道谁杀死了子进程才能进行回收。在接收到status信号的时候，执行以下的步骤：

1. 先执行`WIFEXITED(status)`，判断进程是否是正常结束，若非0，则进程正常结束，然后调用`WEXITSTATUS(status)`来获取进程退出状态。
2. 若为0，则判断` WIFSIGNALED(status) `，若非0，则是异常终止，执行`WTERMSIG(status) `，返回进程暂停的那个信号的编号。

**waitpid()函数**
作用桶wait，但可以指定pid进程清理（第一个参数设置），可以不阻塞（第三个参数设置）。
语法原型：
```
pid_t waitpid(pid_t pid, int *status, in options);
```
若成功，返回清理掉的子进程ID，若失败，则返回-1。
若第三个参数为WNOHANG，且子进程正在进行，那么wiatpid就不会回收子进程，则返回0。

特殊参数和返回情况：

- 参数pid：


| pid |含义  |
| --- | --- |
| >0 |回收指定ID的子进程  |
| -1 |回收指定ID的子进程  |
| 0 | 回收和当前调用waitpid一个组的所有子进程 |
| <-1 | 回收指定进程组的任意子进程 |

参数3：设置为0，则会阻塞；设置为WNOHANG就不会阻塞，去探测子进程是否结束，若结束就回收，否则不回收然后退出（如果想让它回收就得通过轮询方式，轮询方式见下面）；设置为WUNTRACED，若某实现支持作业控制，而由pid指定的任一子进程已处于暂停状态，但是其状态自暂停以后还未报告过，则返回其状态，WIFSTOPPED宏确定返回值是否对应一个暂停子进程；WCONTINUED-若支持作业控制，那么由pid指定的任一子进程在暂停后已经继续，但其状态未被报告，则返回其状态。 

注意：一次wait或waitpid调用**只能清理一个子进程**，清理多个子进程应使用循环。

轮询方式实现非阻塞进程回收：
```
pid_t wpid;
int flag=5;//回收5个进程
do{
	wpid = waitpid(-1,NULL,WNOHANG);
    if(wpid > 0)
        n--;
	//如果wpid==0说明子进程正在运行，前提是第三个参数设置为WNOHANG
	sleep(1);//为了不让这个轮询速度太快，所以加了个休眠时间
}while(n > 0);
```

## 进程间通信

### 前言部分

Linux环境下，进程地址空间相互独立，每个进程各自有不同的用户地址空间。任何一个进程的全局变量在另一个进程中都看不到，所以进程和进程之间不能相互访问，要交换数据必须通过内核，在内核中开辟一块缓冲区，进程1把数据从用户空间拷到内核缓冲区，进程2再从内核缓冲区把数据读走，内核提供的这种机制称为进程间通信（IPC，Inter Process Communication）。如下图所示：

![9bdfd540bfb59ebda038a101fd255f61.png](http://tech.yushuai.xyz/wzpt/linuxstudy/day74.png)

在进程间完成数据传递需要借助操作系统提供特殊的方法，如：文件、管道、信号、共享内存、消息队列、套接字、命名管道等。随着计算机的蓬勃发展，一些方法由于自身设计缺陷被淘汰或者弃用。现今常用的进程间通信方式有：

- 管道（使用最简单）。掌握`pipe()`函数，管道一般读写行为。
- 信号（开销最小）。`fifo()`（有名管道）用于非血缘关系进程间通信。
- 共享映射区（无血缘关系也可以传递）。共享内存：`mmap()`函数，父子之间或者非血缘关系进程之间通信，要注意函数参数使用注意事项，与管道相比，它可以反复读取。
- 本地套接字（最稳定，但时间复杂度最高、难度最大）。

假如我有两个程序（a.out和b.out）它们想要实现信息的传递，我们原来的方法可以是由于a.out和b.out共享一个打开的文件结构体，我可以在a.out打开一个文件，a.out有一个指向文件的文件描述符，然后把数据写入文件，然后b.out也打开这个文件，b.out就可以从这个文件读数据。a.out和b.out的4G进程空间是独立的。

![0a5e5ca6a28171c42e227dcfef3d5d3a.png](http://tech.yushuai.xyz/wzpt/linuxstudy/day75.png)

它们的内核区虽然在虚拟内存区域不同，但是在物理内存上是同一块内存区域，所以我们可以通过一个管道实现信息的流出流入，实现一个**单向的流入流出**。

![d99eb7563466c8ea19f13d78b0b6d9ef.png](http://tech.yushuai.xyz/wzpt/linuxstudy/day76.png)

回顾下Linux里面的文件类型


|符号 |类型 |是否占用存储空间|
| --- | --- | ---|
| - |普通文件  |√|
| d | 目录 |√|
|l  | 符号链接（软连接） |√|
|s  | 套接字 |×|
| b |块设备  |×|
| c | 字符设备 |×|
| p |管道  |×|

其中后面这四种（套接字、管道、字符设备、块设备）被称为**伪文件**，不占用存储空间。


### 管道

管道是一种最基本的IPC机制，作用于**有血缘关系的进程**之间，完成数据传递。调用pipe系统函数即可创建一个管道。有如下特质：

1. 其本质是一个伪文件(实为内核缓冲区) 
2. 由两个文件描述符引用，一个表示读端，一个表示写端。
3. 规定数据从管道的写端流入管道，从读端流出。

管道的原理: 管道实为内核使用**环形队列**机制，借助**内核缓冲区**(4k)实现。

由于管道本质上是一个队列，所以它有**先进先出**的性质。由于它是一个队列，所以管道有以下局限性：

- 数据自己读不能自己写。
- 数据一旦被读走，便不在管道中存在，不可反复读取。
- 由于管道采用半双工通信方式。因此，数据只能在一个方向上流动。
- 只能在有公共祖先的进程间使用管道。

### pipe()函数

函数功能：创建管道,，同时将管道两端打开（两个文件描述符打开），并且作为函数参数传出来（pipefd[2]）。
函数原型：
```
#include <unistd.h>
int pipe(int pipefd[2]);      
```
返回值：若执行成功则返回0，失败返回-1，错误记录在`errno`里面。

函数调用成功返回r/w两个文件描述符。无需open，但需手动close。规定：fd[0]为读端； fd[1]为写端，就像0对应标准输入，1对应标准输出一样。向管道文件读写数据其实是在读写内核缓冲区。

我们写一个例程，如下面代码所示。在这个例程，我们发现在`fork()`之前我们就执行了`pipe()`函数，也就是说我们的`a.out`掌握了读入和写出的两个文件描述符。

在`pipe()`函数之后，我们调用了一次`fork()`，创建出来了一个子进程，子进程也掌握着管道的两端（写入端、读出端）。形成了如下图所示的情况，我们发现对于同一个进程，它既可以读出来也可以写进去，并不是单向的。所以为了能够单向流动，我们需要规定除谁读谁写。

![02dd30b58f6d4c1300407de98e6a3ec1.png](http://tech.yushuai.xyz/wzpt/linuxstudy/day77.png)

我们可以指定子进程读（需要将写端关闭掉），父进程写（需要将读端关闭掉）。由于人为规定（不是我规定的）了fd[0]为读端，fd[1]为写端，所以讲子进程的fd[1]close掉，将父进程的fd[0]close掉。

```
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
	int pipefd[2];
	pid_t pid;

	int ret = pipe(pipefd);
	if(ret == -1){
		perror("pipe error:");
		exit(1);
	}

	pid = fork();
	if(pid == -1)
	{
		perror("Fork error:");
		exit(1);
	}
	//子，假设为读数据
	else if(pid ==0)
	{
		close(pipefd[1]);
		char* buff[1024];
		ret = read(pipefd[0],buff,sizeof(buff));//从pipefd[0]也就三管道里面读取数据到buffer
		if(ret == 0)
			printf("-------\n");
		write(STDOUT_FILENO,buff,ret);

	}
	else
	{
	close(pipefd[0]);
	char *str="This is your time.\n";
	write(pipefd[1],"This is your time.\n",strlen("This is your time.\n"));
	}

	return 0;
}
```
### 管道的读写行为

使用管道需要注意以下4种特殊情况（假设都是阻塞I/O操作，没有设置O_NONBLOCK标志）：

1. 如果所有指向管道写端的文件描述符都关闭了（管道写端引用计数为0），而仍然有进程从管道的读端读数据，那么管道中剩余的数据都被读取后，再次read会返回0，就像读到文件末尾一样。
2. 如果有指向管道写端的文件描述符没关闭（管道写端引用计数大于0），而持有管道写端的进程也没有向管道中写数据，这时有进程从管道读端读数据，那么管道中剩余的数据都被读取后，再次read会阻塞，直到管道中有数据可读了才读取数据并返回。
3. 如果所有指向管道读端的文件描述符都关闭了（管道读端引用计数为0），这时有进程向管道的写端write，那么该进程会收到信号SIGPIPE，通常会导致进程异常终止。当然也可以对SIGPIPE信号实施捕捉，不终止进程。具体方法信号章节详细介绍。
4. 如果有指向管道读端的文件描述符没关闭（管道读端引用计数大于0），而持有管道读端的进程也没有从管道中读数据，这时有进程向管道写端写数据，那么在管道被写满时再次write会阻塞，直到管道中有空位置了才写入数据并返回。

总结：

① 读管道：

- 管道中有数据，read返回实际读到的字节数。
- 管道中无数据：
(1) 管道写端被全部关闭，read返回0 (好像读到文件结尾)
(2) 写端没有全部被关闭，read阻塞等待(不久的将来可能有数据递达，此时会让出cpu)

② 写管道：    
- 管道读端全部被关闭， 进程异常终止(也可使用捕捉SIGPIPE信号，使进程不终止)
- 管道读端没有全部关闭： 
(1) 管道已满，write阻塞。
 (2) 管道未满，write将数据写入，并返回实际写入的字节数。


### 管道缓冲区的大小

可以使用ulimit –a 命令来查看当前系统中创建管道文件所对应的内核缓冲区大小。通常为：
`pipe size            (512 bytes, -p) 8`

也可以使用fpathconf函数，借助参数 选项来查看。使用该宏应引入头文件<unistd.h>
```
long fpathconf(int fd, int name);    
```
  
成功：返回管道的大小         失败：-1，设置errno

### 管道的优缺点

优点：简单，相比信号，套接字实现进程间通信，简单很多。

缺点：
* 只能单向通信，双向通信需建立两个管道。
* 只能用于父子、兄弟进程(有共同祖先)间通信。该问题后来使用fifo有名管道解决。

## FIFO

FIFO常被称为命名管道，以区分管道(pipe)。管道(pipe)只能用于“有血缘关系”的进程间。但通过FIFO，不相关的进程也能交换数据。

FIFO是Linux基础文件类型中的一种。但，FIFO文件在磁盘上没有数据块，仅仅用来标识内核中一条通道。各进程可以打开这个文件进行read/write，实际上是在读写内核通道，这样就实现了进程间通信。

创建方式：

- 命令： mkfifo <管道名>
- 库函数：

```
int mkfifo(const char *pathname, mode_t mode);
```
成功：0；失败：-1

一旦使用mkfifo创建了一个FIFO，就可以使用open打开它，常见的文件I/O函数都可用于fifo。如：close、read、write、unlink等。



