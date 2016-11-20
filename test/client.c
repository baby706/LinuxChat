#include <stdio.h>
#include "../client/include/base.h"

int main(int argc,char** argv)
{
	int sockfd = -1;     //声明套接字
	sockfd = socket(AF_INET,SOCK_STREAM,0);    //创建套接字
	if(sockfd < 0)
	{
		perror("sockfd error");
		exit(1);
	}
	struct sockaddr_in serveraddr;     //声明专用地址
	serveraddr.sin_family = AF_INET;    //ipv4协议
	serveraddr.sin_port = htons(atoi(argv[2]));     //将数据格式转换为网络格式
	inet_pton(AF_INET,argv[1],&serveraddr.sin_addr.s_addr);     //将点分十进制地址转化为二进制整数
	if((connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)))!= 0)
	{
		perror("connect error");
		exit(1);
	}
	char buffer[200];
	printf("I am connectting ...\n");
	char bei[] = "贝贝：";
	char i[] = "我：";
	while(1)
	{
		write(1,i,sizeof(i));
		memset(buffer,0,sizeof(buffer));
		fgets(buffer,sizeof(buffer),stdin);
		write(sockfd,buffer,sizeof(buffer));
		read(sockfd,buffer,sizeof(buffer));
		write(1,bei,sizeof(bei));
		write(1,buffer,sizeof(buffer));
		
	}
	
	
	return 0;
	
}
