#include<bits/stdc++.h>
#define allof(a)            a.begin(),a.end()
#define int                 long long
#define fi                  first
#define se                  second
#define pb                  push_back
#define F(i,a,b,k)          for(int i=a;i<=b;i+=k)
#define D(i,a,b,k)          for(int i=a;i>=b;i-=k)
#define lsb(i) (i&(-i))
#define inf                 0x3f3f3f3f3f3f3f3f
using namespace             std;
using ii=                   pair<int,int>;
using u128=                 __uint128_t;
int n,q;
int u,v;
int a[100001];
int t[100001];
int fen1[100001],fen2[100001];
// fen1[i] quản lý đọan [i-lsb(i)+1,i] ; fen2[i] quản lý đoạn [i,i+lsb(i)-1];
// point update,point query,range query (for everything)

void op(const string ff)
{
    ios::sync_with_stdio(0);
    freopen((ff+".inp").c_str(),"r",stdin);
    freopen((ff+".out").c_str(),"w",stdout);
}
void init(){op((fopen("t.inp","r"))?"t":"ggez");}

void update(int p,int val)
{
    a[p]=val;
    F(i,p,n,lsb(i))fen1[i]+=val;
    for(;p;p-=lsb(p))fen2[p]+=val;
}

int get(int p)
{
    int ans=0;
    for(;p;p-=lsb(p))ans+=fen1[p];
    return ans;
}

int get(int l,int r)
{
    int ans=0,i=l;
    while(i+lsb(i)<=r){ans+=fen2[i];i+=lsb(i);}
    i=r;
    while(i-lsb(i)>=l){ans+=fen1[i];i-=lsb(i);}
    return ans+a[i];
}

signed main()
{
    init();
    cin>>n>>q;
    F(i,1,n,1){cin>>a[i];t[i]=t[i-1]+a[i];}
    F(i,1,n,1)update(i,a[i]);
    F(i,1,q,1)
    {
        cin>>u>>v;
        cout<<get(u,v)<<'\n';
    }
}
