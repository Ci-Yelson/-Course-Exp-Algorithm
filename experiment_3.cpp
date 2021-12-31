/**
 * 【实验3-最长公共子序列】
 * 
 * LCS
 * 状态转移方程
 * 1.dp[i][j] = dp[i-1][j-1]+1, if x[i]==y[j]
 * 2.dp[i][j] = max({dp[i-1][j], dp[i][j-1]}), if x[i]!=y[i] 
*/

#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int N=5e3+100;
ll t,n,m;
char x[N],y[N];
ll dp[N][N],trans[N][N];
pair<int,char> mark[N][N];
ll LEN;
unordered_map<string,int> zs; //哈希表，用于给所有LCS去重

void dfs(string &cur,int px,int py,int pl) //搜索所有LCS
{
    if(pl==LEN)
    {
        // for(int i=0;i<LEN;i++) cout<<cur[i]<<(i==LEN-1?"\n":" ");
        zs[cur]=1;
        return ;
    }
    for(int i=px;i<=m;i++)
    {
        for(int j=py;j<=n;j++)
        {
            if(mark[i][j].first==pl+1)
            {
                cur.push_back(mark[i][j].second);
                dfs(cur,i+1,j+1,pl+1);
                cur.pop_back();
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>t;
    for(int ct=1;ct<=t;ct++)
    {
        cin>>m>>n;
        cout<<"Case "<<ct<<"\n";
        for(int i=1;i<=m;i++) cin>>x[i];
        for(int i=1;i<=n;i++) cin>>y[i];

        zs.clear();
        for(int i=1;i<=m;i++)
            for(int j=1;j<=n;j++)
                mark[i][j]={0,0};

        for(int i=1;i<=m;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(x[i]==y[j])
                {
                    dp[i][j]=dp[i-1][j-1]+1;
                    mark[i][j]={dp[i][j],x[i]}; //标记转移点，用于搜索LCS
                    trans[i][j]=1;
                }
                else
                {
                    if(dp[i-1][j] > dp[i][j-1]) trans[i][j]=2;
                    if(dp[i-1][j] < dp[i][j-1]) trans[i][j]=3;
                    if(dp[i-1][j] == dp[i][j-1]) trans[i][j]=4;
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }

        //LCS_len
        LEN=dp[m][n];
        cout<<"LCS Length: "<<LEN<<"\n";

        //ALL_LCS (with duplication)
        string str;
        dfs(str,0,0,0);
        //no duplication
        for(auto z:zs) for(int i=0;i<LEN;i++) cout<<z.first[i]<<(i==LEN-1?"\n":" ");

        //dp_table
        cout<<"\n>:Table_dp\n";
        for(int i=0;i<=m;i++)
            for(int j=0;j<=n;j++)
                cout<<dp[i][j]<<(j==n?"\n":" ");
            
        //trans_table
        cout<<"\n>:Table_trans\n";
        for(int i=0;i<=m;i++)
            for(int j=0;j<=n;j++)
                cout<<trans[i][j]<<(j==n?"\n":" ");
    }

    return 0;
}

/*
TEST DATA:
2
7 6
A B C B D A B
B D C A B A
8 9
b a a b a b a b
a b a b b a b b a
*/