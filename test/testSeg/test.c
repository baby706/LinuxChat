#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

int i = 0,j = 0;

void handler(int signo)
{
	printf("this is a segnaton error!\n");
	printf("i = %d,j = %d\n",i++,j);
	sleep(1);
}

int main()
{
	signal(SIGSEGV,handler);
	int* p = NULL;
	j++;
	*p = 0;
	
	
	return 0;
     
}
