#include<vector>
#include<queue>
#include<tuple>
using namespace std;
using ii=pair<int,int>;

struct dinitz_impl{
    vector<vector<ii>>adj;  // adjacency list
    vector<int>cap,flow;    // capacity and current flow through each edge
    vector<int>d;           // height of node after performing BFS in residual graph
    vector<int>num;         // used to denote current augmenting path
    vector<int>pos;
    // heuristical array, used so that no two augmenting path of the same residual graph shares an edge

    int start,dest;         // source and sink of the flow network
    int t=0;                // index of the current augmenting path, used along with the num[] array
    int edge_count=0;
    // Note: every main edge (u,v) whose index is 2*x have its back-edge (v,u) indexed 2*x+1
    // (see the add_edge() function).
    // This trivializes the act of finding the index of the reverse edge, that is
    // index(u,v) = index(v,u)^1.

    dinitz_impl(){}
    dinitz_impl(int n,int m,int start,int dest):
        adj(n+1),d(n+1),num(n+1),pos(n+1),cap(2*m+1),flow(2*m+1),start(start),dest(dest){}
    // not m, but 2*m, since each main edge have its back-edge

    void add_edge(int u,int v,int w){
        adj[u].emplace_back(v,edge_count);
        adj[v].emplace_back(u,edge_count+1);
        cap[edge_count]+=w;edge_count+=2;
    }

    // Attempt to construct the residual graph. Return true if that graph reaches t
    // (i.e an augmenting path exists).
    bool bfs(int s,int t,int lim){
        fill(d.begin(),d.end(),0);
        queue<int>q;
        q.emplace(s);d[s]=1;

        while(q.size()){
            int u=q.front();q.pop();
            if(u==t)return true;

            for(const ii& k:adj[u]){
                int v=k.first,uv=k.second;
                if(flow[uv]+lim<=cap[uv] && d[v]==0)
                    d[v]=d[u]+1,q.emplace(v);
            }
        }
        return false;
    }

    int dfs(int u,int cur_flow){
        if(u==dest)return cur_flow;
        if(num[u]!=t)num[u]=t;
        else return 0;

        for(;pos[u]<adj[u].size();pos[u]++){
            int v,uv;tie(v,uv)=adj[u][pos[u]];
            int vu=uv^1; // explained above

            if(flow[uv]<cap[uv] && num[v]!=t && d[v]==d[u]+1){
                int x=dfs(v,min(cur_flow,cap[uv]-flow[uv]));
                if(x)return flow[uv]+=x,flow[vu]-=x,x;
            }
        }

        return 0;
    }

    long long solve(){
        long long res=0;

        for(int lim=(1<<30);lim>=1;lim>>=1)while(bfs(start,dest,lim)){
            fill(pos.begin(),pos.end(),0);
            int x;
            do{
                t++,x=dfs(start,0x3f3f3f3f);
                res+=x;
            }while(x);
        }
        return res;
    }
}st;