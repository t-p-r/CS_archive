#include<bits/stdc++.h>
#define allof(a)            a.begin(),a.end()
#define int                 long long
#define fi                  first
#define se                  second
#define pb                  push_back
#define F(i,a,b)            for(int i=a;i<=b;i++)
#define D(i,a,b)            for(int i=a;i>=b;i--)
#define inf                 0x3f3f3f3f3f3f3f3f
#define mn                  300001
using namespace             std;
using ii=                   pair<int,int>;
using ip=                   tuple<int,int,int>;
const int mod=              1e9+7;

typedef struct {int a,b;} point;
int f(const point& g,const int& x)
    {return g.a*x+g.b;}

class li_chao_tree //controlling array w' index from LB to RB
{
    #define mid         ((l+r)>>1)             
    #define lc          id->lid,l,mid
    #define rc          id->rid,mid,r // MID NOT MID+1
    
    private:
    int LB=1,RB=1000000;
    struct node//node (id,l,r) control segment [l..r)
    {
        point val={0,inf};// initialize with line 0x + inf
        node *lid,*rid;
    };
    node *root=new node();

    inline void crt(node *par,int dir)
    {
        if(dir==0)par->lid=new node();
        else par->rid=new node();
    }
    
    void update(node *id,int l,int r,point nw)
    {
        bool lft=f(nw,l)<f(id->val,l);
        bool md=f(nw,mid)<f(id->val,mid);
        if(md)swap(id->val,nw);
        if(r-l==1)return;
        if(lft!=md) 
        {
            if(id->lid==nullptr)crt(id,0);
            update(lc,nw);
        } 
        else
        {
            if(id->rid==nullptr)crt(id,1);
            update(rc,nw);
        }
    }
    int get(node *id,int l,int r,int i)
    {
        if(id==nullptr)return inf;
        if(r-l==1)return f(id->val,i);
        return i<mid ? min(f(id->val,i),get(lc,i))
                     : min(f(id->val,i),get(rc,i));
    }
    void clear(node *id)
	{
		if(id==nullptr)return;
		clear(id->lid);
		clear(id->rid);
		delete id;id=nullptr;
	}

    public:

    void clear()
		{clear(root->lid);clear(root->rid);root=new node();}
    void insert(point nw)
        {update(root,LB,RB,nw);}
    int get(int i)// the line which yields the lowest y_value with given x_value
        {return get(root,LB,RB,i);}

};