#include <color.h>
#include "base.h"
#include "menu.h"

extern int sockfd;
extern DataPack buffer;

void mainMenu()
{
	while(1)
	{	
		int choose = -1;
		system("clear");
		YELLOW;
		printf("\t\t\t\t\t聊天系统  v1.0  \n\n");
		END;
		printf("\t\t\t\t*****************************************\n");
		printf("\t\t\t\t*\t\t\t\t\t*\n");
		printf("\t\t\t\t*\t\t1.登陆\t\t\t*\n");
		printf("\t\t\t\t*\t\t2.注册\t\t\t*\n");
		printf("\t\t\t\t*");
		RED;
		printf("\t\t3.退出");
		END;
		printf("\t\t\t*\n");
		END;
		printf("\t\t\t\t*\t\t\t\t\t*\n");
		printf("\t\t\t\t*****************************************\n\n");
		printf("\t\t\t\t请选择:");
		scanf("%d",&choose);
		while(getchar() != '\n');   //吸收输入选择后的回车
		switch(choose)
		{
			case 1:
			    login();
				break;
			
			case 2:
				regin();
				break;
			
			case 3:
				return ;
			default:
				break;
				
		}
	}

}

void login(int fd)
{
	int i = 3;
	while(1)
	{
		buffer.type = TYPE_LOGIN;
		if(i == 0)
		{
			printf("出错次数达到上线，请稍后再试！\n");
			exit(1);
		}
		char name[20];
		char passwd[20];
		printf("请输入你的用户名：");
		scanf("%s",name);
		while(getchar()!='\n');
		printf("请输入你的密码：");
		scanf("%s",passwd);
		strcpy(buffer.name,name);
		strcpy(buffer.passwd,passwd);
		sendToServer();
		revFromServer();
		
		if(buffer.type == TYPE_ERR)
		{
			printf("%s\n",buffer.data);
			i--;
			continue;
		}
		
		if(buffer.type == TYPE_OK)
		{
			printf("恭喜您，登陆成功！\n");
			sleep(1.5);
			menu2();
			return ;
			//menuLogin(name);
		}
		
	}
}

void regin()
{ 
	char name[20];
	char passwd[20];
	while(1)
	{
		printf("请输入用户名：");
		scanf("%s",name);
		buffer.type = TYPE_REG;
		strcpy(buffer.name,name);
		sendToServer();
		memset(&buffer,0,sizeof(buffer));
		revFromServer();
		if(buffer.type == TYPE_ERR)
		{
			printf("%s\n",buffer.data);
			continue;
		}
		if(buffer.type == TYPE_OK)
		{
			printf("%s\n",buffer.data);
			
		}
		printf("请输入密码：");
		scanf("%s",passwd);
		strcpy(buffer.passwd,passwd);
		sendToServer();
		revFromServer();
		//revFromServer();
		if(buffer.type == TYPE_OK)
		{
			printf("恭喜您，注册成功!\n");
			sleep(1);
			break;
		}
		else
		{
			printf("type is %d\n",buffer.type);
		}
		
	}
	
}



void sendToServer()
{
	write(sockfd,&buffer,sizeof(buffer));
}

void revFromServer()
{
	read(sockfd,&buffer,sizeof(buffer));
}
int connectServer(int argc,char** argv)
{
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	printf("client_fd is %d\n",sockfd);
	
	if(argc < 2)
	{
		printf("usgae: %s  port\n",argv[0]);
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
	serveraddr.sin_port = htons(atoi(argv[1]));    //服务器端口
	inet_pton(AF_INET,"127.0.0.1",&serveraddr.sin_addr.s_addr);
	
	if( connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)     //连接服务器
	{
		perror("connect error");
		return -1;
	}	
	return 0;
}

void menu2()
{
	while(1)
		{	
			int choose = -1;
			system("clear");
			YELLOW;
			printf("\t\t\t\t\t聊天系统  v1.0  \n\n");
			END;
			printf("\t\t\t\t*****************************************\n");
			printf("\t\t\t\t*\t\t\t\t\t*\n");
			printf("\t\t\t\t*\t\t1.单聊\t\t\t*\n");
			printf("\t\t\t\t*\t\t2.群聊\t\t\t*\n");
			printf("\t\t\t\t*\t\t3.命令\t\t\t*\n");
			printf("\t\t\t\t*");
			RED;
			printf("\t\t4.返回");
			END;
			printf("\t\t\t*\n");
			END;
			printf("\t\t\t\t*\t\t\t\t\t*\n");
			printf("\t\t\t\t*****************************************\n\n");
			printf("\t\t\t\t请选择:");
			scanf("%d",&choose);
			while(getchar() != '\n');   //吸收输入选择后的回车
			switch(choose)
			{
				case 1:
					chat();
					break;
				case 2:
					group();
					break;	
				case 3:
					commd();
					break;	
				case 4:
					return ;
				default:
					printf("输入错误，请重新选择！\n");
					break;
				
			}

		}
}

//shell命令菜单

void commd()
{
	char con[10240] = "\0";
	printf("请输入命令:");
	char cmd[40];
	bzero(cmd,40);
	fgets(cmd,40,stdin);
	buffer.type = TYPE_CMD;
	strcpy(buffer.data,cmd);
	sendToServer();
	read(sockfd,con,10240);
	printf("%s\n",con);
	printf("返回请按ENTER\n");
	while(getchar()!='\n');
	return ;
	
}

//单聊函数
void chat()
{
	char name[20];
	bzero(name,20);
	printf("目前在线用户为：\n");
	buffer.type = TYPE_ONL;
	sendToServer();
	getOnl();
	
	alarm(3);
	signal(SIGALRM,heartHandler);
	printf("请输入需要聊天的用户名:");
	scanf("%s",name);
	
	printf("**************开始聊天*******************\n");
	while(1)
	{
		bzero(buffer.message,sizeof(buffer.message));
		printf("我： ")；
		scanf("%s",buffer.message);
		buffer.type = TYPE_CHAT;
		strcpy(buffer.name,name);
		sendToServer();
	}
	pthread_t chatPth;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);   //以分离状态启动线程
	pthread_create(&chatPth,&attr,chatFunc,NULL);
	pthread_attr_destroy(&attr);
}



void* chatFunc(void* arg)
{
	while(1)
	{
		revFromServer();
		if((strcmp(buffer.message,"~end~")) != 0)
		{
			write(1,buffer->message,sizeof(buffer->message))
		}
		else
		{
			printf("该用户已下线！\n");
			return ;
		}	
	}
}
//群聊函数
void group()
{

}

//心跳函数

void heartHandler(int signo)
{
	buffer.type = TYPE_HEART;
	sentToServer();
	alarm(3);
}

void getOnl()
{
	while(1)
	{
		char name[20];
		bzero(name,20);
		read(sockfd,name,20);
		if(strcmp(name,"end") != 0)
		{
			printf("%s ",name);
		}
		else
		{
			break;
		}
	}
}










