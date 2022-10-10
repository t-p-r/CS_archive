#include<bits/stdc++.h>
#define int             long long
using namespace std;

const int mm=20001;

template<typename t>
bool ckmax(t& target,const t& source){
    return target<source ? target=source,1 : 0;
}
template<typename t>
bool ckmin(t& target,const t& source){
    return target>source ? target=source,1 : 0;
}

int n,m;
vector<int>w(1),v(1);
int dp[mm];

int32_t main()
{
    cin.tie(0)->sync_with_stdio(0);
    #ifdef _TPR_
        freopen("t.inp","r",stdin);
        freopen("t.out","w",stdout);
    #endif
    cin>>n>>m;

    for(int i=1;i<=n;i++){
        int count,weight,val;cin>>weight>>val>>count;
        int k=1;
        while(count>=k){
            w.emplace_back(k*weight);
            v.emplace_back(k*val);
            count-=k;k*=2;
        }
        if(count){
            w.emplace_back(count*weight);
            v.emplace_back(count*val);
        }
    }
    n=w.size()-1;

    for(int i=1;i<=n;i++)
        for(int j=m;j>=w[i];j--)
            ckmax(dp[j],dp[j-w[i]]+v[i]);

    cout<<dp[m];
}