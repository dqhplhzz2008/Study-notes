
# Linux第八天：共享存储映射、匿名映射

## 知识点

- 共享内存
mmap函数：参数、返回值。

- 借助共享内存访问磁盘文件：使用mmap将文件映射到内存，就可以使用指针来对文件进行操作。
- 父子进程（血缘关系进程）使用mmap通信
- 匿名映射区

## 共享存储映射

### 文件进程间通信

使用文件也可以完成IPC，理论依据是，fork后，父子进程共享文件描述符。也就共享打开的文件。

我们来看下面这段代码，这是一个父子进程共享打开的文件描述符（是结构体，不是那个数字），使用文件完成进程间通信。子进程向文件里面写入文件，父进程从文件里面读出信息来。 
```
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(void)
{
    int fd1, fd2; pid_t pid;
    char buf[1024];
    char *str = "---test for shared fd in parent child process---\n";
    pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        fd1 = open("test.txt", O_RDWR);
        if (fd1 < 0) {
            perror("open error");
            exit(1);
        }
        write(fd1, str, strlen(str));
        printf("child wrote over...\n");

    } else {
        fd2 = open("test.txt", O_RDWR);
        if (fd2 < 0) {
            perror("open error");
            exit(1);
        }
        sleep(1);                   //保证子进程写入数据
        int len = read(fd2, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, len);
        wait(NULL);
    }
    return 0;
}
```

### mmap函数

**函数功能：**

**函数原型：**
```
#include <sys/mman.h>
void *mmap(void *adrr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t length);
```
**参数介绍：**
addr: 建立映射区的首地址，由Linux内核指定。使用时，直接传递NULL

length：欲创建映射区的大小

prot：映射区权限PROT_READ、PROT_WRITE、PROT_READ|PROT_WRITE

flags：标志位参数(常用于设定更新物理区域、设置共享、创建匿名映射区)
- MAP_SHARED:  会将映射区所做的操作反映到物理设备（磁盘）上。
- MAP_PRIVATE: 映射区所做的修改不会反映到物理设备。

fd：用来建立映射区的文件描述符

offset：映射文件的偏移(4k的整数倍)，可以把整个文件都映射到内存空间，也可以只把一部分文件内容映射到内存空间。

返回：成功：返回创建的映射区首地址；失败：MAP_FAILED宏

映射区：把磁盘空间上的一个文件映射到内存当中的一块缓冲区上。

munmap的作用就是释放掉所分配的内存。

例程：创建一个映射区，然后把字符串“abc”输出到硬盘字符文件中。

```
#include <stdio.h>
#include <unistd.h>//(f)truncate使用
#include <sys/types.>//(f)truncate使用
#include <sys/mman.h>

int main(void)
{
	char *p = NULL;//我们想传一个字符串
	int fd = open("mytest.txt", O_CREAT|O_RDWR, 0644);
	if(fd <0){
		perror("open error:");
		exit(1);
	}
	int ret = ftruncate(fd,4);
	if(ret == -1)
	{
		perror("ftrucate error:");
		exit(1);
	}
	p = mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);//void*可以和任何指针类型隐式转换，所以不需要强制转换
	if(p == MAP_FAILED)
	{
		perror("mmap error:");
		exit(1);
	}
	strcpy(p,"abc");//写数据，操作共享内存结束
	int reet = munmap(p,len);
	if(ret == -1)
	{
		perror("munmap error: ");
		exit(1);
	}
	close(fd);
	return 0;
	
}
```

### 使用mmap注意事项

1. 使用malloc可以分配0字节大小的内存，但是用mmap却不能创建0字节大小的映射区。这要求我们：**创建一个新文件以后一定要指定一定的大小才可以使用mmap。**
2.  如果我们分配映射区之后将首地址赋值给mem，这个时候我们将指针mem后移一位（++mem），那么输入内容还是可以输入的，但是munmap操作就会失败。这要求我们：**在移动mem指针后，如果完成了所有操作，必须将mem移回初始位置。**
3.  如果open文件的时候设置的权限是只读（`O_RDONLY`），mmap的时候PROT参数指定为`PROT_READ | PROT_WRITE`，且设置为`MAP_SHARED`，那么就会报错，提示`Permission denied`。如果设置为`MAP_PRIVATE`，就会出现“总线错误（核心已转储）”。这要求我们：**创建映射区的时候要小于等于打开文件的权限，映射区创建过程中隐含着一次对文件的读操作。**
4.  最后一个参数offset必须是**4k的整数倍**。这是因为映射是由MMU帮忙创建的，而MMU操作的基本单位就是4K，所以才会这样。
5.  文件描述符先关闭，对mmap映射没有影响。所谓文件描述符是你用mmap进行映射的句柄，当映射建立以后，这个文件描述符就没有什么作用了。

### mmap父子进程间的通信

我们看如下例程：
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

int var = 100;

int main(void)
{
    int *p;
    pid_t pid;

    int fd;
    fd = open("temp", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if(fd < 0){
        perror("open error");
        exit(1);
    }
    unlink("temp");				//删除临时文件目录项,使之具备被释放条件.
    ftruncate(fd, 4);

    p = (int *)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    //p = (int *)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    if(p == MAP_FAILED){		//注意:不是p == NULL
        perror("mmap error");
        exit(1);
    }
    close(fd);					//映射区建立完毕,即可关闭文件

    pid = fork();				//创建子进程
    if(pid == 0){
        *p = 2000;//将映射区第一个内存的值修改为2000
        var = 1000;
        printf("child, *p = %d, var = %d\n", *p, var);
    } else {
        sleep(1);
        printf("parent, *p = %d, var = %d\n", *p, var);
        wait(NULL);

        int ret = munmap(p, 4);				//释放映射区
        if (ret == -1) {
            perror("munmap error");
            exit(1);
        }
    }

    return 0;
}
```
这个例程的输出结果如下：
child, *p = 2000, var = 1000
parent, *p = 2000, var =100

为什么是这样的结果呢？这是由于我们在之前学习的时候就提到过：
父子进程共享：
* 文件描述符(打开文件的结构体)  
* mmap建立的映射区 (进程间通信详解)

p位于映射区，而var是全局变量，位于0~3G的用户区，遵循**读时共享写时复制**的原则，子进程在修改的时候自动执行了复制操作，所以子进程只修改了自己复制的那一份的内容。

当我们把`MAP_SHARED`修改为`MAP_PRIVATE`时，父子进程独享内存映射区。所以次数的输出为
child, *p = 2000, var = 1000
parent, *p = 0, var =100

## 匿名映射

通过使用我们发现，使用映射区来完成文件读写操作十分方便，父子进程间通信也较容易。但缺陷是，每次创建映射区一定要依赖一个文件才能实现。通常为了建立映射区要open一个temp文件，创建好了再unlink、close掉，比较麻烦。 可以直接使用匿名映射来代替。其实Linux系统给我们提供了创建匿名映射区的方法，无需依赖一个文件即可创建映射区。同样需要借助标志位参数flags来指定。
在mmap中使用`MAP_ANONYMOUS` (或`MAP_ANON`)参数。
```
p = mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
```

需注意的是，MAP_ANONYMOUS和MAP_ANON这两个宏是Linux操作系统特有的宏。在其它类Unix系统中如无该宏定义，可使用如下两步来完成匿名映射区的建立。
1. fd = open("/dev/zero", O_RDWR);
2. p = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

其它类Unix系统包括IBM、苹果、惠普和sun等开发的商业版本以及BSD等。

## mmap无血缘关系进程间通信

实质上mmap是内核借助文件帮我们创建了一个映射区，多个进程之间利用该映射区完成数据传递。由于内核空间多进程共享，因此无血缘关系的进程间也可以使用mmap来完成通信。只要设置相应的标志位参数flags即可。若想实现共享，当然应该使用`MAP_SHARED`了。

mmap_w.c
```
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
struct STU {
    int id;
    char name[20];
    char sex;
};
void sys_err(char *str)
{
    perror(str);
    exit(1);
}
int main(int argc, char *argv[])
{
    int fd;
    struct STU student = {10, "xiaoming", 'm'};
    char *mm;
    if (argc < 2) {
        printf("./a.out file_shared\n");
        exit(-1);
    }
    fd = open(argv[1], O_RDWR | O_CREAT, 0664);
    ftruncate(fd, sizeof(student));
    mm = mmap(NULL, sizeof(student), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (mm == MAP_FAILED)
        sys_err("mmap");
    close(fd);
    while (1) {
        memcpy(mm, &student, sizeof(student));
        student.id++;
        sleep(1);
    }
    munmap(mm, sizeof(student));
    return 0;
}
```
mmap_r.c
```
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

struct STU {
    int id;
    char name[20];
    char sex;
};

void sys_err(char *str)
{
    perror(str);
    exit(-1);
}

int main(int argc, char *argv[])
{
    int fd;
    struct STU student;
    struct STU *mm;

    if (argc < 2) {
        printf("./a.out file_shared\n");
        exit(-1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        sys_err("open error");

    mm = mmap(NULL, sizeof(student), PROT_READ, MAP_SHARED, fd, 0);
    if (mm == MAP_FAILED)
        sys_err("mmap error");
    
    close(fd);

    while (1) {
        printf("id=%d\tname=%s\t%c\n", mm->id, mm->name, mm->sex);
        sleep(2);
    }

    munmap(mm, sizeof(student));

    return 0;
}
```

最后在说几句，当我们新建了一块内存映射，我们应该把这块内存当做数组来看待。所谓mm或者说p指向了数组的首地址。

以上是我们针对非血缘关系进程在内存区进行操作，那么我们可否将文件作为通信的桥梁呢？答案是可以的。文件打开是得到文件结构体，文件结构体在内核中，a、b两个进程内核处于同一区域，所以是可以的。

### strace函数

```
strace 可执行文件
```
可以追踪这个可执行文件使用到的系统调用有哪些。可以看到，我们在使用open/write/read函数的时候，系统底层都在使用mmap函数。
