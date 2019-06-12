
## day7练习1

### 题目说明
使用管道实现父子进程间通信，完成：ls | wc –l。假定父进程实现ls，子进程实现wc


### 题目解析
题目还是为了巩固我们对于`pipe()`以及`fork()`的使用，以及如何使用`dup2()`函数。
这里面我就重点说一下`pipe()`和`dup2()`函数吧。
其实正如学习笔记里面的那个例子，我们首先要新建一个int型的有两个元素的数组，这个数组作为`pipe()`的传出参数，担任着记录输入和输出的地址的重任。由于我们要求父进程担任传出端，子进程担任传入端，所以一定要记得分别关闭fd[0]和fd[1]（前者是读入，后者是写出）。

然后就是由于我们不再是在标准输入输出进行输入输出数据，所以要使用dup2对文件描述符的0和1进行重定向即可。

### 代码实现


```
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int fd[2];
	int ret = pipe(fd);
	if(ret == -1)
	{
		perror("pipe error:");
		exit(1);
	}
	pid = fork();
	//pid==0，即为子进程，从管道读数据
	if(pid == 0)
	{
		close(fd[1]);//关闭写端
		dup2(fd[0],STDIN_FILENO);//本来wc从stdin读数据，现在把第0个文件描述符指向了fd[0]
		execlp("wc","wc","-l",NULL);
		
	}
	//父进程，写数据到管道
	else{
		close(fd[0]);//关闭读端
		dup2(fd[1],STDOUT_FILENO);//同理
		execlp("ls","ls",NULL);
		
	}
	return 0;
	
}
```