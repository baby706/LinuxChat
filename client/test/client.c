#include <unistd.h>
#include <string.h>
#include <memory.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc,char** argv)
{
	int sockfd = -1;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	if(argc < 3)
	{
		printf("usgae: %s ip port\n",argv[0]);
		exit(1);
	}
	
	if(sockfd < 0)
	{
		perror("sockfd error");
		exit(1);
	}
	
	struct sockaddr_in serveraddr;    //服务器地址
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));    //服务器端口
	inet_pton(AF_INET,argv[1],&serveraddr.sin_addr.s_addr);
	
	if( connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)     //连接服务器
	{
		perror("connect error");
		exit(1);
	}
	
	char buffer[1024];
	memset(buffer,0,sizeof(buffer));
	size_t size;
	while(1)
	{
	
	
		fgets(buffer,sizeof(buffer),stdin);
		write(sockfd,buffer,sizeof(buffer));
		printf("buffer is %s\n",buffer);
		
		//fflush(stdout);
		memset(buffer,0,sizeof(buffer));
	
		/*if((size = read(sockfd,buffer,sizeof(buffer))) < 0)
		{
			perror("read error");
			exit(1);
		}
	
		if(write(STDOUT_FILENO,buffer,size)!=size)
		{
			perror("write error");
			exit(1);
		}*/
	}
	
	close(sockfd);

	return 0;
}
