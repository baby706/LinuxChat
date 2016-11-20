#include "base.h"
#include "main.h"
#include <malloc.h>
#include "bottomFunction.h"
#include <color.h>

void* thread_func(void* arg)
{
	printf("\n\nEnter:%s\n",__func__);
	struct uni *uniData = (struct uni *)arg;
	DataPack buffer;    //数据包
	memset(&buffer,0,sizeof(buffer));
	int retval = -1;
	//int save_fd = -1;
	while(1)
	{
		
		printf("*************************\n");
		RED;
		printf("\nwaitting for command!\n");
		END;
		printf("*************************\n");
		
		retval = read(uniData->fd ,&buffer,sizeof(buffer));    //接收数据包，存入buffer
		printf("type is %d,name is %s\n",buffer.type,buffer.name);
		
		
		if(retval == 0)
			break;
		if(retval < 0)
		{	
			perror("error:");
			break;
		}
		switch(buffer.type)
		{
			case TYPE_REG:
			
				reg(&buffer,uniData->fd,uniData->userHead);
				break;
			
			case TYPE_LOGIN:
				login(&buffer,uniData->fd,uniData->userHead,uniData->onLineHead);
				break;
			case TYPE_CMD:
				cmd(&buffer,uniData->fd);
				break;
			case TYPE_ONL:
				onl(&buffer,uniData->userHead,uniData->fd);
				break;
			case TYPE_CHAT:
				chat(&buffer,uniData->userHead,uniData->fd);
				break;
				
			default:
				break;
		}
	}
	close(uniData->fd);
	pthread_exit(NULL);
}



int main(int argc,char** argv)
{
	struct onLineLink* onLineHead = (struct onLineLink*)calloc(1,sizeof(struct onLineLink));
	struct userLink* userHead = (struct userLink*)calloc(1,sizeof(struct userLink));
//线程执行函数
	loadUser(userHead);
	
	/*创建了服务器套接字，返回的是套接字文件描述符*/
	int server_fd = -1;
	//第一个参数：AF_INET代表使用IPV4的域
	//第二个参数：使用TCP协议
	//第三个参数：不自定义协议
	server_fd = socket(AF_INET,SOCK_STREAM,0);	
	printf("server_fd = %d\n",server_fd);
	/*绑定本地IP和PORT*/
	//定义一个通用地址结构体
	struct sockaddr_in sock_addr;
	memset(&sock_addr,0,sizeof(sock_addr));
	//指定只有IPV4地址族
	sock_addr.sin_family = AF_INET;
	//指定端口号
	sock_addr.sin_port = htons(atoi(argv[1]));
	//指定IP地址
	sock_addr.sin_addr.s_addr = INADDR_ANY;
	//将指定的IP、PORT、地址族绑定到套接字上
	//第一个参数：要绑定的套接字
	//第二个参数：通用地址结构体（存放的是服务器的IP和端口等信息）
	//第三个参数：地址长度
	socklen_t sock_len = sizeof(sock_addr);
	bind(server_fd,(struct sockaddr *)&sock_addr,sock_len);
	/*监听套接字*/
	//第二个参数：处于等待链接队列中的客户端个数最大为10个
	listen(server_fd,20);
	/*接收客户端链接*/
	struct sockaddr_in client_addr;
	struct uni uniData;
	
	memset(&client_addr,0,sizeof(client_addr));
	socklen_t len = sizeof(client_addr);
	int client_fd = -1;
	pthread_t thread = 0;
	pthread_attr_t attr;    //定义线程属性
	while(1)
	{
		DataPack buff;
		memset(&buff,0,sizeof(buff));
		printf("I am waiting...\n");
		//接受客户端的链接，链接上来的客户端的IP和端口放在第二个参数中
		//返回值为代表客户端的套接字文件描述符
		client_fd = accept(server_fd,(struct sockaddr *)&client_addr,&len);
		
		
		uniData.fd = client_fd;
		uniData.userHead = userHead;
		uniData.onLineHead = onLineHead;
		
		printf("client_fd = %d\n",client_fd);
		printf("client IP:%s,PORT:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);   //以分离状态启动线程
		pthread_create(&thread,&attr,thread_func,(void *)&uniData);
		pthread_attr_destroy(&attr);
	}
	close(server_fd);
	return 0;
}
