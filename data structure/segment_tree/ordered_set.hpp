#include<bits/stdc++.h>
using namespace std;

template<int LB,int RB>
class ordered_set
{

    #define mid         ((l+r)>>1)
    #define lc          id->lid,l,mid
    #define rc          id->rid,mid+1,r

    private:

    struct node
    {
        int cnt=0,sum=0;
        int lo=RB,hi=LB;
        node *lid,*rid;
    };
    node *root=new node();

    inline void create_node(node *par,int dir)
    {
        if(dir==0)par->lid=new node();
        else par->rid=new node();
    }
    int get_cnt(node *id)
        {return id==nullptr ? 0 : id->cnt;}
    int get_sum(node *id)
        {return id==nullptr ? 0 : id->sum;}
    int get_min(node *id)
        {return id==nullptr ? RB : id->lo;}
    int get_max(node *id)
        {return id==nullptr ? LB : id->hi;}
    void update(node *id,int l,int r,int i,int hs)
    {
        if(l==r)
        {
            if(id->cnt==0 && hs<0)return;
            if(hs==-2)hs=id->cnt;
            id->cnt+=hs;id->sum+=i*hs;
            id->lo= id->cnt ? i : RB;
            id->hi= id->cnt ? i : LB;
            return;
        }
        if(i<=mid) {if(id->lid==nullptr)create_node(id,0);update(lc,i,hs);}
        else {if(id->rid==nullptr)create_node(id,1);update(rc,i,hs);}

        id->cnt=get_cnt(id->lid)+get_cnt(id->rid);
        id->sum=get_sum(id->lid)+get_sum(id->rid);
        id->lo=min(get_min(id->lid),get_min(id->rid));
        id->hi=max(get_max(id->lid),get_max(id->rid));
    }

    int get(node *id,int l,int r,int u,int v)
    {
        if(id==nullptr || r<u || v<l)return 0;
        if(u<=l && r<=v)return id->cnt;
        return get(lc,u,v)+get(rc,u,v);
    }

    int trace(node *id,int l,int r,int k)//k_th largest element from l..r
    {
        if(id==nullptr)return RB;
        if(l==r)return id->cnt ? l : RB;
        else return get_cnt(id->lid)>=k ? trace(lc,k) 
                                        : trace(rc,k-get_cnt(id->lid));
    }
    int climb(node *id,int l,int r,int val,int hs)
    {
        if(id==nullptr)return RB;
        if(l==r)return id->cnt ? l : RB;
        return hs==0 ? id->lid!=nullptr && get_max(id->lid)>=val ? climb(lc,val,hs) 
                                                                 : climb(rc,val,hs)
                     : id->rid!=nullptr && get_min(id->rid)<=val ? climb(rc,val,hs) 
                                                                 : climb(lc,val,hs);
    }
    
    void clear(node *id)
    {
        if(id==nullptr)return;
        clear(id->lid);clear(id->rid);
        delete id;id=nullptr;
    }

    public:
    
    ordered_set() {}

    int end()
        {return RB;}
    int size()
        {return root->cnt;}
    bool empty()
        {return !size();}
    
    void insert(const int& i)
        {update(root,LB,RB,i,1);}
    void erase(const int& i)
        {update(root,LB,RB,i,-1);}
    void erase_all(const int& i)
        {update(root,LB,RB,i,-2);}
    void clear()
        {clear(root->lid);clear(root->rid);root=new node();}

    int order_of_key(const int& k)
        {return get(root,LB,RB,LB,k);}
    int find_by_order(const int& k)
        {return root->cnt>=k ? trace(root,LB,RB,k) : RB;}
    
    int lower_bound(const int& val)
        {return climb(root,LB,RB,val,0);}
    int upper_bound(const int& val)
        {return climb(root,LB,RB,val,1);}
    int count(int l,int r)
        {return get(root,LB,RB,l,r);}

    #undef mid
    #undef lc
    #undef rc
};
