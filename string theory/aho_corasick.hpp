#include<bits/stdc++.h>
using namespace std;

const int mn=1e5+11;
struct trie
{
    int cnt=0;
    int np[mn][256];
    int ise[mn];

    void insert(const string& s){
        int pt=0;
        for(int i=0;i<s.size();i++){
            int c=s[i];
            if(!np[pt][c])np[pt][c]=++cnt;
            pt=np[pt][c];
        }
        ise[pt]=1;
    }
    int pre[mn];
    int next(int u,char c){
        for(int i=u;i!=-1;i=pre[i]){
            if(np[i][c])return np[i][c];
        }
        return 0;
    }
    void build_kmp(){
        queue<int>q;
        q.push(0);pre[0]=-1;
        while(q.size()){
            int u=q.front();q.pop();
            for(int c=0;c<256;c++)if(int v=np[u][c]){
                q.push(v);
                pre[v]=next(pre[u],c);
                ise[v]|=ise[pre[v]];
            }
        }
    }
    vector<int>matches(const string& s){
        vector<int>res;
        int pt=0;
        for(int i=0;i<s.size();i++){
            pt=next(pt,s[i]);
            if(ise[pt])res.emplace_back(i),pt=0;
        }
        return res;
    }
};