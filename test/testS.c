
#include<stdio.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

void handler(int signo)
{
	
}

int main(void)
{
	//int i = 0;
	signal(SIGSEGV,handler);
	char *p = 0x1;
	while(1)
	{	
		p++;
		printf("%p\n",p);
		printf("%u\n",*p);
		fflush(stdout);
		sleep(1);
	}
	return 0;
}
