#include<bits/stdc++.h>
#define allof(a)        a.begin(),a.end()
#define int             long long
#define fi              first
#define se              second
#define pb              push_back
#define F(i,a,b)        for(int i=a;i<=b;i++)
#define D(i,a,b)        for(int i=a;i>=b;i--)
#define inf             0x3f3f3f3f3f3f3f3f
#define mn              100001
#define task            "kosaraju"
using namespace std;
const int mod=          1e9+7;
typedef pair<int,int>   ii;
typedef pair<int,ii>    ip;

int n,m;
vector<int>adj[mn];
vector<int>rev[mn];
vector<int>post;//hold all verticles of the graph in post_order
bool vs[mn];
int scc[mn],cnt=0;

void prevs(int u){
    vs[u]=1;
    for(auto v:adj[u])if(!vs[v])
        prevs(v);
    post.emplace_back(u);
}

void dfs(int u){
    scc[u]=cnt;
    for(int v:rev[u])if(!scc[v])
        dfs(v);
}
void kosaraju(){
    F(i,1,n)if(!vs[i])prevs(i);
    for(auto it=post.rbegin();it!=post.rend();it++)
        if(!scc[*it])
            ++cnt,dfs(*it);
}
int32_t main()
{
    ios::sync_with_stdio(0);
    #ifdef _TPR_
        freopen("t.inp","r",stdin);
        freopen("t.out1","w",stdout);
    #endif
    cin>>n>>m;
    while(m--){
        int u,v;cin>>u>>v;
        adj[u].pb(v);
        rev[v].pb(u);
    }
    kosaraju();
} 