#include<bits/stdc++.h>
#define allof(a)        a.begin(),a.end()
#define int             int64_t
#define fi              first
#define se              second
#define pb              push_back
#define F(i,a,b)        for(int i=a;i<=b;i++)
#define D(i,a,b)        for(int i=a;i>=b;i--)
#define inf             0x3f3f3f3f3f3f3f3f
#define mn              1000001
#define task            "lminmax"
#define mp              make_pair
using namespace std;
typedef pair<int,int>   ii;
int n,k;
int a[mn];
int l[mn];

void scan(int& number)
{
    number=0;
    register int c=getchar();
    while(c<48 || c>57)c=getchar();
    for(;c>=48 && c<=57;c=getchar())number=10*number+c-48;
}

deque<int>stmin,stmax;
int32_t main()
{
    ios::sync_with_stdio(0);
    #ifdef _TPR_
        freopen("t.inp","r",stdin);
        freopen("t.out","w",stdout);
    #else
        freopen(task".inp","r",stdin);
        freopen(task".out","w",stdout);
    #endif
    cin>>n>>k;
    F(i,1,n)cin>>a[i];
    F(i,1,n)
    {
        while(stmin.size() && a[stmin.back()]>a[i])stmin.pop_back();
        while(stmax.size() && a[stmax.back()]<a[i])stmax.pop_back();
        stmin.pb(i);stmax.pb(i);
        bool kt=0;int lim=i;
        while(a[stmax[0]]-a[stmin[0]]>k)
        {
            kt=1;
            if(stmin[0]<stmax[0])lim=stmin[0]+1,stmin.pop_front();
            else lim=stmax[0]+1,stmax.pop_front();
        }
        l[i]=(kt)?lim:max(1LL,l[i-1]);
    }
    int res=0;
    F(i,1,n)res=max(res,i-l[i]+1);
    cout<<res;
}