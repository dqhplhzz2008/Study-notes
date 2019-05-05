
## 利用stat函数实现ls- l filename功能

### 功能&函数介绍

在我们使用 `ls -l` 命令的时候，会输出下面的结果：

![](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/statls1.png)

在这里，我使用stat函数来实现这一功能。我们知道，stat函数提供了一个结构体，其内容为：

```
struct stat {
    dev_t         st_dev;       //文件的设备编号
    ino_t         st_ino;       //节点
    mode_t        st_mode;      //文件的类型和存取的权限
    nlink_t       st_nlink;     //连到该文件的硬连接数目，刚建立的文件值为1
    uid_t         st_uid;       //用户ID
    gid_t         st_gid;       //组ID
    dev_t         st_rdev;      //(设备类型)若此文件为设备文件，则为其设备编号
    off_t         st_size;      //文件字节数(文件大小)
    blksize_t     st_blksize;   //块大小(文件系统的I/O 缓冲区大小)
    blkcnt_t      st_blocks;    //块数
    time_t        st_atime;     //最后一次访问时间
    time_t        st_mtime;     //最后一次修改时间
    time_t        st_ctime;     //最后一次改变时间(指属性)
};
```

基于此，我们就可以获取到我们想要的信息。
根据图片中使用`ls -l`获得到的信息，我们知道我们需要获得的是块数、文件的类型和存取的权限、硬连接数目、用户ID、组ID、最后一次修改时间、文件名等信息。接下来我们可以分别来进行写。


下面开始讲解这个程序。

### 头文件

首先是所用到的头文件
```
#include <stdio.h> //perror和printf等使用
#include <unistd.h> //stat使用
#include <sys/stat.h> //stat使用
#include <sys/types.h> //stat、getpwuid、getgrgid使用
#include <pwd.h>//getpwuid使用
#include <grp.h>//getgrgid使用
#include <time.h> //输出时间ctime使用
#include<stdlib.h> //exit使用
```
### 文件类型

我们知道，首先要显示的是文件类型，而文件类型则可使用stat结构体中的st_mode与上S_IFMT即可得到相应的文件类型，然后我们可以使用一个switch判断即可。相应的文件类型分别是：

|字符表示 |八进制表示|文件类型名称|
| --- | --- | --- |
|S_IFSOCK|0140000  |套接字  |
|S_IFLINK| 0120000 |符号链接（软连接）  |
| S_IFREG |0100000  |普通文件  |
| S_IFBLK |0060000  | 块设备 |
| S_IFDIR | 0040000 |目录  |
| S_IFCHR |0020000  |字符设备  |
| S_IFIFO |0010000  |管道  |

代码实现可以写为（因为是示例，所以就用两种常用的文件格式来演示）：

```
switch(st.st_mode & S_IFMT)
	{
		case S_IFREG:
			printf("-");
			break;
		case S_IFDIR:
			printf("d");
			break;
	}
```

### 权限输出（以及输出.）

我们知道用户、用户组、其它的权限信息仍然是保存在`st._st_mode`中，且其分布分别是：

- 所有者权限（6~8bit）
- 所属组权限（3~5bit）
- 其它人权限（0~2bit）

所以我们可以通过取某一位，然后判断其除以3的余数情况来判断其是否可以读写执行。由于我们输出顺序为所有者、所有者的用户组、其他人，所以我们要先从高位进行取，取的方式就是将st_mode与某一位为1其它位为0的数字相与（为1的位置就是我们想取的那个位置），然后进行判断。若该部分余0，则说明没有该权限，所以为“-”代码如下：

```
int i = 0;
	for(i = 8;i >= 0;i--)
	{
		if(st.st_mode & (1 << i))
		{
			switch(i%3)
			{
				case 2:
					printf("r");
					break;
				case 1:
					printf("w");
					break;
				case 0:
					printf("x");
					break;
			}
		}
		else
			printf("-");
	}
```
用于在权限后面有一个“.”，所以我们直接输出它：
```
printf(".");
```

### 硬连接数目

接下来就是要输出硬链接的数目，直接读取结构体中的st_nlink即可。所以实现代码如下（记得前面有一个空格）：

```
int hardlin = (int)st.st_nlink;
	printf(" %d",hardlin);
```

### 输出所有者名

由于结构体中存储的是用户的uid，所以要想输出所有者名，我们就需要根据uid来获取用户的用户名。我们可以利用读取`/etc/passwd`进行查找，也可以采用下面的方法，即使用`getpwuid()`这个函数。

**基础知识**：
函数原型：
```
struct passwd *getwnam(const char *name);

struct passwd *getwuid(uid_t uid);
```
- 关于getwnam


|项目|内容|
| --- | --- |
| 功能 | 用来逐一搜索参数name 指定的账号名称, 找到时便将该用户的数据以passwd 结构返回。 |
| 返回值 | 返回 passwd 结构数据, 如果返回NULL 则表示已无数据, 或有错误发生。 |

- 关于getpwuid

|项目|内容|
| --- | --- |
| 功能 | 用来逐一搜索参数uid指定的用户识别码, 找到时便将该用户的数据以passwd结构体返回。 |
| 返回值 | 返回 passwd 结构数据, 如果返回NULL 则表示已无数据, 或有错误发生。 |

- 关于passwd结构体

```
struct passwd
{
    char * pw_name; //用户账号
    char * pw_passwd; //用户密码
    uid_t pw_uid; //用户识别码
    gid_t pw_gid; //组识别码
    char * pw_gecos; //用户全名
    char * pw_dir; //家目录
    char * pw_shell; //所使用的shell 路径
};
```
根据以上，我们可以直接写出以下代码：

```
struct passwd *pw = getpwuid(st.st_uid);
	printf(" %s",pw->pw_name);
```

### 输出所属组名

同上面一样，结构体里面只提供了所属组的GID，所以我们需要根据GID去查找所属组名。方法依然有两种，一为读取`/etc/passwd`进行查找；二为使用`getgrgid()`函数进行返回。

**基础知识**
函数原型：
```
struct group *getgrnam(const char *name)；
struct group *getgrgid(gid_t gid);
```
- 关于getgrnam


|项目|内容|
| --- | --- |
| 功能 | 用来以指定的用户组名来搜索组文件, 找到时便将该组的数据以group 结构返回。 |
| 返回值 | 返回 group 结构数据, 如果返回NULL 则表示已无数据, 或有错误发生。 |

- 关于getgrgid

|项目|内容|
| --- | --- |
| 功能 |用来以指定的gid参数来逐一搜索组文件, 找到时便将该组的数据以group 结构返回。 |
| 返回值 | 返回 group 结构数据, 如果返回NULL 则表示已无数据, 或有错误发生。 |

- 关于group结构体

```
struct group
{
    char *gr_name; //组名称
    char *gr_passwd; //组密码
    gid_t gr_gid; //组识别码
    char **gr_mem; //组成员账号
}
```

所以实现代码如下：
```
struct group *gp=getgrgid(st.st_gid);
	printf(" %s",gp->gr_name);
```

### 输出文件大小、最后修改时间、文件名

文件大小在stat的结构体里面为`st.st_size`。

输出最后修改时间我们可以直接使用结构体里面的`st.st_mtime`即可，但是要转换成标准的日期输出方式，我们就需要用到`ctime()`函数。

其原型如下：
```
char *ctime(const time_t *timep);
```
其功能为：ctime()将参数timep所指的time_t 结构中的信息转换成真实世界所使用的时间日期表示方法，然后将结果以字符串形态返回。此函数已经由时区转换成当地时间，字符串格式为"Wed Jun 30 21 :49 :08 1993\n"。

所以可以直接写出如下代码：
```
printf(" %s %s\n",ctime(&(st.st_mtime)),argv[1]);
```

至此，我们使用stat实现`ls-l filename`功能的程序便写完了。
我们的程序的运行结果如下：

![](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/statls2.png)


