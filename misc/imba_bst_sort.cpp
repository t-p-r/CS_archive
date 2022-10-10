// Sort algothirm using Binary Search Tree (BST)

// ************************************************

#include<bits/stdc++.h>
#define allof(a)            a.begin(),a.end()
#define int                 long long
#define fi                  first
#define se                  second
#define pb                  push_back
#define F(i,a,b)            for(int i=a;i<=b;i++)
#define D(i,a,b)            for(int i=a;i>=b;i--)
#define inf                 0x3f3f3f3f3f3f3f3f
using namespace             std;
using ii=                   pair<int,int>;
using u128=                 __uint128_t;
int n,a[1000001],b[1000001],bd=0;

struct node
{
    int key;
    node* l;
    node* r;
};

node *root=new node();

void insert(int val)
{
    node* i=root;
    node* j=new node();
    j->key=val;

    bool kt=0;
    while(1)
    {
        if(val<i->key){if(i->l!=nullptr)i=i->l;else break;}
        else{if(i->r!=nullptr)i=i->r;else{kt=1;break;}}
    }

    if(!kt)i->l=j;else i->r=j;
}

vector<int>v;
void dfs(node* i)
{
    if(i->l!=nullptr)dfs(i->l);
    if(i!=root)v.pb(i->key);
    if(i->r!=nullptr)dfs(i->r);
}

template<typename iter>
void bst_sort(iter l,iter r)
{
    for(iter i=l;i!=r;i++)insert(*i);
    dfs(root);
}

int32_t main()
{
    ios::sync_with_stdio(0);
    #ifdef _TPR_
        freopen("t.inp","r",stdin);  
        freopen("t.out","w",stdout);
    #endif
    cin>>n;
    F(i,1,n)cin>>a[i];
    bst_sort(a+1,a+n+1);
    for(int g:v)cout<<g<<' ';
}
