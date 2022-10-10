//Acquire, USACO March 2008 Gold Division

#include<bits/stdc++.h>
using namespace std;

template<typename t>
bool ckmin(t& target,const t& source){
    return target>source ? target=source,1 : 0;
}

namespace convex_hull_trick{
    vector<int>a,b;
    bool bad(int l1,int l2,int al3,int bl3){
        /*
        intersection(l1,l2) has x-coordinate (b1-b2)/(a2-a1)
        intersection(l1,l3) has x-coordinate (b1-b3)/(a3-a1)
        set the latter lesser than the former, cross-multiply to
        eliminate division
        */
        return (bl3-b[l1])*(a[l1]-a[l2])<(b[l2]-b[l1])*(a[l1]-al3);
    }
    int eval(int idx,int x){
        return a[idx]*x+b[idx];
    }
    void insert_line(int _a,int _b){
        while(a.size()>1 && bad(a.size()-2,a.size()-1,_a,_b)){
            a.pop_back();
            b.pop_back();
        }
        a.emplace_back(_a);b.emplace_back(_b);
    }
    int j=0;
    int query(int x){
        ckmin(j,(int)a.size()-1);
        while(j+1<a.size() && eval(j+1,x)<eval(j,x))j++;
        return eval(j,x);
    }
    // CONCEPT REQUIREMENT: a is non-increasing (if query finds minimum value) and vice versa; j is non-decreasing
    // If concept requirements are not met, use a Li Chao tree instead.
}

// int f[500001];
// bool bad(int l1,int l2,int l3)
// {
//     /*
// 	intersection(l1,l2) has x-coordinate (b1-b2)/(a2-a1)
// 	intersection(l1,l3) has x-coordinate (b1-b3)/(a3-a1)
// 	set the former greater than the latter, and cross-multiply to
// 	eliminate division
// 	*/
// 	return (b[l3]-b[l1])*(a[l1]-a[l2])<(b[l2]-b[l1])*(a[l1]-a[l3]);
// }
// void update(int _a,int _b)// thêm đt y=_a*x+_b vào bao lồi  
// {
//     a.pb(_a);b.pb(_b);
//     while(a.size()>2 && bad(a.size()-3,a.size()-2,a.size()-1))
//     {
//         a.erase(a.end()-2);
//         b.erase(b.end()-2);
//     }
// }
// int j=0;
// int query(int x)
// {
//     if(j>=a.size())j=a.size()-1;
//     while(j<a.size()-1 && a[j+1]*x+b[j+1]<a[j]*x+b[j])j++;
//     return a[j]*x+b[j];
// }

// void read()
// {
//     vector<ii>a(500001);
//     cin>>n;F(i,1,n)cin>>a[i];
//     sort(a.begin()+1,a.begin()+n+1);
//     F(i,1,n)
//     {
//         while(!v.empty() && v.back().se<=a[i].se)v.pop_back();
//         v.pb(a[i]);
//     }
//     v.insert(v.begin(),{0,0});n=v.size()-1;
// }

