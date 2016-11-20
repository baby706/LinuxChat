#include "base.h"
#include "menu.h"


int sockfd = -1;
DataPack buffer;

int main(int argc,char** argv)
{
	
	if(connectServer(argc,argv) == -1)
	{
		perror("connect error");
		exit(1);
	}
	else
	{
		mainMenu();
	}
	
	return 0;
}
