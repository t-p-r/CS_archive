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

void spfa(int s)
{
    memset(d,63,sizeof(d));d[s]=0;vs[s]=1;
    deque<int>q;
    q.push_back(s);

    while(!q.empty())
    {
        int u=q.front();
        q.pop_front();vs[u]=0;
        for(auto i:adj[u])
        {
            int uv=i.fi,v=i.se;
            if(d[v]>d[u]+uv)
            {
                d[v]=d[u]+uv;
                if(!vs[v]){vs[v]=1;q.push_back(v);}
            }
        }
    }
}

int32_t main()
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
    spfa(1);
    cout<<"calculating time: "<<clock()-f<<'\n';
    F(i,1,n)cout<<i<<' '<<d[i]<<"\n";
}
