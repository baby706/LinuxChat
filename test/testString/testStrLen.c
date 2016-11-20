#include <stdio.h>
#include <string.h>

int main(void)
{
	char ch[100] = "\0";
	//scanf("%s",ch);
	strcpy(ch,"hello\n\0");
	printf("strlen is %d\n",strlen(ch));
	
	return 0;
}
