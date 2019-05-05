#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	if(argc<2)
	{
		printf("Usage:./lsl <filename>\n");
		exit(1);
	}
	struct stat st;//保存文件信息的结构体
	int ret = stat(argv[1],&st);//把stat信息读取出来保存在st
	if(ret == -1)
	{
		perror("Stat Error:");
		exit(1);
	}
# if 0
	/*通过宏函数判断文件类型*/
	if(S_ISREG(st.st_mode))
		printf("-");
	else if(S_ISDIR(st.st_mode))
		printf("d");
#endif
	//通过st_mode的值判断文件类型,其他类型就不在这里写了
	switch(st.st_mode & S_IFMT)
	{
		case S_IFREG:
			printf("-");
			break;
		case S_IFDIR:
			printf("d");
			break;
	}
	//文件的三个权限（读写执行，用户，用户组，其他）
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
	printf(".");
	int hardlin = (int)st.st_nlink;
	printf(" %d",hardlin);
	struct passwd *pw = getpwuid(st.st_uid);//根据UID获取用户的用户名
	printf(" %s",pw->pw_name);

	struct group *gp=getgrgid(st.st_gid);
	printf(" %s",gp->gr_name);

	printf(" %ld", st.st_size);

	printf(" %s %s\n",ctime(&(st.st_mtime)),argv[1]);
	return 0;
}
