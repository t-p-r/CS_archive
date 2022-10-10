#include<bits/stdc++.h>
#define allof(a)            a.begin(),a.end()
#define int                 long long
#define fi                  first
#define se                  second
#define pb                  push_back
#define F(i,a,b)            for(int i=a;i<=b;i++)
#define D(i,a,b)            for(int i=a;i>=b;i--)
#define inf                 0x3f3f3f3f3f3f3f3f
using namespace             std;
using ii=                   pair<int,int>;
using u128=                 __uint128_t;
int cnt=0;

int pow(int a,int b,int mod){
    int res=1;
    a%=mod;
    while(b){   
        if(b&1)res=(u128)res*a%mod;
        a=(u128)a*a%mod;
        b>>=1;
    }
    return res;
}

bool check_composite(int n,int a,int d,int s){
    int x=pow(a,d,n);
    if(x==1 || x==n-1)
        return false;
    for(int r=1;r<s;r++)
        if((x=(u128)x*x%n)==n-1)
            return false;
    return true;
};

bool isp(int n){
    if(n<2)return false;

    int r=0,d=n-1;
    while(!(d&1))
        d>>=1,r++;
    
    for(int a:{2,3,5,7,11,13,17,19,23,29,31,37}){
        if(n==(int32_t)n && a==11)break;
        if(n==a)return true;
        if(check_composite(n,a,d,r))return false;
    }
    return true;
    // deterministic for up to 64-bit numbers
}
int32_t main()
{
    ios::sync_with_stdio(0);
    #ifdef _TPR_
        freopen("t.inp","r",stdin);  
        freopen("t.out","w",stdout);
    #endif
    int res=0;
    F(i,1,1000000)res+=(isp(i));
    cout<<res;cerr<<clock();
}