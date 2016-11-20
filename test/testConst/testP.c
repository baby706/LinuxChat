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
