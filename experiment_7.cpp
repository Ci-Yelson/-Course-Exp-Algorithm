/**
 * 【实验7-装载问题】
 * 有n个集装箱要装上2艘载重量分别为c1和c2的轮船，
 * 其中第i个集装箱的重量为wi，
 * 要求确定是否有一个合理的装载方案可将这个集装箱装上这2艘轮船。
 * 如果有，找出一种装载方案。
 * 
 * 【要求时间复杂度-O(2^n)】
*/
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int N=50,M=30000+100;
ll n,c1,c2,ct;
ll w[N];
ll bestw,sum=0;
string ans;
ll ians;

//=======solve01-01背包求出bestw，再DFS检验求方案-O(2^n)========
ll lbw;
bool isfd;
ll dp[M];
void dfs01(int p,string &vc,ll s1,ll s2)
{
    if(isfd) return ;
    if(s1>c1 || s2>c2) return ;
    if(p==n+1)
    {
        if(s1==lbw)  ans=vc,isfd=1,bestw=lbw;
        return ;
    }
    vc+='1'; dfs01(p+1,vc,s1+w[p],s2); vc.pop_back();
    vc+='0'; dfs01(p+1,vc,s1,s2+w[p]); vc.pop_back();
}

void solve01()   //dfs01，O(n*c1+2^n)
{
    for(int i=0;i<=c1;i++) dp[i]=0;
    //01背包
    for (int i = 1; i <= n; i++)                        //遍历每个物品
        for (int k = c1; k >= w[i]; k--)               //背包空间
            dp[k] = max(dp[k], dp[k - w[i]] + w[i]);
    lbw=dp[c1];
    
    ans="",bestw=-1;
    string tmp="";
    dfs01(1,tmp,0,0);
    if(bestw==-1)   cout<<"No\n";
    else            cout<<bestw<<" "<<ans<<"\n";
}

//=======solve0-状压DFS-O(2^n)========
void dfs0(int p,ll &vc,ll s1,ll s2,ll r)
{
    if(s1>c1 || s2>c2) return ;
    if(p==n+1)
    {
        if(s1>bestw)    ians=vc,bestw=s1;
        return ;
    }
    if(r+s1<bestw) return ;
    r-=w[p];
    vc+=1<<(p-1); dfs0(p+1,vc,s1+w[p],s2,r);
    vc-=1<<(p-1); dfs0(p+1,vc,s1,s2+w[p],r);
}

void solve0()   //dfs0，
{
    ians=0,bestw=-1;
    ll vc=0;
    dfs0(1,vc,0,0,sum);
    ans="";
    for(int i=1;i<=n;i++) ans+='0'+(ians>>(i-1)&1);
    if(bestw==-1)   cout<<"No\n";
    else            cout<<bestw<<" "<<ans<<"\n";
}

//=======solve1-基础暴力DFS-O(n2^n)========
void dfs(int p,string &vc,ll s1,ll s2)
{
    if(s1>c1 || s2>c2) return ;
    if(p==n+1)
    {
        if(s1>bestw)        ans=vc,bestw=s1;
        // else if(s1==bestw)  ans=max(ans,vc);
        return ;
    }
    vc+='1'; dfs(p+1,vc,s1+w[p],s2); vc.pop_back();
    vc+='0'; dfs(p+1,vc,s1,s2+w[p]); vc.pop_back();
}

void solve1()   //dfs，O(n2^n)
{
    ans="",bestw=-1;
    string tmp="";
    dfs(1,tmp,0,0);
    if(bestw==-1)   cout<<"No\n";
    else            cout<<bestw<<" "<<ans<<"\n";
}

//=======solve2========
void solve2()   //状压写法，O(n2^n)
{
    bestw=-1,ans="";
    for(int i=0;i<(1<<n);i++)
    {
        ll s1=0,s2=0;
        string cur="";
        for(int j=0;j<n;j++)
            if(i>>j&1)  s1+=w[j+1], cur+='1';
            else        s2+=w[j+1], cur+='0';
        if(s1>c1 || s2>c2) continue;
        if(s1>bestw)        ans=cur,bestw=s1;
        else if(s1==bestw)  ans=max(ans,cur);
    }
    if(bestw==-1)   cout<<"No\n";
    else            cout<<bestw<<" "<<ans<<"\n";
}

int main()
{
    while(cin>>n)
    {
        sum=0;
        for(int i=1;i<=n;i++) cin>>w[i],sum+=w[i];
        cin>>c1>>c2;
        cout<<"Case "<<++ct<<"\n";

        cout<<">:Solve01-01背包:\n";
        solve01();

        cout<<">:Solve0-2^nDFS:\n";
        solve0();

        cout<<">:Solve0-2^nDFS:\n";
        solve1();
    }

    return 0;
}

/*
TEST DATA:
3
10 40 40
50 50
3
20 40 40
50 50
*/