#include <stdio.h>

char (*pun)(int);



char dis(int a)
{
	char b;
	printf("this is a test\n");
	return b;
}

int main(void)
{
	int a;
	pun = dis;
	(*pun)(a);
	return 0;
}
