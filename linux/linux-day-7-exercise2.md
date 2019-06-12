
## day7练习2

### 问题描述

使用管道实现兄弟进程间通信。 兄：ls  弟： wc -l  父：等待回收子进程。


### 题目解析

与练习2题目类似，不再提供解析。

### 代码实现

```
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
	pid_t pid;
	int i;
	int n=2;
	int fd[2];
	int ret = pipe(fd);
	if(ret == -1)
	{
		perror("pipe error:");
		exit(1);
	}
	//创建两个子进程
	for(i=0;i<n;i++)
	{
		pid = fork();
		if(pid == 0)
			break;
	}
	//子进程1：兄
	if(i == 0)
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls",NULL);
	}
	//子进程2：弟
	else if(i == 1)
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		execlp("wc","wc","-l",NULL);
		
	}
	//父进程
	else
	{
		close(fd[0]);
		close(fd[1]);
		sleep(2);
		for(i=0;i < 2;i++)
		{
			wait(NULL);
		}
	}

	return 0;
	
}
```