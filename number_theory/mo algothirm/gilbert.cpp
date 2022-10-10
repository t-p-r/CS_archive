#include<bits/stdc++.h>
#define all(a)          a.begin(),a.end()
#define fi              first
#define se              second
#define pb              push_back
#define F(i,a,b)        for(int i=a;i<=b;i++)
#define D(i,a,b)        for(int i=a;i>=b;i--)
#define inf             0x3f3f3f3f
using namespace std;
using ii=pair<int,int>;
int n,m,s;
int a[30001];

inline int gilbertOrder(int x, int y, int pow, int rotate)
{
	if(!pow)return 0;
	int hpow=1<<(pow-1);
	int seg=(x<hpow) ?((y<hpow) ?0 :3) :((y<hpow) ?1 :2);
	seg=(seg+rotate)&3;
	const int rotateDelta[]={3,0,0,1};
	int nx=x&(x^hpow),ny=y&(y^hpow);
	int nrot=(rotate+rotateDelta[seg])&3;
	int subSquareSize=1<<(2*pow-2);
	int ans=seg*subSquareSize;
	int add=gilbertOrder(nx,ny,pow-1,nrot);
	ans+=(seg==1 || seg==2) ?add :(subSquareSize-add-1);
	return ans;
}

struct query
{
    int u,v,tt,cal;
    bool operator<(const query& k){return cal<k.cal;}
}q[200001];

struct obj
{
    int cnt=0;
    int c[1000001];
    void insert(int g){if(!c[g])++cnt;c[g]++;}
    void erase(int g){c[g]--;if(!c[g])--cnt;}
    void create(int l,int r){F(i,l,r)insert(a[i]);}
    void move(int l1,int r1,int l2,int r2)
    {
        int u=min(l1,l2),v=max(r1,r2);
        D(i,l1-1,u)insert(a[i]);
        F(i,r1+1,v)insert(a[i]);
        F(i,u,l2-1)erase(a[i]);
        D(i,v,r2+1)erase(a[i]);
    }
}st;
 
int32_t main()
{
    ios::sync_with_stdio(0);
    #ifdef _TPR_
        freopen("t.inp","r",stdin);  
        freopen("t.out","w",stdout);
    #endif
    cin>>n;s=sqrt(n);
    F(i,1,n)cin>>a[i];
    cin>>m;
    F(i,1,m)
    {
        cin>>q[i].u>>q[i].v;q[i].tt=i;
        q[i].cal=gilbertOrder(q[i].u,q[i].v,21,0);
    }
    sort(q+1,q+m+1);
    vector<int>res(m+1);
    st.create(q[1].u,q[1].v);res[q[1].tt]=st.cnt;
    F(i,2,m)
    {
        int u=q[i].u,v=q[i].v;
        st.move(q[i-1].u,q[i-1].v,u,v);
        res[q[i].tt]=st.cnt;
    }
    F(i,1,m)cout<<res[i]<<'\n';
}