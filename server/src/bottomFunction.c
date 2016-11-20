#include "base.h"
#include "main.h"
#include "bottomFunction.h"

//struct onLineLink* createOnLineNode(struct onLine data);

extern struct onLineLink* onLineHead;

void reg(DataPack* buffer,int client_fd,struct userLink* userHead)
{
	struct user userData;
	if(userHead == NULL)
	{
		printf("头节点为空!\n");
		buffer->type = TYPE_ERR;
		strcpy(buffer->data,"服务器错误！");
		write(client_fd,buffer,sizeof(*buffer));
	}
	
	struct userLink* pre = selectUserLink(userHead,buffer->name);
	if(pre != NULL)
	{
		memset(buffer,0,sizeof(*buffer));
		buffer->type = TYPE_ERR;
		strcpy(buffer->data,"用户名已存在！");
		write(client_fd,buffer,sizeof(*buffer));
	}
	
	else
	{
		
		strcpy(userData.name,buffer->name);
		memset(buffer,0,sizeof(*buffer));
		buffer->type = TYPE_OK;
		strcpy(buffer->data,"用户名输入正确！");
		write(client_fd,buffer,sizeof(*buffer));
	}
	
	read(client_fd,buffer,sizeof(*buffer));
	printf("passwd is %s\n",buffer->passwd);
	strcpy(userData.passwd,buffer->passwd);
	
	printf("username :%s passwd :%s\n",userData.name,userData.passwd);
	buffer->type = TYPE_OK; 
	write(client_fd,buffer,sizeof(*buffer));
	
	insertAfterUser(userHead,userData);
	printf("注册成功！\n");
	printUserLink(userHead);
	saveUser(userHead);
	
}


struct userLink* createUserNode(struct user data)
{
	struct userLink* new = (struct userLink*)calloc(1,sizeof(struct userLink));
	new->data = data;
	new->next = NULL;

	return new;
}

//后向插入，将创建的节点插入userLink链表尾部
void insertAfterUser(struct userLink* userHead,struct user data)
{
	if(userHead == NULL)
	{
		printf("头节点为空!\n");
		return ;
	}
	while(userHead->next != NULL)
	{
		userHead = userHead->next;
	}
	struct userLink* new = createUserNode(data);
	userHead->next = new;
}

void loadUser(struct userLink* userHead)
{
	if(userHead == NULL)
	{
		printf("头节点为空!\n");
		return ;
	}
	FILE* fp = fopen("data/user.dat","r");
	if(fp == NULL)
	{
		printf("加载文件中...!\n");
		return ;
	}
	struct user data;  //创建一个临时变量用来保存从文件中读取的数据
	while(1)
	{
		int res = fread(&data,sizeof(struct user),1,fp);  //将数据存到临时变量中，并返回读取的字节数
		if(res<1)
		{
			break;
		}
		insertAfterUser(userHead,data);
		
	}
	fclose(fp);
	fp = NULL ;
}

//保存用户链表
void saveUser(struct userLink* userHead)
{
	//printf("this is save function\n");
	if(userHead == NULL)
	{
		printf("头节点为空!\n");
		return ;
	}
	FILE* fp = fopen("data/user.dat","w");
	if(fp == NULL)
	{
		printf("写入文件失败!\n");
		return ;
	}
	userHead = userHead->next;   //跳过头节点
	while(userHead != NULL)
	{
		fwrite(&userHead->data,sizeof(struct user),1,fp);
		userHead = userHead->next;
	}
	fclose(fp);
	fp = NULL;
}

struct userLink* selectUserLink(struct userLink* userHead,char *id)
{
	if(userHead == NULL)
	{
		printf("头节点为空!\n");
		return NULL;
	}
	
	struct userLink* pre = userHead;   //保留当前查询到的id的上一个节点
	userHead = userHead->next;   //跳过头节点
	while(userHead != NULL)
	{
		if(strcmp(userHead->data.name,id) == 0)
		{
			return pre;
		}
		pre = userHead;
		userHead = userHead->next;
	}
	return NULL;
}

//查看用户链表
void printUserLink(struct userLink* userHead)
{
	if(userHead == NULL)
	{	
		printf("头节点为空!\n");
		return ;
	}
	userHead = userHead -> next;
	while(userHead != NULL)
	{
		printf("用户名:%s    密码:%s   \n",userHead->data.name,userHead->data.passwd);
		userHead = userHead->next;
	}
	
}
 
//登陆函数 
void login(DataPack* buffer,int client_fd,struct userLink* userHead,struct onLineLink* onLineHead)
{
	printf("name is %s ,passwd is %s\n",buffer->name,buffer->passwd);
	struct onLineLink* pre2 = selectionLineLink(onLineHead,buffer->name);
	if(pre2 != NULL)
	{
		buffer->type = TYPE_ERR;
		strcpy(buffer->data,"当前用户已在别处登陆，请检查是否密码泄露！");
		write(client_fd,buffer,sizeof(*buffer));
		//exit(1);
	}
	
	struct userLink* pre = selectUserLink(userHead,buffer->name);
	if(pre == NULL)
	{
		buffer->type = TYPE_ERR;
		strcpy(buffer->data,"用户名或密码错误，请重新输入！");
		write(client_fd,buffer,sizeof(*buffer));
		//exit(1);
	}
	else
	{
		
		if((strcmp(buffer->name,pre->next->data.name) == 0) && (strcmp(buffer->passwd,pre->next->data.passwd)))
		{
			buffer->type = TYPE_OK;
			printf("登陆成功！\n");
			struct onLine data;
			strcpy(data.name,buffer->name);
			data.fd = client_fd;
			insertAfterOnline(onLineHead,data);
			write(client_fd,buffer,sizeof(*buffer));
			//return ;
		}
		else
		{
			buffer->type = TYPE_ERR;
			write(client_fd,buffer,sizeof(*buffer));
			//exit(1);
		}
		
	}
}


struct onLineLink* createOnlineNode(struct onLine data)
{
	struct onLineLink* new = (struct onLineLink*)calloc(1,sizeof(struct onLineLink));
	new->data = data;
	new->next = NULL;

	return new;
}

//后向插入，将创建的节点插入onLineLink链表尾部
void insertAfterOnline(struct onLineLink* onLineHead,struct onLine data)
{
	if(onLineHead == NULL)
	{
		printf("在线链表头节点为空!\n");
		return ;
	}
	while(onLineHead->next != NULL)
	{
		onLineHead = onLineHead->next;
	}
	struct onLineLink* new = createOnlineNode(data);
	onLineHead->next = new;
}


struct onLineLink* selectionLineLink(struct onLineLink* onLineHead,char *id)
{
	if(onLineHead == NULL)
	{
		printf("在线链表头节点为空!\n");
		return NULL;
	}
	
	struct onLineLink* pre = onLineHead;   //保留当前查询到的id的上一个节点
	onLineHead = onLineHead->next;   //跳过头节点
	while(onLineHead != NULL)
	{
		if(strcmp(onLineHead->data.name,id) == 0)
		{
			return pre;
		}
		pre = onLineHead;
		onLineHead = onLineHead->next;
	}
	return NULL;
}


void cmd(DataPack* buffer,int client_fd)
{
	char err[100] = "\0";
	int save_fd = dup(1);
	dup2(client_fd,1);
	int ret = system(buffer->data);
	if(!ret)
	{
		strcpy(err,"错误：命令未找到！\n");
		write(client_fd,err,100);
	}
	dup2(save_fd,1);
	printf("ret is %d\n",ret);
	return ;
	
}


void onl(DataPack* buffer,struct userOnlineLink* userHead,int client_fd)
{
	char name[20];
	bzero(name,20);
	if(userHead == NULL)
	{
		buffer->type = TYPE_ERR;
		write(client_fd,&buffer,sizeof(*buffer));
		return ;
	}
	else
	{
		userHead = userHead->next;   //跳过头节点
		while(userHead != NULL)
		{
			strcpy(name,userHead->name);
			write(client_fd,name,20);
		}
		strcpy(name,"end");
		write(client_fd,name,20);
	}
	return ;
	
}

//单聊函数
void chat(DataPack* buffer,struct OnlineLink* userHead,int client_fd)
{
	int fd;
	char name[20] = "\0";
	strcpy(name,buffer->name);
	fd = getFd(buffer,name,userHead);
	write(fd,buffer,sizeof(buffer));
	return ;
	
}

int getFd(DataPack* buffer,char* name,struct onLineLink* userHead)
{
	if(userHead == NULL)
	{
		buffer->type = TYPE_ERR;
		write(client_fd,buffer,sizeof(buffer));
		return ;
	}
	else
	{
		userHead = userHead->next;
		while(userHead != NULL)
		{
			if(strcmp(name,userHead->name) == 0)
			{
				return userHead->fd;
			}
			
			userHead = userHead -> next;
		}
	}
	return ;
}













































