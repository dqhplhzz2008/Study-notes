
# day7练习3:统计当前系统中进程由用户运行的进程并输出到文件中

## 题目描述

统计当前系统中进程由用户运行的进程并输出到文件中。

## 题目解析
统计当前系统中进程由用户运行的进程并输出到屏幕上的命令为：
```
ps -u xiaoao | wc -l
```
而在这里我们使用的代码有`pipe()`、`fork()`和`dup2()`等。

## 代码实现

```
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	pid_t pid;
	pid_t wpid;
	int i;
	int n = 2;
	int fd[2];
	//首先pipe
	int ret = pipe(fd);
	if(ret == -1)
	{
		perror("pipe error:");
		exit(1);
	}
	for(i=0;i<n;i++)
	{
		pid = fork();
		if(pid == 0)
			break;
	}
	//子进程1为兄，执行ps -u xiaoao
	if(i == 0)
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		execlp("ps","ps","-u","xiaoao",NULL);
	}
	else if(i == 1)
	{
        int fdff = open("day7out", O_RDWR | O_CREAT, 0644);
        if( fdff == -1)
        {
            perror("File open error:");
            exit(1);
        }   
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		dup2(fdff,STDOUT_FILENO);
        execlp("wc","wc","-l",NULL);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		do{
			wpid = waitpid(-1, NULL, WNOHANG);
			if(wpid > 0)
				n--;
			sleep(1);
		}while(n > 0);
		printf("Clean finished!!!\n");
		
	}
	return 0;
}
```
