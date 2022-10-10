#include<bits/stdc++.h>
#define allof(a)            a.begin(),a.end()
#define int                 int64_t
#define fi                  first
#define se                  second
#define F(i,a,b)            for(int i=a;i<=b;i++)
#define D(i,a,b)            for(int i=a;i>=b;i--)
#define inf                 0x3f3f3f3f3f3f3f3f
#define mn                  200011
#define task                "jewel"
using namespace std;
const int mod=              998244353;
typedef pair<int,int>       ii;

template<typename t>
bool ckmax(t& target,const t& source){
    return target<source ? target=source,1 : 0;
}
template<typename t>
bool ckmin(t& target,const t& source){
    return target>source ? target=source,1 : 0;
}
struct line{
    int a,b;
    line():a(0),b(-inf){}
    line(int a,int b):a(a),b(b){}
};
int f(const line& g,const int& x)
    {return g.a*x+g.b;}

template<int LB,int RB>
class li_chao_tree //controlling array w' index from LB to RB
{          
    #define mid         (l+r>>1)
    #define lc          2*id,l,mid
    #define rc          2*id+1,mid+1,r
    private:
    line st[4*(RB-LB+1)];
    
    void update(int id,int l,int r,int u,int v,line val){
        if(v<l || r<u)return;
        if(u<=l && r<=v){

            if(f(st[id],l)>= f(val,l) && f(st[id],r)>=f(val,r))
                return;
            if(f(st[id],l)<= f(val,l) && f(st[id],r)<=f(val,r)){
                st[id]=val;return;
            }
            if(f(st[id],l)>=f(val,l) && f(st[id],mid)>=f(val,mid)){
                update(rc,u,v,val);return;
            }
            if(f(st[id],l)<=f(val,l) && f(st[id],mid)<=f(val,mid)){
                update(rc,u,v,st[id]);st[id]=val;return;
            }
            if(f(st[id],mid+1)>=f(val,mid+1) && f(st[id],r)>=f(val,r)){
                update(lc,u,v,val);return;
            }
            if(f(st[id],mid+1)<=f(val,mid+1) && f(st[id],r)<=f(val,r)){
                update(lc,u,v,st[id]);st[id]=val;return;
            }
            return;
        }
        update(lc,u,v,val);
        update(rc,u,v,val);
    }
    int get(int id,int l,int r,int i){
        int res=f(st[id],i);
        if(l==r)return res;

        if(i<=mid)ckmax(res,get(lc,i));
        else ckmax(res,get(rc,i));
        return res;
    }

    public:

    void insert(line nw,int u,int v)
        {update(1,LB,RB,u,v,nw);}
    int get(int i)// the line which yields the lowest y_value with given x_value
        {return get(1,LB,RB,i);}

};
