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
int n,m,q;
int t,u,v,k;

void op(const string ff)
{
    ios::sync_with_stdio(0);cin.tie(0);
    freopen((ff+".inp").c_str(),"r",stdin);
    freopen((ff+".out").c_str(),"w",stdout);
}
void init(){op((fopen("t.inp","r"))?"t":"ggez");}

struct segment_tree
{
    #define mid (l+r>>1)
    int st[200001]={},lazy[200001]={};
    void down(int id,int l,int r)
    {
        if(!lazy[id])return;
        st[id]+=lazy[id];
        if(l!=r)
        {
            lazy[2*id]+=lazy[id];
            lazy[2*id+1]+=lazy[id];
        }
        lazy[id]=0;
    }

    void update(int id,int l,int r,int u,int v,int val) 
    {
        down(id,l,r);
        if(v< l || r< u)return;
        if(u<=l && r<=v) 
        {
            lazy[id]+=val;
            down(id,l,r);
            return;
        }   
        update(2*id,l,mid,u,v,val);
        update(2*id+1,mid+1,r,u,v,val);
        st[id]=max(st[2*id],st[2*id+1]);
    }
    void update(int u,int v,int k){update(1,1,n,u,v,k);}

    int get(int id,int l,int r,int u,int v) 
    {
        down(id,l,r); 
        if(v< l || r< u)return -inf;
        if(u<=l && r<=v)return st[id];
        return max(get(2*id,l,mid,u,v),get(2*id+1,mid+1,r,u,v));
    }
    int get(int u,int v){return get(1,1,n,u,v);}
}st;

int32_t main()
{
    init();
    cin>>n>>m;
    while(m--)
    {
        cin>>t;
        if(!t){cin>>u>>v>>k;st.update(u,v,k);}
        else{cin>>u>>v;cout<<st.get(u,v)<<'\n';}
    }
}