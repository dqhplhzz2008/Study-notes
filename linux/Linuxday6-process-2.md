
## Linux第六天：进程（下）

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