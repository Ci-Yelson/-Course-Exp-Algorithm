/**
 * 【实验2-矩阵连乘】
 * 
 * 状态转移方程
 * dp[i][j] = 
 * 1.0, i==j;
 * 2.min({ dp[i][k] + dp[k+1][j] + p[i-1]*p[k]*p[j] }), i<=k<j;
*/


#include<bits/stdc++.h>
using namespace std;

#define ll long long
const ll N=1e3+10,inf=1e18;
int n,t;
int p[N];       //p[]数组：矩阵的阶数
ll dp[N][N];    //dp数组：dp[i][j]表示起点为i，终点为j时的最少乘法次数
int mk[N][N];   //mk数组：mk[i][j]表示起点为i，终点为j时的分割点，用于输出方案
int mt[N];      //方案标记数组：mt[i]>0表示此处需填|mt[i]|个'('；mt[i]<0表示此处需填|mt[i]|个')'.

//递归获取方案
void getMethod(int l,int r,int k)
{
    if(l==r) return ;
    //分割点标记
    mt[l]+=1,mt[k]-=1;
    mt[k+1]+=1,mt[r]-=1;
    //递归分割后的左区间和右区间
    getMethod(l,k,mk[l][k]);
    getMethod(k+1,r,mk[k+1][r]);
}

//区间DP
void solve()
{
    //第一次枚举区间长度
    for(int l=1;l<n;l++)
    {
        //第二层枚举区间起点
        for(int i=1;i+l<=n;i++)
        {
            int j=i+l;
            dp[i][j]=inf;
            int mid=0;
            //第三层枚举分割点
            for(int k=i;k<j;k++)
            {
                ll val = dp[i][k] + dp[k+1][j] + p[i-1]*p[k]*p[j];
                //更新答案
                if(val<dp[i][j]) 
                    mid=k,dp[i][j]=val;
            }
            //记录分割点            
            mk[i][j]=mid;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    while(cin>>n)
    {
        for(int i=0;i<=n;i++) cin>>p[i],mt[i]=0;
        solve();
        getMethod(1,n,mk[1][n]);

        cout<<"Case "<<++t<<"\n";
        cout<<dp[1][n]<<" ";
        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<mt[i];j++) cout<<"(";
            cout<<"A"<<i;
            for(int j=0;j<-mt[i];j++) cout<<")";
        }
        cout<<"\n";
    }

    return 0;
}

/*
TEST DATA:
3
10 100 5 50
4
50 10 40 30 5
*/