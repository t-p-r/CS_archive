#include<bits/stdc++.h>
#define allof(a)        a.begin(),a.end()
#define int             long long
#define fi              first
#define se              second
#define pb              push_back
#define F(i,a,b)        for(int i=a;i<=b;i++)
#define D(i,a,b)        for(int i=a;i>=b;i--)
#define inf             0x3f3f3f3f3f3f3f3f
#define mn              50001
#define task            "holiday"
using namespace std;
const int mod=          1e9+7;
typedef pair<int,int>   ii;
typedef pair<int,ii>    ip;

class dynamic_segment_tree //controlling array w' index from LB to RB
{
    #define mid         ((l+r)>>1)
    #define lc          id->lid,l,mid
    #define rc          id->rid,mid+1,r
    
    private:
    int LB=LLONG_MIN,RB=LLONG_MAX;
    struct node
    {
        int val=-inf;
        node *lid,*rid;
    };
    node *root=new node();

    inline void crt(node *par,int dir)
    {
        if(dir==0)par->lid=new node();
        else par->rid=new node();
    }

    int getval(node *id)
        {return (id==nullptr) ? -inf : id->val;}
    void update(node *id,int l,int r,int i,int val)
    {
        if(l==r){id->val=val;return;}
        if(i<=mid) {if(id->lid==nullptr)crt(id,0);update(lc,i,val);}
        else {if(id->rid==nullptr)crt(id,1);update(rc,i,val);}
        id->val=max(getval(id->lid),getval(id->rid));
    }
    int get(node *id,int l,int r,int u,int v)
    {
        if(id==nullptr || r<u || v<l)return -inf;
        if(u<=l && r<=v)return id->val;
        return max(get(lc,u,v),get(rc,u,v));
    }
    void clear(node *id)
	{
		if(id==nullptr)return;
		clear(id->lid);
		clear(id->rid);
		delete id;id=nullptr;
	}

    public:

    dynamic_segment_tree(){}
    dynamic_segment_tree(int l,int r){LB=l,RB=r;}

    void clear()
		{clear(root->lid);clear(root->rid);root=new node();}
    void update(int i,int val)
        {update(root,LB,RB,i,val);}
    int get(int u,int v)
        {return get(root,LB,RB,u,v);}

}st;

int32_t main()
{
    ios::sync_with_stdio(0);
    #ifdef _TPR_
        freopen("t.inp","r",stdin);
        freopen("t.out","w",stdout);
    #endif
}