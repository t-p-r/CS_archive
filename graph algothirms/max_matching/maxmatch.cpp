#include<bits/stdc++.h>
#define allof(a)        a.begin(),a.end()
#define int             long long
#define fi              first
#define se              second
#define pb              emplace_back
#define double          long double
#define F(i,a,b)        for(int i=a;i<=b;i++)
#define D(i,a,b)        for(int i=a;i>=b;i--)
#define inf             0x3f3f3f3f3f3f3f3f
#define mn              3001
#define task            "match1"
using namespace std;
const int mod=          1e9+7;
typedef pair<int,int>   ii;
typedef pair<int,ii>    ip;
int n,m;
int assign[mn],root=0;
int vs[mn];
vector<int>adj[mn];

bool dfs(int u)//assign u to another vertex on the other side
//current augmenting path starts from vertex (root)
{
    if(vs[u]==root)return false;// (u) has already been registered in the augmenting path
    vs[u]=root;//register (u) to the augmenting path
    for(int v:adj[u]){
        if(!assign[v] || dfs(assign[v])){//the path keeps augmenting until reaching an unassigned(free) vertex
            return assign[v]=u,true;
        }
    }
    return false;
}

int32_t main()
{
    ios::sync_with_stdio(0);
    #ifdef _TPR_
        freopen("t.inp","r",stdin);
        freopen("t.out","w",stdout);
    #endif
    cin>>n>>m;
    int u,v;
    while(cin>>u>>v)adj[u].pb(v);

    int res=0;
    F(i,1,n){
        root=i;
        res+=dfs(i); 
    }
    cout<<res<<'\n';
    F(i,1,m)if(int j=assign[i]){
        cout<<j<<' '<<i<<'\n';
    }
}