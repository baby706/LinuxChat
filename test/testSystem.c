#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{
	int fd1,fd2,save_fd;
	char cmd[100],err[100],com[100];
	save_fd = dup(1);
	fd1 = open("a.txt",O_RDWR|O_CREAT,0777);
	fd2 = open("b.txt",O_RDWR|O_CREAT,0777);
	
	int ret = -1;
	
	while(1)
	{
		//system("rm *.txt");
		bzero(cmd,100);bzero(err,100);bzero(com,100);
		dup2(fd2,2);
		printf("please input a command:");
		fflush(stdout);
		dup2(fd1,1);
		fgets(cmd,100,stdin);
		ret = system(cmd);
		dup2(save_fd,1);
		printf("\nthe conntent info is \n");
		system("cat a.txt");
		printf("\nthe error info is \n");
		system("cat b.txt");
		printf("ret is %u\n",ret);
		while(getchar() == '\n')
		{
			system("clear");
			break;
		}
		
		
	}
	
	return 0;
}
