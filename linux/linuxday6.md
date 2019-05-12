## Linux第六天：进程

### 课程知识点框架
本部分课程的知识体系：
1. 进程相关的概念  
    - 并发
    - 单道程序设计
	- 多道程序设计
	- cpu/mmu
	- 进程控制块
    -进程状态

2. 环境变量
	- 常用的环境变量/作用
	- 函数（了解）

3. 进程控制原语
    - fork函数：循环创建子进程的架构。
    - exec函数族：了解各个函数的参数使用方法和作用
    - wait/waitpid：回收子进程的一般方式。

### 程序、进程和并发

程序，是指编译好的二进制文件，在磁盘上，不占用系统资源（cpu、内存、打开的文件、设备、锁......）。

进程，是一个抽象的概念，与操作系统原理联系紧密。进程是活跃的程序，占用系统资源。在内存中执行。(程序运行起来，产生一个进程)

打个比方，程序就相当于一个剧本，而进程就相当于上演的一出戏（包括舞台、演员、灯光等就是系统资源）。剧本可以在多个舞台同时上演，同样，同一个程序也可以加载为不同的进程（彼此之间互不影响）。

所谓并发，在操作系统中，一个时间段中有多个进程都处于已启动运行到运行完毕之间的状态。**但任一个时刻点上仍只有一个进程在运行**。

**单道程序设计**就是所有进程一个一个排对执行。若A阻塞，B只能等待，即使CPU处于空闲状态。

**多道程序设计**就是在计算机内存中同时存放几道相互独立的程序，它们在管理程序控制之下，相互穿插的运行。**总体来看（宏观上）它们是并行执行，从具体某个时间点来看（微观上），是串行的。**

每个程序被分为了多个时间轮片，然后在CPU控制下执行完这个程序的时间轮片，再去执行另一个，然后循环往复，也就是**分时复用**。
多道程序设计必须有硬件基础作为保证。

**时钟中断**即为多道程序设计模型的理论基础。 并发时，任意进程在执行期间都不希望放弃cpu。因此系统需要一种强制让进程让出cpu资源的手段。时钟中断有硬件基础作为保障，对进程而言不可抗拒。 操作系统中的中断处理函数，来负责调度程序执行。

### CPU和MMU

CPU的架构（具体参加计算机组成原理课程内容，在这里不做笔记）：

![](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/linuxclasses/day6/linuxday6cpu.png)

MMU（内存管理单元）位于CPU内，图如下：

![](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/linuxclasses/day6/linuxday6mmu.png)

功能主要是：

- 实现虚拟内存和物理内存的映射。
- 设置修改内存访问级别。虚拟内存中分为用户区（0~3G）和内核区（3G~4G），两个区域的访问权限不一致，MMU可以设置CPU的内存访问级别。

MMU分配内存最小单位是page，是4kb。
在MMU进行映射的时候，对于用户区，不同的进程映射**不同的区域**，但是对于内核区，不同的进程映射**同一块**区域，但是两个进程的PCB是不同的，只是在同一块内存里面。

### 进程控制块（PCB）

进程控制块（PCB）也被称为进程描述符。每个进程在内核中都有一个进程控制块（PCB）来维护进程相关的信息，Linux内核的进程控制块是**task_struct结构体**。

这个结构体内部成员有很多，可以重点掌握以下部分：

* 进程id。系统中每个进程有唯一的id，在C语言中用`pid_t`类型表示，其实就是一个**非负整数**。
* 进程的状态，有**就绪**、**运行**、**挂起**、**停止**等状态。
* 进程切换时需要保存和恢复的一些CPU寄存器。
* 描述虚拟地址空间的信息。MMU维护，存储在PCB里面。
* 描述控制终端的信息。
* 当前工作目录（Current Working Directory）。
* umask掩码。
* 文件描述符表，包含很多指向file结构体的指针。
* 和信号相关的信息。
* 用户id和组id。
* 会话（Session）和进程组。
* 进程可以使用的资源上限（Resource Limit）。可以使用`ulimit -a`来查看当前使用系统资源的上线。

进程基本的状态有5种。分别为初始态（进程准备），就绪态（准备结束，等待CPU分配时间片），运行态（占用CPU运行），挂起态（等待除CPU以外的其它资源，主动放弃CPU）与终止态。其中初始态为进程准备阶段，常与就绪态结合来看。

![](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/linuxclasses/day6/linuxday6processstatus.png)


### 环境变量

环境变量，是指在操作系统中用来指定操作系统运行环境的一些参数。通常具备以下特征：
① 字符串(本质) ② 有统一的格式：名=值[:值] ③ 值用来描述进程环境信息。
存储形式：与命令行参数类似。char *[]数组，数组名environ，内部存储字符串，NULL作为哨兵结尾。

使用形式：与命令行参数类似。

加载位置：与命令行参数类似。位于用户区，高于stack的起始位置。

引入环境变量表：须声明环境变量。extern char ** environ;            

编写程序，实现输出环境变量的程序。

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main(void)
{
    int i;
    for (i = 0; environ[i] != NULL; i++)
        printf("%s\n", environ[i]);
    return 0;
}
```

常用的环境变量：

- PATH：可执行文件的搜索路径。ls命令也是一个程序，执行它不需要提供完整的路径名/bin/ls，然而通常我们执行当前目录下的程序a.out却需要提供完整的路径名./a.out，这是因为PATH环境变量的值里面包含了ls命令所在的目录/bin，却不包含a.out所在的目录。PATH环境变量的值可以包含多个目录，用:号隔开。在Shell中用echo命令可以查看这个环境变量的值

- SHELL：当前Shell，它的值通常是/bin/bash。

- TERM：当前终端类型，在图形界面终端下它的值通常是xterm，终端类型决定了一些程序的输出显示方式，比如图形界面终端可以显示汉字，而字符终端一般不行。

- LANG：语言和locale，决定了字符编码以及世界、货币等信息的显示格式。

- HOME：当前用户主目录的路径。


常用的环境变量函数：

- getenv函数：获取环境变量值

函数原型：
```
char *getenv(const char *name);   
```

函数返回值：
成功：返回环境变量的值；失败：NULL (name不存在)


- setenv函数：设置环境变量

函数原型：
```
int setenv(const char *name, const char *value, int overwrite);
```
参数overwrite取值：1位覆盖原有环境变量；0为不覆盖（改参数常用于设置新的环境变量）。

函数返回值：
成功：返回0；失败：返回-1。


- unsetenv函数：删除环境变量name的定义

函数原型：
```
int unsetenv(const char *name);
```
注意事项：name不存在仍返回0(成功)，当name命名为"ABC="时则会出错。

函数返回值：
成功：返回0；失败：返回-1。

测试代码如下：
```
#include <stdio.h>
#include <stdlib.h>
int main()
{
	char *val;
	const char *name="ABCD";

	val = getenv(name);
	printf("1,%s = %s\n", name ,val);

	setenv(name,"I-love-you",1);

	printf("setenv()以后的结果\n");

	val = getenv(name);
	printf("2, %s = %s\n",name,val);
#if 0
	int ret = unsetenv("ABCDEFG");
	printf("ret = %d\n", ret);

	val = getenv(name);
	printf("3, %s = %s\n",name,val);
#else
	int ret = unsetenv("ABCD");
	printf("ret = %d\n",ret);

	val = getenv(name);
	printf("3, %s = %s\n",name, val);
#endif

	return 0;
}
```

### 进程控制

**fork函数**

作用：创建一个子进程。

原型：
```
#include <unistd.h>
pid_t fork(void);
```
描述：
成功返回两个值：
- 父进程返回子进程的ID(非负)  
- 子进程返回 0 

返回值-1表示出错。

pid_t类型表示进程ID，但为了表示-1，它是有符号整型。(0不是有效进程ID，init最小，为1)

实际上，不是fork函数能返回两个值，而是fork后，fork函数变为两个，父子需**各自**返回一个。如下图所示。

![](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/linuxclasses/day6/linuxday6fork.png)



创建的一个子进程，从fork()函数后开始执行，而不是从头开始执行。

**示例1：创建一个子进程**
测试代码：
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("xxxxxxxx\n");
	pid_t pid;
	pid = fork();
	if(pid == -1)
	{
		perror("Fork Error:");
		exit(1);
	}
	else if(pid == 0)
	{
		printf("This is child process. My pid = %u\n",getpid());
		printf("And my parent process is %u\n", getppid());
	}

	else
	{
		printf("This is parent process, and pid is %u\n",getpid());
		printf("My parent process is %u\n",getppid());
		sleep(1);
	}
	printf("This is the end of this process.\n");
	return 0;
}
```
测试结果：

![](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/linuxclasses/day6/linuxday6forkpresentation.png)


可执行程序的运行结果正如我们前文所述。首先执行fork()前面的语句，只执行一遍，打印出来了`xxxxxxxx`。然后开始打印输出父进程的东西，打印出来了父进程的PID和父进程的父进程的PID，（由于这个时候对父进程执行了休眠1秒钟，所以父进程的`This is the end of this process`被延迟到最后来执行了。）然后打印子进程的信息，输出子进程的`This is the end of this process`。

注意，如果父进程不执行`sleep(1)`的话，父进程的最后那句`This is the end of this process`可能会穿插在子进程输出信息中输出。

父进程的父进程是什么呢？我们执行`ps aux | grep 7921` 就可以看到了7921实际上是bash的进程PID。

**示例2：循环创建3个子进程**

假如我们是这样设计的，那么正确吗？
```
for(int i=0;i<3;i++)
{
    fork();
}
```
实际上，是创建了7个子进程（还有1个父进程）,即(2<sup>n</sup>-1)个子进程，如图所示。

![](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/linuxclasses/day6/linuxday6multifork.png)



修改为：
```
int main(void)
{
    int i;
    pid_t pid;
    printf("xxxxxxxxxxx\n");

    for (i = 0; i < 5; i++) {
        pid = fork();
        if (pid == 0) {
            break;
        }
    }

    if (i < 5) {

        sleep(i);
        printf("I'am %d child , pid = %u\n", i+1, getpid());

    } else  {
        sleep(i);
        printf("I'm parent\n");
    }

    return 0;
}
```

这个程序在进入for循环的含义是：当i=0的时候，执行fork()函数，创建出一个子进程来（将子进程命名为子0），此时子进程返回的pid=0，然后判断符合pid==0，执行break语句，跳出for循环，父进程则因为不符合这个if语句，因而进行下一个循环；当i=1的时候，执行fork()函数，创建出一个子进程来（将子进程命名为子1），此时子进程返回的pid=0，然后判断符合pid==0，执行break语句，跳出for循环，父进程则因为不符合这个if语句，因而进行下一个循环；当i=2的时候，执行fork()函数，创建出一个子进程来（将子进程命名为子2），此时子进程返回的pid=0，然后判断符合pid==0，执行break语句，跳出for循环，父进程则因为不符合这个if语句，因而进行下一个循环......一直到i=4执行完成后退出，后续又产生了子3、子4。

对于子0来说，此时i=0，执行if(i<5)里面的语句，休眠0秒钟，输出子进程0的信息；对于子1来说，休眠1秒钟，输出子进程1的信息，以此类推。对于父进程来说，执行完for循环之后，i=5，因此休眠5秒钟。所以将按照子进程0~4、父进程的顺序显示。

其实父进程和子进程没有优先级，谁都有可能抢到，但是无论谁抢到了，其都需要挂起i秒，所以到最后还是按照我们想要的顺序来输出结果。

但是如果我们去掉挂起i秒这个语句，五个进程和1个父进程是可以看做共同争夺CPU，不会存在父进程因为循环五次而慢于5个子进程的情况。

![](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/linuxclasses/day6/linuxday6multiforkresult1.png)


如上图所示，之所以在输出I'm parent之后就又显示出bash等待命令的界面是因为，bash在执行命令后就会切到后台，但是只要看到父进程的`return 0`后就会自动切换前台，但是它这个时候并不知道还有子进程在运行，所以才会出现它和剩余的子进程进行抢夺CPU资源，结果就是它有可能比所有剩余的子进程优先抢到CPU，得到图中的结果，也有可能某个子进程先抢到，所以会出现下图的样子。

![](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/linuxclasses/day6/linuxday6multiforkresult2.png)


### 父子进程共享

父子进程之间在fork后。有哪些相同，那些相异之处呢？
刚fork之后：
父子相同处: 全局变量、.data、.text、栈、堆、环境变量、用户ID、宿主目录、进程工作目录、信号处理方式...
父子不同处: 
* 进程ID
* fork返回值
* 父进程ID
* 进程运行时间
* 闹钟(定时器)
* 未决信号集

似乎，子进程复制了父进程0-3G用户空间内容，以及父进程的PCB，但pid不同。真的每fork一个子进程都要将父进程的0-3G地址空间完全拷贝一份，然后在映射至物理内存吗？

当然不是!父子进程间遵循**读时共享写时复制**的原则。这样设计，无论子进程执行父进程的逻辑还是执行自己的逻辑都能节省内存开销。   

【重点】：父子进程共享：
* 文件描述符(打开文件的结构体)  
* mmap建立的映射区 (进程间通信详解)

特别的，fork之后父进程先执行还是子进程先执行不确定。取决于内核所使用的调度算法。


### GDB调试

使用gdb调试的时候，gdb只能跟踪一个进程。可以在fork函数调用之前，通过指令设置gdb调试工具跟踪父进程或者是跟踪子进程。默认跟踪父进程。

设置gdb在fork之后跟踪子进程：
```
set follow-fork-mode child
```
设置跟踪父进程：
```
set follow-fork-mode parent 
```
注意，一定要在fork函数调用之前设置才有效。

如果是在多个子线程中跟踪第3个子进程，那么直接在相应的判断语句中设置条件断点即可。




