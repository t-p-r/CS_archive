#include<bits/stdc++.h>
using namespace std;

const int mn=2001,mk=10001;
const int mod=1e9+7;

template<typename t>
bool ckmin(t& target,const t& source){
    return target>source ? target=source,1 : 0;
}
template<typename t>
bool ckmax(t& target,const t& source){
    return target<source ? target=source,1 : 0;
}


int n,w;
int dp[mn][mk];
//dp[i][j]: maximum value possible with weight constraint j\
    when considering node from 1 to i (sorted by POST_ORDER)

int weight[mn],val[mn];

vector<int>adj[mn];
void dfs(int u,int pu){
    memcpy(dp[u],dp[pu],sizeof(dp[u]));
    for(int v:adj[u])dfs(v,u);
    for(int j=0;j+weight[u]<=w;j++)
        ckmax(dp[pu][j+weight[u]],dp[u][j]+val[u]);  
}
int32_t main()
{
    cin.tie(0)->sync_with_stdio(0);
    #ifdef _TPR_
        freopen("t.inp","r",stdin);
        freopen("t.out","w",stdout);
    #endif
    cin>>n>>w;
    memset(dp,-1,sizeof(dp));
    memset(dp[0],0,sizeof(dp[0]));

    for(int i=2,p;i<=n;i++){
        cin>>p;p++;
        cin>>weight[i]>>val[i];
        adj[p].emplace_back(i);
    }
    dfs(1,0);
    cout<<*max_element(dp[0],dp[0]+w+1);
}