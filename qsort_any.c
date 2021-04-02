#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int cmp(const void *x,const void *y)
{
    return strcmp(*(const char **)x,*(const char **)y);
}
void output(int n,char *s[])
{
    printf("The array elements after qsort are:\n");
    for(int i=0;i<n;i++)
        puts(s[i]);
}
int main(int argc,char *argv[])
{
    qsort(&argv[0],argc,sizeof(argv[0]),cmp);                                                                  // sizeof(char *) is same as sizeof(s[0]), and first argument can be &s[0] or s
    output(argc,argv);
    return 0;
}
