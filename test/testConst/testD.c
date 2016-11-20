/*************************************************************************
	> File Name: testD.c
	> Author: Liang Bo
	> Mail: cs-b@163.com 
	> Function: 
	> Created Time: 2016年09月28日 星期三 13时39分56秒
 ************************************************************************/

#include<stdio.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
void handler(int s)
{
	    printf("出现了段错误！\n");  
	    exit(1);
}
int main()
{
	    int *p = NULL;
	    signal(SIGSEGV,handler);
	    *p = 0;
	    return 0;
}
