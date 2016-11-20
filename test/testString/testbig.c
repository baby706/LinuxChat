#include <stdio.h>

int main(void)
{
	int a = 0x41424344;
	char *p = &a;
	char b[4];
	for(int i = 0;i<4;i++)
	{
		b[i] = *p;
		p++;
		printf("%c",b[i]);
	}
	printf("\n");
	return 0;
}
