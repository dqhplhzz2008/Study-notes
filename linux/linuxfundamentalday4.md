
## Linux第四天之C库函数和系统函数

![](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/ckuhanshu1.png)

FILE其实本质上是一个结构体，它里面有：

- 文件描述符（整型值）。索引到对应的磁盘文件。
- 文件读写位置指针：读写文件过程中指针的实际位置。
- I/O缓冲区（内存地址）：通过寻址找到对应的内存块。大小默认是8个byte。设置I/O缓冲区是为了减少对内存的读写访问，节省时间。

Linux的系统函数是没有缓冲区的，需要我们自己提供。

### 文件描述符

![27a83efda5abad975380a4c0276d8da2.png](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/wjmsf.png)


Linux每一个运行的程序（进程），操作系统都会为其分配一个0~4G（232）的地址空间（虚拟地址空间）。文件描述符大小是1024。
文件描述符就是在内核区，如上图所示。第0、1、2个是标准输入、标准输出和标准错误，默认是打开状态，也可以被关闭。每打开一个新文件，则占用一个文件描述，而且使用的是空闲的最小的一个文件描述符。例如我们打开3个文件分别用了3、4和5，这个时候我们关闭了第一个文件，第3个空闲了，再打开第4个文件，那么就占用的是第3个。

### 用户区
Linxu下可执行文件格式是ELF。
![27a83efda5abad975380a4c0276d8da2.png](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/yonghuqu.png)

查看文件类型可以使用`file app`就可以了。如图所示就是ELF。ELF主要包含的三个段.bss、.data、.text，其他还有一些只读数据段和符号段等。
然后下面就是受保护的地址，地址是0~4K。
程序在读的时候首先从代码段开始，全局变量就放在.bss或者.data，局部变量是在栈空间，栈空间是**向下增长**。用户使用new或者malloc分配的内存是从堆空间分配，堆空间是**向上增长**。

### C库函数与系统函数的关系

![0622382618d21aad3f42608fdfe50109.png](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/ckuxths.png)

上图中展示了C语言中printf函数是如何实现的。如图所示，printf函数相当于是一个stdout，它需要通过FILE* 来进行操作。我们知道一个FILE本质上是一个结构体，里面有文件描述符（FD）、文件读写位置指针、I/O缓冲区（C库函数维护的）。当我们使用printf的时候，它调用了Linux系统的API：

- 首先调用了应用层的write函数，printf将文件描述符传递给应用层的write，然后将字符串和字符串的长度传递给了write。write只能在0~3G的用户空间操作，它会帮我们做一个空间转换，将用户空间转换到内核空间。

- 然后从应用层又调用了系统调用层里面的sys_wirte()。这个sys_write()是可以对系统内核进行操作，也就是说对3G~4G范围内进行操作
- 到内核层以后，会调用显示器的驱动，然后让驱动把字符串显示出来。

以上是整个的工作流程。 

    Linux的API又分为三层，由上层到底层分别是：
    - 应用层，包括write,open之类，操作的是用户空间。
    - 系统调用。
    - 内核层。操作设备驱动函数等。
    
### open函数

open是用来打开和创建一个文件或设备。语法如下：
```
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
```

在上述使用方式里面，pathname顾名思义是路径名，flags是打开方式，有O_RDONLY，O_WRONLY或者O_RDWR（分别是只读、只写和读写），当然还有其它的一些打开方式。

第一个语句用于打开已经存在的文件，而第二个语句用于创建一个不存在的文件。第二个语句flags至少应该是一个可写的，并且需要提供一个O_CREAT，创建不存在的文件需要提供mode参数，也就是访问权限。

参数mode具体指明了使用权限，它通常也会被umask修改，所以一般新建文件的权限为`（mode&~umask）`。注意模式只被应用于将来对这个文件的使用中。open调用创建一个新的只读文件，但仍将返回一个可读写文件描述符。

open()通常用于将路径名转换为一个文件描述符，当open()调用成功的时候，它会返回一个新的文件描述符（永远取未用描述符中的最小值）。如果出现错误则返回-1，并在`errno`设置错误信息。

这个调用创建一个新的打开文件，即分配一个新的独一无二的文件描述符，不会与运行中的任何其他程序共享（但可以通过for(2)系统调用实现共享）。这个心的文件描述符在其后对打开文件操作的函数中调用。文件的读写指针被置于文件头。

`errno`是一个全局变量，当函数调用失败后，errno就会被赋值，值就是对应的错误信息。

### open函数中的errno

errno定义在头文件`errno.h`中（地址为/usr/include/errno.h），它是一个**全局变量**，任何标准C库函数都能对其进行修改（Linux系统函数更可以）。

其错误宏定义位置：

- 第1~34个错误定义：/usr/include/asm-generic/errno-base.h
- 第35~133个错误定义：/usr/include/asm-generic/errno.h

我们以errno-base.h截图来看一下，内容如下所示：

![2ddd475893c76eba04a2611f9b0d7ec0.png](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/errnobaseh.png)

我们又改如何查看错误信息呢？我们可以用`perror`函数来实现。

|项目 |说明|
| --- | --- |
|头文件|stdio.h|
|函数定义|void perror(const char *s)|
|函数说明|用来将上一个函数发生错误的原因输出到标准设备（stderr）；参数s所指的字符串会首先被打印出，后面再加上错误原因字符串；此处错误原因依照全局变量errno的值来决定要输出的字符串。|

我们来用实际操作实践一下以下三点：

- 打开一个不存在的文件
- 打开一个已经存在的文件
- 创建一个新文件

下面的第一张图显示的是源代码，第二张图显示的是操作和操作结果。

![896a7035ab5f613848f7062b565e9a0c.png](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/openceshidaima.png)

![9147f46947ce41dff2354912ea8aae96.png](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/openceshizhixing.png)

可以看出以下问题：

- 为什么我设置了新建文件的权限为777，而实际生成的文件的权限是775？如前面我们在介绍open()中的mode中所说，其实本地还有一个掩码umask，这个umask值为0002（如第二张图所示），所以我们实际的权限的计算公式为`（mode&~umask）`，umask取反后做按位与操作。

接下来再进行一个实践，在新建一个文件前来判断下文件是否存在。
就是在`open()`函数中第二个参数中对`O_CREAT`和`O_EXCL`进行连用来判断，即
```
fd=open("newfile", O_RDWR | O_CREAT | O_EXCL, 0777);
```

如果文件存在，则返回`File exists`信息。当然判断文件是否存在不只这一种方法。

还有一种操作就是将文件截断为0，使用参数为`O_TRUNC`。

### read函数

read函数的使用格式如下：

```
#include<unistd.h>
ssize_t read(int fd, void *buf, size_t count);
```
参数中，fd是文件描述符；buf是一个缓冲区，可以通过新建一个数组并将该参数设置为数组名，或者malloc一个内存块，然后把指针名设置为改参数；count是字节数。

|项目 |内容 |
| --- | --- |
| 函数功能 |在文件描述符上执行读操作  |
|函数描述 |read()从文件描述符fd中读取count字节的数据并放入从buf开始的缓冲区。如果count为零，read()返回0并不执行其他操作，如果count大于SSZIE_MAX，则结果不可预料。  |
|返回值 |成功时返回读取到的字节数（为0表示读到文件描述符，即文件已经读完了），此返回值受文件剩余字节数限制，当返回值小于指定的字节数时并不意味着错误，这可能因为当前可读取的字节数小于指定的字节数。发生错误时返回-1，并置errno为相应值，在这种情况下无法得知文件偏移位置是否有变化。  |

### write函数

write函数的使用格式如下：

```
#include<unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
```
参数中，fd是文件描述符；buf是一个缓冲区，可以通过新建一个数组并将该参数设置为数组名，或者malloc一个内存块，然后把指针名设置为改参数；count是字节数。

|项目 |内容 |
| --- | --- |
| 函数功能 |在文件描述符上执行写操作  |
|函数描述 |write()向文件描述符fd所引用的文件中写入从buf开始的缓冲区中count字节的数据。POSIX规定，当使用了write()之后在使用read()，那么读取到的应该是更新后的数据。|
|返回值 |成功时返回所写入的字节数（为0表示没有写入数据）。发生错误时返回-1，并置errno为相应值。若count为零，对普通文件没任何影响，但对特殊文件将产生不可预料的后果。  |


### lseek函数

函数功能是用来重新定位文件读写的位移

语法：
```
#include <sys/types.h>
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);
```
lseek()函数会重新定位被打开文件的位移量，根据参数offset以及whence的组合来决定：

SEEK_SET: 
　　从文件头部开始偏移offset个字节。 
SEEK_CUR： 
　　从文件当前读写的指针位置开始，增加offset个字节的偏移量。 
SEEK_END： 
　　文件偏移量设置为文件的大小加上偏移量字节。
  
|项目 |内容 |
| --- | --- |
| 函数功能 |在文件描述符上执行写操作  |
|函数描述 |write()向文件描述符fd所引用的文件中写入从buf开始的缓冲区中count字节的数据。POSIX规定，当使用了write()之后在使用read()，那么读取到的应该是更新后的数据。|
|返回值 |成功时返回所写入的字节数（为0表示没有写入数据）。发生错误时返回-1，并置errno为相应值。若count为零，对普通文件没任何影响，但对特殊文件将产生不可预料的后果。  |
