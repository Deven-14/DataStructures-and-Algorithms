#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int input_no_of_str()
{
    int a;
    printf("Enter the number of strings:\n");
    scanf("%d",&a);
    return a;
}
void input_ele(int n,char *s[n])
{
	for(int i=0;i<n;i++)
		s[i]=(char *)malloc(50*sizeof(char));
    printf("Enter the strings:\n");
    for(int i=0;i<n;i++)
        scanf("%s",s[i]);
}
int cmpstr(const void *x,const void *y)
{
	return strcmp(*(const char **)x,*(const char **)y);
}
void output(int n,char *s[n])
{
	printf("The array elements after qsort are:\n");
	for(int i=0;i<n;i++)
		puts(s[i]);
	for(int i=0;i<n;i++)
	{
		free(s[i]);
		s[i]=NULL;
	}
}
int main()
{
    int n;
    n=input_no_of_str();
    char *s[n];                                                                                            //s is the name of the pointer as well as the string name, that's y 1st argument in qsort is &s[0] and in puts we no need to use *s[i], just s[i]
    input_ele(n,s);
    qsort(s,n,sizeof(char *),cmpstr);                                                                  // sizeof(char *) is same as sizeof(s[0]), and first argument can be &s[0] or s
    output(n,s);
    return 0;
}
