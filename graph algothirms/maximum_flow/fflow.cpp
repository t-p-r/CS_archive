#include<bits/stdc++.h>
using namespace std;
using ii=pair<int,int>;

struct dinitz_impl{
    int start,dest;
    int t=0,edge_count=0;

    vector<int>d,num;
    vector<int>cap,flow;
    vector<vector<ii>>adj;
    vector<int>pos;

    dinitz_impl(int n,int m,int start,int dest):
        start(start),dest(dest),d(n+1),num(n+1),cap(2*m+1),flow(2*m+1),adj(n+1),pos(n+1){}

    int lim;
    bool bfs(int s,int t){
        fill(d.begin(),d.end(),0);
        queue<int>q;
        d[s]=1;q.emplace(s);

        while(q.size()){
            int u=q.front();q.pop();
            if(u==t)return true;

            for(const ii& k:adj[u]){
                int v,uv;tie(v,uv)=k;
                if(flow[uv]+lim<=cap[uv] && !d[v])
                    d[v]=d[u]+1,q.emplace(v);
            }
        }
        return false;
    }
    
    
    int dfs(int u,int cur_flow){
        if(u==dest)
            return cur_flow;
        if(num[u]!=t)
            num[u]=t;
        else
            return 0;
        
        for(;pos[u]<adj[u].size();pos[u]++){
            int v,uv;tie(v,uv)=adj[u][pos[u]];
            int vu=uv^1;// black magic
            if(flow[uv]<cap[uv] && num[v]!=t && d[v]==d[u]+1){
                int x=dfs(v,min(cur_flow,cap[uv]-flow[uv]));
                if(x)return flow[uv]+=x,flow[vu]-=x,x;
            }
        }
        return 0;
    }

    void add_edge(int u,int v,int w){
        adj[u].emplace_back(v,edge_count);
        adj[v].emplace_back(u,edge_count+1);
        cap[edge_count]+=w;edge_count+=2;
    }

    long long solve(){
        long long res=0;
        for(lim=(1<<30);lim>=1;){
            if(!bfs(start,dest)){
                lim>>=1;
                continue;
            }
            fill(pos.begin(),pos.end(),0);
            
            int x;
            do{
                t++,x=dfs(start,lim);
                res+=x;
            }
            while(x);
        }
        return res;
    }
};

int32_t main()
{
    cin.tie(0)->sync_with_stdio(0);
    #ifdef _TPR_
        freopen("t.inp","r",stdin);
        freopen("t.out","w",stdout);
    #endif

    int n,m;cin>>n>>m;
    dinitz_impl st(n,2*m,1,n);

    while(m--){
        int u,v,w;cin>>u>>v>>w;
        st.add_edge(u,v,w);
        st.add_edge(v,u,w);
    }
    return cout<<st.solve(),0;
}