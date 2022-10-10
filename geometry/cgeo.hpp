#include<bits/stdc++.h>
#define allof(a)            a.begin(),a.end()
#define F(i,a,b)            for(int i=a;i<=b;i++)
#define D(i,a,b)            for(int i=a;i>=b;i--)
using namespace std;

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
namespace cgeo{
    #define x               real()
    #define y               imag()
    typedef complex<double> coord;
    typedef coord           gvector;
    coord para;
    bool chk=1;
    istream& operator>>(istream& is,coord& k){
        int u,v;is>>u>>v;k=coord(u,v);return is;
    }
    double dot(const gvector& a,const gvector& b){
        return (conj(a)*b).x;
    }
    double cross(const gvector& a,const gvector& b){
        return (conj(a)*b).y;
    }
    double sqrlen(const gvector& a){
        return norm(a);
    }
    double angle(const gvector& a){
        complex<double>ta(a.x,a.y);
        return 180/M_PI*arg(ta);
    }
    coord inter(coord a,coord b,coord p,coord q){
        double c1=cross(p-a,b-a),c2=cross(q-a,b-a);
        return (c1*q-c2*p)/(c1-c2);
    }
    bool ins(coord a,coord b,coord c){
        return (c.x-a.x)*(b.x-c.x)>=0 && (c.y-a.y)*(b.y-c.y)>=0;
    }
    bool cw(const gvector& a,const gvector& b,const gvector& c){
        return cross((b-a),(c-b))<0;
    }
    bool ccw(const gvector& a,const gvector& b,const gvector& c){
        return cross((b-a),(c-b))>0;
    }
    double area(const vector<coord>& a){
        int n=a.size();
        double res=0;
        F(i,0,n-2){
            res+=(a[i].x-a[i+1].x)*(a[i].y+a[i+1].y);
        }
        res+=(a[n-1].x-a[0].x)*(a[n-1].y+a[0].y);
        return abs(res)/2;
    }
    vector<coord>convex_hull(vector<coord> a){
        if(a.size()==1)return a;
        sort(allof(a),[](const coord& a,const coord& b){
            if(a.x!=b.x)return a.x<b.x;
            return a.y<b.y; 
        });

        coord p1=a.front(),p2=a.back();
        vector<coord>up,down;
        up.emplace_back(p1),down.emplace_back(p1);

        F(i,1,a.size()-1){
            if(i==a.size()-1 || cw(p1,a[i],p2)){
                while(up.size()>=2 && 
                        !cw(up[up.size()-2],up.back(),a[i])){
                            up.pop_back();
                }
                up.emplace_back(a[i]);
            }

            if(i==a.size()-1 || ccw(p1,a[i],p2)){
                while(down.size()>=2 &&
                        !ccw(down[down.size()-2],down.back(),a[i])){
                            down.pop_back();
                }
                down.emplace_back(a[i]);
            }
        }

        a.clear();
        F(i,0,(int)up.size()-1)a.emplace_back(up[i]);
        D(i,(int)down.size()-2,1)a.emplace_back(down[i]);
        return a;
    }
    coord reflect(coord p,coord a,coord b){//reflect p across(a,b)
        return a+conj((p-a)/(b-a))*(b-a);
    }

    //---------------------------------------------------------------------


    struct line{
        double a,b,c;

        template<typename _t>
            line(_t a,_t b,_t c):a(a),b(b),c(c){}
        
        line(const coord& n,const coord& m){
            gvector v(-(m-n).y,(m-n).x);
            a=v.x,b=v.y,c=-a*n.x-b*n.y;
        }
        friend ostream& operator<<(ostream& os,const line& k){
            os<<'('<<k.a<<','<<k.b<<','<<k.c<<')';
            return os;
        }
    };
    
}