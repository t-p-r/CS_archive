#include<bits/stdc++.h>
#define allof(a)        a.begin(),a.end()
#define ll              long long
#define fi              first
#define se              second
#define pb              emplace_back
#define F(i,a,b)        for(int i=a;i<=b;i++)
#define D(i,a,b)        for(int i=a;i>=b;i--)
#define inf             0x3f3f3f3f
#define mn              100001
#define task            "holiday"
using namespace std;
const int mod=          1e9+7;
typedef pair<int,int>   ii;
typedef pair<int,ii>    ip;
int n,m;
int num[mn],low[mn];
int ap[mn];int bridges=0;
vector<int>adj[mn];

int cnt=0,root=-1,child=0;
void dfs(int u,int pre)
{
    num[u]=low[u]=++cnt;
    for(int v:adj[u])if(!num[v])
    {
        dfs(v,u);
        if(u==root)++child;
        low[u]=min(low[u],low[v]);
        if(low[v]>=num[u])ap[u]=1;
        if(low[v]>num[u])bridges++;
    }
    else if(v!=pre)low[u]=min(low[u],num[v]);
}
int32_t main()
{
	ios::sync_with_stdio(0);
    #ifdef _TPR_
        freopen("t.inp","r",stdin);  
        freopen("t.out","w",stdout);
    #endif
    cin>>n>>m;
    while(m--)
    {
        int u,v;cin>>u>>v;
        adj[u].pb(v);adj[v].pb(u);
    }
    F(i,1,n)if(!num[i])
    {
        root=i,child=0,dfs(i,-1);
        ap[i]=(child>1);
    }
    cout<<accumulate(ap+1,ap+n+1,0)<<' '<<bridges;
}
