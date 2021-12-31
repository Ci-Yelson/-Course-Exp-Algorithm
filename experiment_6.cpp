/**
 * 【实验6-跳马问题】
 * 给定8*8方格棋盘，求棋盘上一只马从一个位置到达另一位置的最短路径长。
 * 注意马是走“日”形的。
*/
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

#define pi pair<int,int>
const int N=10,w=5,inf=1e9;
bool vis[N][N];
int dis[N][N];
int sx,sy,tx,ty;

//============命令行输出相关=============
void gotoxy(short int x, short int y) {					//移动光标【用于命令行可视化】
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void print()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            if(i==sx && j==sy)  //起点
            {
                SetConsoleTextAttribute(hOut,0x0E);
                cout << setw(w) << 'S';
                SetConsoleTextAttribute(hOut,0x0F);
            }else if(i==tx && j==ty)    //终点
            {
                SetConsoleTextAttribute(hOut,0x0E);
                cout << setw(w) << (dis[i][j]==inf? 'T':(char)(dis[i][j]+'0'));
                SetConsoleTextAttribute(hOut,0x0F);
            }else if(dis[i][j]==inf)
            {
                SetConsoleTextAttribute(hOut,0x09);
                cout << setw(w) << "inf";
                SetConsoleTextAttribute(hOut,0x0F);
            }else
            {
                cout << setw(w) << dis[i][j];
            }
            if(j==N-1) cout<<endl;
        }
}

//八个方向
int dx[]={1,2,-1,-2,1,2,-1,-2};
int dy[]={2,1,2,1,-2,-1,-2,-1};

struct node
{
    int x,y,dis;
};

//============BFS=============
void solve_bfs()
{
    queue<node> q;
    dis[sx][sy]=0;
    q.push({sx,sy,0});
    vis[sx][sy]=1;
    while(q.size())
    {
        node cur=q.front(); q.pop();
        dis[cur.x][cur.y]=cur.dis;
        //命令行-执行过程可视化
        // gotoxy(0,0);
        // print();
        // Sleep(100);
        if(cur.x==tx && cur.y==ty) break;   //已找到跳出
        for(int i=0;i<8;i++)
        {
            int vx=cur.x+dx[i],vy=cur.y+dy[i];
            if( !(0<=vx && vx<=7 && 0<=vy && vy<=7) ) continue; //边界判断
            if(vis[vx][vy]) continue;
            vis[vx][vy]=1;
            q.push({vx,vy,cur.dis+1});
        }
    }
}

//============A*=============
struct node2
{
    int x,y,dis;
    double hs;
    node2(int _x,int _y,int _dis,double _hs):x(_x),y(_y),dis(_dis),hs(_hs) {};
    bool operator>(const node2 & a) const
    {
        return hs>a.hs; 
    }
};

//启发函数-代价采用当前点到终点的欧几里得距离
double distance(int x1,int y1,int x2,int y2) 
{
    double dx=abs(x1-x2);
    double dy=abs(y1-y2);
    return sqrt(dx*dx+dy*dy);
}

void solve_Astar()
{
    priority_queue<node2,vector<node2>,greater<node2>> q; //小根堆
    dis[sx][sy]=0;
    q.push({sx,sy,0,0});
    vis[sx][sy]=1;
    while(q.size())
    {
        node2 cur=q.top(); q.pop();
        dis[cur.x][cur.y]=cur.dis;
        if(cur.x==tx && cur.y==ty) break;
        for(int i=0;i<8;i++)
        {
            int vx=cur.x+dx[i],vy=cur.y+dy[i];
            if( !(0<=vx && vx<=7 && 0<=vy && vy<=7) ) continue; //边界判断
            if(vis[vx][vy]) continue;
            vis[vx][vy]=1;
            q.push({vx,vy,cur.dis+1,distance(vx,vy,tx,ty)});
        }
    }
}


int main()
{
    string s,t;
    while(cin>>s>>t)
    {
        sx=s[0]-'a',sy=s[1]-'1',tx=t[0]-'a',ty=t[1]-'1';
        for(int i=0;i<N;i++) for(int j=0;j<N;j++) dis[i][j]=inf,vis[i][j]=0;    //初始化

        cout<<">:BFS\n";
        solve_bfs();
        print();    //打印执行结果

        for(int i=0;i<N;i++) for(int j=0;j<N;j++) dis[i][j]=inf,vis[i][j]=0;    //初始化
        cout<<">:A*\n";
        solve_Astar();
        print();    //打印执行结果
        
        cout<<s<<"==>"<<t<<": "<<dis[tx][ty]<<" moves\n";
    }

    return 0;
}

/*
TEST DATA:
a1 a2
a1 a3
a1 h8
g2 b8
*/