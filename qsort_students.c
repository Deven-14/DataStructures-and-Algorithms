#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct student
{
	int roll;
	char name[50];
	float percentage;
}Student;
int input_no_of_students()
{
    int a;
    printf("Enter the number of studnets:\n");
    scanf("%d",&a);
    return a;
}
void input_ele(int n,Student s[n])
{
	for(int i=0;i<n;i++)
	{
		printf("Enter student %d's roll number, name and percentage :\n",i);
		scanf("%d %s %f",&s[i].roll,s[i].name,&s[i].percentage);
	}
}
int cmproll(const void *x,const void *y)
{
	int a=((Student *)x)->roll; //Student *p; then p->roll;
	int b=((Student *)y)->roll;
	return a-b;
}
int cmpname(const void *x,const void *y)
{
	return strcmp(((Student *)x)->name,((Student *)y)->name);
}
int cmp_percentage(const void *x,const void *y)
{
	return ((Student *)y)->percentage-((Student *)x)->percentage;// decending order
}
void sort(int n,Student s[n])
{
	char ch;
	printf("Sort according to Roll number(R)/Name(N)/Percentage(P)?\n");
	scanf(" %c",&ch);
	if(ch=='R')
		qsort(s,n,sizeof(s[0]),cmproll);
	else if(ch=='N')
		qsort(s,n,sizeof(s[0]),cmpname);
	else
		qsort(s,n,sizeof(s[0]),cmp_percentage);
}
void output(int n,Student s[n])
{
	printf("The order after sorting is:\nRoll number - Name - Percentage\n");
	for(int i=0;i<n;i++)
		printf("%d %s %f\n",s[i].roll,s[i].name,s[i].percentage);
}
int main()
{
    int n;
    n=input_no_of_students();
    Student s[n];
    input_ele(n,s);
    sort(n,s);
    output(n,s);
    return 0;
}
