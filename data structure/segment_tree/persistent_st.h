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
#define task            "euler"
using namespace std;
const int mod=          1e9+7;
typedef pair<int,int>   ii;
typedef pair<int,ii>    ip;

template<typename t>
bool ckmax(t& target,const t& source){
    return target<source ? target=source,1 : 0;
}
template<typename t>
bool ckmin(t& target,const t& source){
    return target>source ? target=source,1 : 0;
}

template<int max_node_size=10000001>
struct persistent_interval_tree{
    #define mid         (l+r>>1)
    #define lc          st[id].lid,l,mid
    #define rc          st[id].rid,mid+1,r
    int node_count=0;
    struct node{
        int lid,rid;
        int val;
        node(){}
        node(int val,int lid,int rid):
            val(val),lid(lid),rid(rid){}
    }st[max_node_size];

    persistent_interval_tree(){}//index starts at 1

    inline void refine(node& cur){
        cur.val=max(st[cur.lid].val,st[cur.rid].val);
    }

    int update(int l,int r,int i,int val,int old_id){
        if(l==r){
            st[++node_count]=node(val,0,0);
            return node_count;
        }
        int cur=++node_count;

        if(i<=mid){
            st[cur].lid=update(l,mid,i,val,st[old_id].lid);
            st[cur].rid=st[old_id].rid;
        }
        else{
            st[cur].lid=st[old_id].lid;
            st[cur].rid=update(mid+1,r,i,val,st[old_id].rid);
        }
        refine(st[cur]);
        
        return cur;
    }

    int get(int id,int l,int r,int u,int v){
        if(v<l || r<u)return -inf;
        if(u<=l && r<=v)return st[id].val;
        return max(get(lc,u,v),get(rc,u,v));
    }
};
