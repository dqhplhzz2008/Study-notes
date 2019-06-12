## Linux第六天：进程（上）

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






