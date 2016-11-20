#ifndef MAIN_H_
#define MAIN_H_

struct user
{
	char name[20];
	char passwd[20];
};

struct userLink
{
	struct user data;
	struct userLink* next;	
};

struct uni
	{
		int fd;
		struct userLink* userHead;
		struct onLineLink* onLineHead;
	};

#endif
