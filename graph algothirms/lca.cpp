#include<bits/stdc++.h>
#define int             long long
#define inf             0x3f3f3f3f
#define infl            0x3f3f3f3f3f3f3f3f
#define fi              first
#define se              second
#define pb              push_back
#define F(i,a,b)        for(int i=a;i<=b;i++)
#define D(i,a,b)        for(int i=a;i>=b;i--)
#define ret             return
using namespace         std;
typedef pair<int,int>   ii;
int n,q;
vector<ii>adj[100001];

int vs[100001];
int h[100001];
int p[100001][21];
int emax[100001][21],emin[100001][21];
void dfs(int u)
{
    vs[u]=1;
    for(auto k:adj[u])
    {
        int v,w;tie(v,w)=k;
        if(!vs[v]){p[v][0]=u;h[v]=h[u]+1;dfs(v);}
    }
}

namespace LCA
{
    void process()
    {
        memset(emax,-1,sizeof(emax));
        memset(emin,0x3f,sizeof(emin));
        F(j,1,20)F(i,1,n)p[i][j]=p[p[i][j-1]][j-1];
    }
    int lca(int u,int v)
    {
        if(h[u]<h[v])swap(u,v);
        int log=log2(h[u]);
        D(i,log,0)if(h[u]-(1<<i)>=h[v])u=p[u][i];
        if(u==v)ret u;
        D(i,log,0)if(p[u][i]!=p[v][i] && p[u][i]){u=p[u][i];v=p[v][i];}
        ret p[u][0];
    }
}
using namespace LCA;

int32_t main()
{
    ios::sync_with_stdio(0);
    #ifdef _TPR_
        freopen("t.inp","r",stdin);  
        freopen("t.out","w",stdout);
    #endif
    cin>>n;
    F(i,1,n-1)
    {
        int u,v,w;cin>>u>>v>>w;
        adj[u].pb({v,w});adj[v].pb({u,w});
    }
    dfs(1);process();
    cin>>q;
    while(q--)
    {
        int u,v;cin>>u>>v;
        cout<<lca(u,v)<<'\n';
    }
}