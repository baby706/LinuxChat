#ifndef BOTTOMFUNCTION_H_
#define BOTTOMFUNCTION_H_

#include "base.h"
#include "main.h"

extern struct userLink* userHead;

void login(DataPack* buffer,int client_fd,struct userLink* userHead,struct onLineLink* onLineHead);

void reg(DataPack* buffer,int client_fd,struct userLink* userHead);

struct userLink* createUserNode(struct user data);

//后向插入，将创建的节点插入userLink链表尾部
void insertAfterUser(struct userLink* userHead,struct user data);

void loadUser(struct userLink* userHead);

//保存用户链表
void saveUser(struct userLink* userHead);

//查询函数
struct userLink* selectUserLink(struct userLink* userHead,char *id);

void printUserLink(struct userLink* userHead);

struct onLineLink* createOnLineNode(struct onLine data);

//后向插入，将创建的节点插入onLineLink链表尾部
void insertAfterOnline(struct onLineLink* onLineHead,struct onLine data);

struct onLineLink* selectionLineLink(struct onLineLink* onLineHead,char *id);

void cmd(DataPack* buffer,int client_fd);
#endif
