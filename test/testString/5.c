#include <stdio.h>

//返回的是局部变量的地址，该地址位于动态数据区，栈里

char *s1()
{
	char* p1 = "qqq";//为了测试‘char p[]="Hello world!"’中的字符串在静态存储区是否也有一份拷贝
	char p[]="Hello world!";
	char* p2 = "w";//为了测试‘char p[]="Hello world!"’中的字符串在静态存储区是否也有一份拷贝
	printf("in s1 p=%p\n", p);
	printf("in s1 p1=%p\n", p1);
	printf("in s1: string's address: %p\n", &("Hello world!"));
	printf("in s1 p2=%p\n", p2);
	return p;
}

//返回的是字符串常量的地址，该地址位于静态数据区

char *s2()
{
	char *q="Hello world!";
	printf("in s2 q=%p\n", q);
	printf("in s2: string's address: %p\n", &("Hello world!"));
	return q;
}

//返回的是静态局部变量的地址，该地址位于静态数据区

char *s3()
{
	static char r[]="Hello world!";
	printf("in s3 r=%p\n", r);
	printf("in s3: string's address: %p\n", &("Hello world!"));
	return r;
}

int main()
{
	char *t1, *t2, *t3;
	t1=s1();
	t2=s2();
	t3=s3();

	printf("in main:");
	printf("p=%p, q=%p, r=%p\n", t1, t2, t3);

	printf("%s\n", t1);
	printf("%s\n", t2);
	printf("%s\n", t3);

	return 0;
}
