#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<ctype.h>
#define WON 1
#define DRAW 0
#define player_no(x) (x%2==0)?2:1
//#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
typedef struct pos
{
	int row;
	int column;
}Pos;
typedef struct result
{
	int res;//result
	char ch;//who one the result
}Result;
COORD coord= {0,0}; // this is global variable
//center of axis is set to the top left cornor of the screen
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void Instructions()
{
	printf("--------Instructions--------\n");
	printf("Player 1 is X\nPlayer 2 is O\n");
}
void draw_board()
{
	int j;
	for(j=10; j<15; j++)
	{
		gotoxy(33,j);
		printf("|     |");
	}
	gotoxy(28,11);
	printf("-----------------");
	gotoxy(28,13);
	printf("-----------------");
}
void put_X_O(char ch,Pos p)
{
	int x,y;
	if(p.row==1)
		y=10;
	else if(p.row==2)
		y=12;
	else
		y=14;
	if(p.column==1)
		x=30;
	else if(p.column==2)
		x=36;
	else
		x=42;
	gotoxy(x,y);
	printf("%c",toupper(ch));
}
int check_win(char a[3][3])
{
	int i=2;
	//checking rows
	while(a[i][0]!=a[i][1] || a[i][0]!=a[i][2])
		i--;//doing in decreasing order because we can avoid i<n condition since a[negative number] doesn't exist the loop will break.
	if(i>-1 && (a[i][0]=='x' || a[i][0]=='o'))
		return WON;
	i=2;
	//checking columns
	while(a[0][i]!=a[1][i] || a[0][i]!=a[2][i])
		i--;
	if(i>-1 && (a[i][0]=='x' || a[i][0]=='o'))
		return WON;
	//checking crossways
	if((a[0][0]==a[1][1] && a[0][0]==a[2][2]) || (a[0][2]==a[1][1] && a[0][2]==a[2][0]))
		return WON;
	return DRAW;
}
void Re_Enter_data()
{
    gotoxy(28,19);
    printf("Re-Enter");
    Sleep(2000);
}
void clear_printed_data()
{
    gotoxy(28,19);
    printf("           ");
    gotoxy(28,22);
    printf("           ");
    gotoxy(28,0);
    printf("           ");
}
Result playtictactoe(char board[3][3])
{
	int turn=1;
	Result r={0,0};
	Pos p;
	gotoxy(28,20);
	printf("Player Number:\n");
	gotoxy(28,21);
    printf("Enter row and column:\n");
	while(turn<=9)
	{
        gotoxy(28+15,20);
        printf("%d",player_no(turn));
        gotoxy(28,22);
        scanf("%d%d",&p.row,&p.column);
        if(p.row>0 && p.row<4 && p.column>0 && p.column<4)
        {
            if(board[(p.row-1)][(p.column-1)]=='x' || board[(p.row-1)][(p.column-1)]=='0')
            {
                Re_Enter_data();
                clear_printed_data();
                continue;
            }
            if(turn%2==0)
                r.ch='o';
            else
                r.ch='x';
            board[(p.row-1)][(p.column-1)]=r.ch;
            put_X_O(r.ch,p);
            if(turn>4)
            {
                r.res=check_win(board);
                if(r.res==1)
                    return r;
            }
            turn++;
        }
        else
            Re_Enter_data();
        clear_printed_data();
    }
	return r;
}
void output_result(Result r)
{
    gotoxy(35,5);
	if(r.res==1)
		printf("%c is the winner",toupper(r.ch));
	else
		printf("DRAW");
}
int main()
{
	char board[3][3];
	Result r;
	Instructions();
	draw_board();
	r=playtictactoe(board);
	output_result(r);
	return 0;
}
