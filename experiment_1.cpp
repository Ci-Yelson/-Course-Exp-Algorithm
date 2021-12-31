/**
 * 【实验1-棋盘覆盖】
 * 
*/
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

#define ll long long
const int N=1e3+100,w=5;
ll k,x,y,alen;
int mp[N][N];
int num;

void gotoxy(short int x, short int y) {					//移动光标【用于命令行可视化】
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void print(int n)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(mp[i][j]==-1)
            {
                SetConsoleTextAttribute(hOut,0x0E);
                cout << setw(w) << '#';
                SetConsoleTextAttribute(hOut,0x0F);
            }else if(mp[i][j]==num)
            {
                SetConsoleTextAttribute(hOut,0x09);
                cout << setw(w) << mp[i][j];
                SetConsoleTextAttribute(hOut,0x0F);
            }else
            {
                cout << setw(w) << mp[i][j];
            }
            if(j==n) cout<<endl;
        }
}

void draw(int x,int y,int nx,int ny)
{
    ++num;
    for(int i=0;i<=1;i++)
        for(int j=0;j<=1;j++)
            if(nx+i!=x || ny+j!=y)
                mp[nx+i][ny+j]=num;
    gotoxy(0,0);
    print(alen);
    Sleep(500);
}

/**
 * 核心函数
*/
void divide_conquer(int n,int px,int py,int nx,int ny)
{
    if(n==1)
    {
        draw(px,py,nx,ny); //骨牌覆盖
        return ;
    }
    int len=1<<n-1,flag=0;
    int x[5],y[5];
    x[1]=nx+len-1,  y[1]=ny+len-1;
    x[2]=nx+len-1,  y[2]=ny+len;
    x[3]=nx+len,    y[3]=ny+len-1;
    x[4]=nx+len,    y[4]=ny+len;

    //area1
    if(nx<=px && px<=nx+len-1 && ny<=py && py<=ny+len-1)
        flag=1;
    //area2
    else if(nx<=px && px<=nx+len-1 && ny+len<=py && py<=ny+2*len-1)
        flag=2;
    //area3
    else if(nx+len<=px && px<=nx+2*len-1 && ny<=py && py<=ny+len-1)
        flag=3;
    //area4
    else if(nx+len<=px && px<=nx+2*len-1 && ny+len<=py && py<=ny+2*len-1)
        flag=4;

    int dx,dy;
    for(int i=1;i<=4;i++)
        if(flag==i) 
            dx=x[i],dy=y[i],x[i]=px,y[i]=py;
    draw(dx,dy,nx+len-1,ny+len-1);

    divide_conquer(n-1,x[1],y[1],nx,ny);
    divide_conquer(n-1,x[2],y[2],nx,ny+len);
    divide_conquer(n-1,x[3],y[3],nx+len,ny);
    divide_conquer(n-1,x[4],y[4],nx+len,ny+len);
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>k>>x>>y;
    system("cls");
    alen=1<<k;
    for(int i=1;i<=alen;i++)
        for(int j=1;j<=alen;j++)
            mp[i][j]=0;
    mp[x][y]=-1;
    divide_conquer(k,x,y,1,1);

    return 0;
}