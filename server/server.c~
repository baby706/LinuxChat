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

int sockfd = -1;

void out_addr(struct sockaddr_in *clientaddr)     
{
	int port  = ntohs(clientaddr->sin_port);
	char ip[16];
	memset(ip,0,sizeof(ip));
	inet_ntop(AF_INET,&clientaddr->sin_addr.s_addr,ip,sizeof(ip));
	printf("client: %s(%d) connetct\n",ip,port);
	
}

int main(int argc,char** argv)
{
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in serveraddr;
	memset(&serveraddr,0,sizeof(serveraddr));
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[1]));
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	
	socklen_t addrlen = sizeof(serveraddr);
	if((bind(sockfd,(struct sockaddr*)&serveraddr,addrlen)) < 0)
	{
		perror("bind error");
		exit(1);
	}
	
	if((listen(sockfd,10))<0)
	{
		perror("listen error");
		exit(1);
	}
	
	struct sockaddr_in clientaddr;     //客户端地址
	memset(&clientaddr,0,sizeof(clientaddr));
	socklen_t clientaddr_len = sizeof(clientaddr);
	int fd;
	char buffer[1024];
	memset(buffer,0,sizeof(buffer));
	while(1)
	{
		int fd = accept(sockfd,(struct sockaddr*)&clientaddr,&clientaddr_len);
		if(fd < 0)
		{
			perror("accept error");
			exit(1);
		}
		out_addr(&clientaddr);
		while(1)
		{
			read(fd,buffer,sizeof(buffer));
			//printf("%s",buffer);
			write(1,buffer,sizeof(buffer));
			memset(buffer,0,sizeof(buffer));
		}
	}
	close(fd);
	return 0;

}
