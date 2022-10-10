#include<bits/stdc++.h>
#define allof(a)        a.begin(),a.end()
#define ll              long long
#define fi              first
#define se              second
#define pb              emplace_back
#define F(i,a,b)        for(int i=a;i<=b;i++)
#define D(i,a,b)        for(int i=a;i>=b;i--)
#define inf             0x3f3f3f3f3f3f3f3f
#define mn              100001
#define task            "holiday"
using namespace std;
const int mod=          1337377;
typedef pair<int,int>   ii;
typedef pair<int,ii>    ip;

#ifdef _getchar_nolock
	#define getchar() 	_getchar_nolock()
	#define putchar(_c)	_putchar_nolock(_c)
#else
	#define getchar() 	getchar_unlocked()
	#define putchar(_c)	putchar_unlocked(_c)
#endif
int next_l()
{
	int cur=0;bool neg=0;
	register int c=getchar();
	while(c!='-' and (c<48 or c>57))c=getchar();
	if(c=='-')neg=1,c=getchar();
	for(;c>=48 and c<=57;c=getchar())cur=10*cur+c-48;
	return neg ? -cur : cur;
}
void printl(int k,char buf=0)
{
	bool neg=0;
	if(k<0)neg=1,k=-k;
	register int v[21];int cnt=0;
	while(k)v[++cnt]=((k%10)+'0'),k/=10;
	if(neg)putchar('-');if(!cnt)putchar('0');
	while(cnt)putchar(v[cnt--]);if(buf)putchar(buf);
}

int n,q;
int t[mn],h[mn],sz[mn];
int pos[mn],chain[mn];
vector<vector<int>>adj;
vector<vector<int>>a;

void prevs(int u,int pre)
{
	sz[u]=1;
	for(int v:adj[u])if(v!=pre)
		t[v]=u,h[v]=h[u]+1,prevs(v,u),sz[u]+=sz[v];
}
int cnt=1;
void dfs(int u,int pre)
{
	a[cnt].pb(u),chain[u]=cnt;
	int idx=-1,cur=-1;
	for(int v:adj[u])if(v!=pre && cur<sz[v])cur=sz[v],idx=v;
	if(idx!=-1)dfs(idx,u);
	for(int v:adj[u])if(v!=pre && v!=idx)++cnt,dfs(v,u);
}

int on[mn];
vector<set<ii>>blacks;
int32_t main()
{
    ios::sync_with_stdio(0);
    #ifdef _TPR_
        freopen("t.inp","r",stdin);
        freopen("t.out","w",stdout);
    #endif
	n=next_l(),q=next_l();
	adj.resize(n+1);a.resize(n+1);blacks.resize(n+1);
	F(i,2,n)
	{
		int u=next_l(),v=next_l();
		adj[u].pb(v);adj[v].pb(u);
	}
	prevs(1,-1);dfs(1,-1);
	F(i,1,q)
	{
		int type=next_l();
		if(type)
		{
			int v=next_l(),res=-1;
			while(v)
			{
				if(blacks[chain[v]].size())
				{
					int cand=blacks[chain[v]].begin()->se;
					if(h[cand]<=h[v])res=cand;
				}
				v=t[a[chain[v]][0]];
			}
			printl(res,'\n');
		}
		else
		{
			int i=next_l();
			if(!on[i])blacks[chain[i]].insert({h[i],i});
				else blacks[chain[i]].erase({h[i],i});
			on[i]^=1;
		}
	}
}