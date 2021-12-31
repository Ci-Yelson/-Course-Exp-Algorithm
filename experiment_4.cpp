/**
 * 【实验4-哈夫曼编码】
 * 给定n个字母（或字）在文档中出现的频率序列X=<x1,x2,…,xn>，
 * 求出这n个字母的Huffman编码。
 * 为方便起见，以下将频率用字母出现的次数（或称权值）w1,w2,…,wn代替。
 * 
 * 要求：
 * 1. 左儿子标记为0，右儿子标记为1；
 * 2．左儿子的权值>=右儿子的权值；
 * 3．相同权值w的两个字母x、y，
 *    先输入权值的字母x的Huffman编码长度不超过后输入权值的字母y的Huffman编码长度。
 * 4．合并两个节点后新的权值应从右到左搜索、插入到相应的位置。
*/
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pi pair<ll,ll>
const int N=100;
ll T,n;
ll w[N];
vector<ll> e[40*N];
ll idx;

string ans[N];

void dfs(ll rt,string &cur)
{
    if(e[rt].size()==0)
    {
        ans[rt]=cur;
        return ;
    }
    cur+='0'; dfs(e[rt][0],cur); cur.pop_back();
    cur+='1'; dfs(e[rt][1],cur); cur.pop_back();
}

int main()
{
    cin>>T;
    for(int ct=1;ct<=T;ct++)
    {
        cout<<"Case "<<ct<<"\n";
        cin>>n;
        priority_queue<pi, vector<pi>, greater<pi>> q; //小根堆
        //插入负id，使得权值相等时，原字母序列下标大的排前面
        for(int i=1;i<=n;i++) cin>>w[i],q.push({w[i],-i}); 

        for(int i=1;i<=idx;i++) e[i].clear();
        idx=n;

        while(q.size()>1)
        {
            auto n1=q.top(); q.pop();
            auto n2=q.top(); q.pop();
            if(n1.first<n2.first) swap(n1,n2);
            //当权值相等时，选真实下标较小的作为左儿子
            if(n1.first==n2.first && abs(n1.second)>abs(n2.second)) 
                swap(n1,n2);
            idx++;
            e[idx].push_back(abs(n1.second));
            e[idx].push_back(abs(n2.second));
            //合并节点插入正id，使得权值相等时，新插入节点排后面
            q.push({n1.first+n2.first,idx});
        }

        string tmp="";
        dfs(idx,tmp);
        for(int i=1;i<=n;i++) cout<<w[i]<<" "<<ans[i]<<"\n";
        cout<<"\n";
    }

    return 0;
}