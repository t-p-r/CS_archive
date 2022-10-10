// Problem: Providing n points on a two-dimensional plane (n<=100000), find the MST connecting these points, with the distance between two points equates their Manhattan distance.
// Solution: Brute-force solutions enumerate all O(n^2) edges, however we can reduce that number to O(n).\
   That is, because, for every point P, we only need to care about the 8 closest points to P from each of the 8 octants created by lines x = P.x, y = P.y, x + y = P.x + P.y, and x - y = P.x - P.y
// Prove: Define Q is the closest point to P that belongs to the an octant. For every other point R in that octant, should we choose \
   PR as an edge in out MST, we can always choose a more optimal PQ or QR, since PQ <= PR (obviously) and QR <= PR (since they belong to the same octant).
// Implementations: By rotating the points around (0,0) by 90 degrees, clockwise or anti-clockwise, for a total of 3 times, we can cut the amount of octants that must be processed to 2. For example, points Q from the first octant (on the 10 o'clock corner) are bound by two below constraints: \
                                                    Q.x + Q.y <= P.x + P.y (1)\
                                                    Q.y       >= Q.x       (2)\
            and of all of those points, the closest point to P (denoted as Z) have Z.x - Z.y maximized.

#include<bits/stdc++.h>
#define int long long

using namespace std;
using ii=pair<int,int>;
using state=tuple<int,int,int>;

template<typename t>
bool ckmax(t& target,const t& source){
    return target<source ? target=source,1 : 0;
}

const int mn=1e5+11,inf=0x3f3f3f3f3f3f3f3f;

int n;
int x[mn],y[mn];
int dist(int i,int j){
    return abs(x[i]-x[j])+abs(y[i]-y[j]);
}

priority_queue<state,vector<state>,greater<state>>pq;
struct dsu{
    vector<int>p;
    dsu():p(mn,-1){}

    int find(int i){
        return p[i]<0 ? i : p[i]=find(p[i]);
    }
    bool merge(int u,int v){
        if((u=find(u))==(v=find(v)))return false;
        if(p[u]>p[v])swap(u,v);
        return p[u]+=p[v],p[v]=u,true;
    }
}st;

int kruskal(){
    int res=0;
    while(pq.size()){
        int w,u,v;tie(w,u,v)=pq.top(),pq.pop();
        if(st.merge(u,v))res+=w;
    }
    return res;
}

struct fenwick_tree{
    ii ft[mn];
    void clear(){
        memset(ft,0xc0,sizeof(ft));
    }
    fenwick_tree(){clear();}

    inline int lsb(int i){
        return i&(-i);
    }
    void update(int i,int val,int idx){
        for(;i<mn;i+=lsb(i))
            ckmax(ft[i],ii(val,idx));
    }
    ii get(int i){
        ii res(-inf,-inf);
        for(;i;i-=lsb(i))
            ckmax(res,ft[i]);
        return res;
    }
}ft;

int mxy[mn];
vector<int>vx,vy,vxy;
int32_t main()
{
    cin.tie(0)->sync_with_stdio(0);
    #ifdef _TPR_
        freopen("t.inp","r",stdin);
        freopen("t.out","w",stdout);
    #endif
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>x[i]>>y[i];

    for(int iter=1;iter<=4;iter++){
        vx.clear(),vy.clear(),vxy.clear();
        for(int i=1;i<=n;i++)
            vx.emplace_back(i),
            vy.emplace_back(i),
            vxy.emplace_back(i);
        sort(vxy.begin(),vxy.end(),[](int i,int j){return x[i]+y[i]<x[j]+y[j];});
        
        int cnt=1;
        for(int i=0;i<vxy.size();i++){
            mxy[vxy[i]]=cnt;
            if(i+1<vxy.size() && x[vxy[i]]+y[vxy[i]]!=x[vxy[i+1]]+y[vxy[i+1]])
                cnt++;
        }
        // for the first octant we sort indexes by increasing order of x[]+y[]
        ft.clear();
        sort(vy.begin(),vy.end(),[](int i,int j){
            if(y[i]==y[j])return x[i]<x[j];
            return y[i]>y[j];
        });
        for(int i:vy){
            int j=ft.get(mxy[i]).second;
            if(j!=-inf)
                pq.emplace(dist(i,j),i,j);
            ft.update(mxy[i],x[i]-y[i],i);
        }

        ft.clear();
        sort(vx.begin(),vx.end(),[](int i,int j){
            if(x[i]==x[j])return y[i]>y[j];
            return x[i]<x[j];
        });
        for(int i=1;i<=n;i++)
            mxy[i]=n-mxy[i]+1;
        // for the second octant we sort indexes by decreasing order of x[]+y[]
        for(int i:vx){
            int j=ft.get(mxy[i]).second;
            if(j!=-inf)
                pq.emplace(dist(i,j),i,j);
            ft.update(mxy[i],x[i]-y[i],i);
        }

        for(int i=1;i<=n;i++){
            int nx=-y[i],ny=x[i];
            x[i]=nx,y[i]=ny;
        }
        // After rotating every coordinates around (0,0) for 3 times we have processed all 8 octants.
    }
    cout<<kruskal();
}