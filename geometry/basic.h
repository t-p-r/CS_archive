#include<bits/stdc++.h>
#define allof(a)            a.begin(),a.end()
#define int                 long long
#define fi                  first
#define se                  second
#define pb                  push_back
#define F(i,a,b)            for(int i=a;i<=b;i++)
#define D(i,a,b)            for(int i=a;i>=b;i--)
#define inf                 1e9+7
using namespace             std;
using ii=                   pair<int,int>;
using u128=                 __uint128_t;
int n,res=0;

class pt
{
    public:int x,y;
    pt(){x=y=0;}
    pt(int _x,int _y){x=_x,y=_y;}

    friend istream& operator>> (istream& is,pt& k)
        {is>>k.x>>k.y;return is;};
    friend ostream& operator<< (ostream& os,pt  k)
        {os<<k.x<<' '<<k.y;return os;};
};

int area(vector<pt>a)
{
    if(a.size()<3)return 0;
    int res=0,n=a.size();
    F(i,0,n-2)res+=(a[i].x-a[i+1].x)*(a[i].y+a[i+1].y);
    return abs(res+(a[n-1].x-a[0].x)*(a[n-1].y+a[0].y));
}

class float_pt
{
    public:double x,y;
    float_pt(){x=y=0;}
    float_pt(double _x,double _y){x=_x,y=_y;}

    friend istream& operator>> (istream& is,float_pt& k)
        {is>>k.x>>k.y;return is;};
    friend ostream& operator<< (ostream& os,float_pt  k)
        {os<<k.x<<' '<<k.y;return os;};
};

class line
{
    public:int a,b,c; 
    line(){a=b=c=0;}
    line(int _a,int _b,int _c){a=_a,b=_b,c=_c;}
    line(pt p,pt q)
    {
        a=p.y-q.y;
        b=q.x-p.x;
        c=-a*p.x-b*p.y;
    }
    friend istream& operator>> (istream& is,line& k)
        {is>>k.a>>k.b>>k.c;return is;};
    friend ostream& operator<< (ostream& os,line  k)
        {os<<k.a<<' '<<k.b<<' '<<k.c;return os;};
};

float_pt intersect(line d1,line d2)
{
    float d  =  d1.a*d2.b-d2.a*d1.b;
    float dx = -d1.c*d2.b+d2.c*d1.b;
    float dy = -d1.a*d2.c+d2.a*d1.c;
    if(d!=0)return {dx/d,dy/d};
    return {inf,inf};
}

bool in_line (pt p,pt q, pt a,pt b, float_pt k)
{
    return  ((p.x<=k.x && k.x<=q.x)||(p.x>=k.x && k.x>=q.x)) &&
            ((a.x<=k.x && k.x<=b.x)||(a.x>=k.x && k.x>=b.x));
}

