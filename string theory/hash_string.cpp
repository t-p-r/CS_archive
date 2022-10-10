#include<bits/stdc++.h>
#define file    "hash_string."
#define int     long long
#define ii      pair<int , int>
#define fi      first
#define se      second
#define pb      push_back
#define F(i,a,b)  for(int i= (a); i<= (b);i++)
#define Fr(i,a,b) for(int i= (a); i<  (b);i++)
#define D(i,a,b)  for(int i= (a); i>= (b);i--)
using namespace std;
const int inf = 1e9+7,bs=311,md=1610612741;
int n,m,hs_w=0;
int p[1000001],hs[1000001];
string s,w;

void init()
{
    if(fopen("t.inp","r"))
    {
        freopen("t.inp","r",stdin);
        freopen("t.out","w",stdout);
    }
    else
    {
        freopen(file"inp","r",stdin);
        freopen(file"out","w",stdout);
    }
}
void build_base()
{p[0]=1;F(i,1,n)p[i]=(p[i-1]*bs)%md;}
void build_hash()
{F(i,1,n)hs[i]=(hs[i-1]*bs+s[i])%md;}
int get_hs(int i,int j)
{return (hs[j]-hs[i-1]*p[j-i+1]+md*md)%md;}
int hash_code(string w)
{
    int hs_w=0,m=s.size();
    w='.'+w;
    F(i,1,m)hs_w=(hs_w*bs+w[i])%md;
    return hs_w;
}
void solve()
{
    cin>>s>>w;
    n=s.size(),m=w.size();
    s='.'+s;w='.'+w;
    build_base();build_hash();
    F(i,1,m)hs_w=(hs_w*bs+w[i])%md;
    F(i,1,n)cout<<get_hs(i,i)<<' ';cout<<'\n';
    F(i,1,n-m+1)if(hs_w==get_hs(i,i+m-1))cout<<i<<' ';
}

main()
{
    init();
    solve();
}