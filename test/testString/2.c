#include <stdio.h>

char *returnStr()
{
	char *p="hello world!";
	return p;
}
int main()
{
	char *str = NULL;//一定要初始化，好习惯
	str = returnStr();
	printf("%s\n", str);

	return 0;
} 
