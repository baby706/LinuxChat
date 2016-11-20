#include <stdio.h>
#include <string.h>

int main(void)
{
	
	char buffer[1024];
	//bzero(buffer,1024);
	printf("please input some word:\n");
	//fgets(buffer,11,stdin);
	//printf("%d\n",strlen(buffer));
	//scanf("%s",buffer);
	fgets(buffer,sizeof(buffer),stdin);
	//write(1,buffer,sizeof(buffer));
	printf("%s",buffer);
	//int c = strcmp(buffer,"hello");
	
	//puts(buffer);
	
	return 0;
}
