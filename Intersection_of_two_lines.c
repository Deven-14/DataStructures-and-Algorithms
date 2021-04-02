#include <stdio.h>
#define slope(x1,y1,x2,y2) (y2-y1)/(x2-x1)
#define y_intercept(x1,y1,m) (y1-m*x1)
typedef struct point
{
	float x;
	float y;
}Point;
typedef struct line 
{
	Point p1;
	Point p2;
}Line;
int input_n()
{
	int n;
	scanf("%d",&n);
	return n;
}
Point input_point()
{
	Point p;
	scanf("%f%f",&p.x,&p.y);
	return p;
}
void input_a_set_of_lines(Line l[2])
{
	int i;
	for(i=0;i<2;i++)
	{
		l[i].p1=input_point();
		l[i].p2=input_point();
	}
}
void input_all_sets_of_lines(int n,Line l[n][2])
{
	int i;
	for(i=0;i<n;i++)
		input_a_set_of_lines(l[i]);
}
Point point_of_intersection_of_two_line(Line l[2])
{
	//not checking for parallel lines
	Point p;
	float m1,m2,c1,c2;
	m1=slope(l[0].p1.x,l[0].p1.y,l[0].p2.x,l[0].p2.y);
	m2=slope(l[1].p1.x,l[1].p1.y,l[1].p2.x,l[1].p2.y);
	c1=y_intercept(l[0].p1.x,l[0].p1.y,m1);
	c2=y_intercept(l[1].p1.x,l[1].p1.y,m2);
	if(l[0].p2.x-l[0].p1.x==0)//checking if line 1 has slope infinity
	{
		p.x=l[0].p1.x;
		p.y=m2*p.x+c2;
		return p;
	}
	else if(l[1].p2.x-l[1].p1.x==0)//checking if line 2 has slope infinity
	{
		p.x=l[1].p1.x;
		p.y=m1*p.x+c1;
		return p;
	}
	else
	{
		p.x=(c1-c2)/(m2-m1);
		p.y=m1*p.x+c1;
	}
	return p;
}
void point_of_intersection_of_all_sets_of_lines(int n,Line l[n][2],Point p[n])
{
	int i;
	for(i=0;i<n;i++)
		p[i]=point_of_intersection_of_two_line(l[i]);
}
void output(int n,Point p[n])
{
	int i;
	for(i=0;i<n;i++)
		printf("(%f,%f)\n",p[i].x,p[i].y);
}
int main()
{
	int n;
	n=input_n();
	Line l[n][2];
	input_all_sets_of_lines(n,l);
	Point p[n];
	point_of_intersection_of_all_sets_of_lines(n,l,p);
	output(n,p);
	return 0;
}