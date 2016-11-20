#include <stdio.h>
#include <malloc.h>


extern int*  a;

int main(void)
{
	int b;
	a = &b;
	printf("%p\n",a);
	return 0;
}
