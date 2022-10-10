#include<bits/stdc++.h>
using namespace std;

const int mn=1e5+11,inf=0x3f3f3f3f;
int n;
namespace matching{
    int pu[mn],pv[mn];
    int d[mn];
    vector<int>adj[mn];

    bool bfs(){
        queue<int>q;
        for(int u=1;u<=n;u++)if(pu[u]==0)
            d[u]=0,q.emplace(u);
        else d[u]=inf;

        d[0]=inf;
        while(q.size()){
            int u=q.front();q.pop();
            if(d[u]<d[0])
                for(int v:adj[u])if(d[pv[v]]==inf)
                    d[pv[v]]=d[u]+1,q.emplace(pv[v]);
        }

        return d[0]!=inf;
    }
    bool dfs(int u){
        if(u==0)return true;
        for(int v:adj[u])
            if(d[pv[v]]==d[u]+1 && dfs(pv[v]))
                return pv[v]=u,pu[u]=v,true;
        return d[u]=inf,false;
    }
    int execute(){
        memset(pu,0,sizeof(pu));
        memset(pv,0,sizeof(pv));
        int res=0;
        while(bfs())
            for(int u=1;u<=n;u++)if(pu[u]==0)
                res+=dfs(u);
        return res;
    }
}