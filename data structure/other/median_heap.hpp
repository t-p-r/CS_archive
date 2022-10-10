#include<bits/stdc++.h>
using namespace std;

struct median_heap{
    priority_queue<int>lo,hi;
    void insert(int x){
        if(lo.empty() || x<=lo.top()){
            lo.push(x);
            if(lo.size()>hi.size()+1){
                hi.push(-lo.top());
                lo.pop();
            }
        }
        else{
            hi.push(-x);
            if(hi.size()>lo.size()){
                lo.push(-hi.top());
                hi.pop();
            }
        }
    }
    int get(){
        return lo.top();
    }
};
 