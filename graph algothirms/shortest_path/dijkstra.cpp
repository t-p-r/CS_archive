#include<bits/stdc++.h>
#define int             long long
#define fi              first
#define se              second
#define pb              push_back
#define F(i,a,b)        for(int i=a;i<=b;++i)
#define D(i,a,b)        for(int i=a;i>=b;--i)
using namespace         std;
typedef pair<int,int>   ii;
typedef pair<int,ii>    ip;
int n,m,s,t,delta;
vector<ii>adj[200001];
int d[200001];
bool vs[200001];

void op(const string ff)
{
    ios::sync_with_stdio(0);
    freopen((ff+".inp").c_str(),"r",stdin);
    freopen((ff+".out").c_str(),"w",stdout);
}
void init(){op((fopen("t.inp","r"))?"t":"metro");}
void dijkstra(int s)
{
    memset(d,63,sizeof(d));d[s]=0;
    priority_queue<ii,vector<ii>,greater<ii>>pq;
    pq.push({0,s});

    while(!pq.empty())
    {
        int du=pq.top().fi,u=pq.top().se;
        pq.pop();
        for(auto i:adj[u])
        {
            int uv=i.fi,v=i.se;
            if(d[v]>du+uv){d[v]=du+uv;pq.push({d[v],v});}
        }
    }
}

void dijkstra1(int s)
{
    memset(d,63,sizeof(d));d[s]=0;
    priority_queue<ii,vector<ii>,greater<ii>>pq;
    pq.push({0,s});

    while(!pq.empty())
    {
        int du=pq.top().fi,u=pq.top().se;
        d[u]=min(d[u],du);pq.pop();
        while(!adj[u].empty())
        {
            int v=adj[u].back().se,uv=adj[u].back().fi;
            adj[u].pop_back();
            pq.push({du+uv,v});
        }
    }
}

main()
{
    ios::sync_with_stdio(0);
    #ifdef _TPR_
        freopen("t.inp","r",stdin);  
        freopen("t.out","w",stdout);
    #endif
    cin>>n>>m;
    int u,v,w;
    while(m--)
    {
        cin>>u>>v>>w;
        adj[u].push_back({w,v});
        adj[v].push_back({w,u});
    }
    int f=clock();cout<<"input time: "<<f<<'\n';
    dijkstra(1);
    cout<<"calculating time: "<<clock()-f<<'\n';
    F(i,1,n)cout<<i<<' '<<d[i]<<"\n";
}
