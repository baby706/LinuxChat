//客户端

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

//定义协议包结构体
struct protocol
{
	int type;
	char buff[1024];
	char shell[20];
};

#define MESSAGE 1
#define SHELL 2


//int socket(int domain, int type, int protocol);
//int bind(int sockfd, const struct sockaddr *addr,                socklen_t addrlen);
// int listen(int sockfd, int backlog);
// int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
// in_addr_t inet_addr(const char *cp);
// char *inet_ntoa(struct in_addr in);
// int connect(int sockfd, const struct sockaddr *addr,                   socklen_t addrlen);


int main(int argc,char** argv)
{
	/*创建了客户端套接字，返回的是套接字文件描述符*/
	int client_fd = -1;
	//第一个参数：AF_INET代表使用IPV4的域
	//第二个参数：使用TCP协议
	//第三个参数：不自定义协议
	client_fd = socket(AF_INET,SOCK_STREAM,0);	
	printf("client_fd = %d\n",client_fd);
	//定义一个通用地址结构体
	struct sockaddr_in sock_addr;
	memset(&sock_addr,0,sizeof(sock_addr));
	//指定只有IPV4地址族
	sock_addr.sin_family = AF_INET;
	//指定端口号
	sock_addr.sin_port = htons(atoi(argv[1]));
	//指定IP地址
	sock_addr.sin_addr.s_addr = inet_addr(argv[2]);
	//将客户端的套接字链接上服务器的IP和端口
	//第一个参数：客户端套接字
	//第二个参数：通用地址结构体（存放的是服务器的IP和端口等信息）
	//第三个参数：地址长度
	if(connect(client_fd,(struct sockaddr *)&sock_addr,sizeof(sock_addr)) < 0)
	{
		perror("connect error:");
		exit(1);
	}
	//创建协议包结构体
	struct protocol data;
	memset(&data,0,sizeof(data));
	int choose = 0;
	while(1)
	{
		printf("1.message\n2.shell\n");
		scanf("%d",&choose);
		getchar();
		//如果选择1,就发送消息数据
		if(choose == 1)
		{
			data.type = MESSAGE;
			fgets(data.buff,sizeof(data.buff),stdin);
			//向服务器发送数据
			write(client_fd,&data,sizeof(data));
		}
		//如果选择2就发送shell数据
		else if(choose == 2)
		{
			char buff[1024] = "\0";
			data.type = SHELL;
			fgets(data.shell,sizeof(data.shell),stdin);
			//将数据发送给服务器
			write(client_fd,&data,sizeof(data));
			memset(&data,0,sizeof(data));
			//读取服务器的数据
			read(client_fd,buff,sizeof(buff));
			printf("shell retval= %s\n",buff);
			//每次读完之后清空数据
			memset(buff,0,sizeof(buff));
		}
	}	
	close(client_fd);
	return 0;
}
