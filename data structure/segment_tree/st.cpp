#include<bits/stdc++.h>
#define allof(a)            a.begin(),a.end()
#define int                 long long
#define fi                  first
#define se                  second
#define pb                  push_back
#define F(i,a,b,k)          for(int i=a;i<=b;i+=k)
#define D(i,a,b,k)          for(int i=a;i>=b;i-=k)
#define lsb(i) (i&(-i))
#define inf                 0x3f3f3f3f3f3f3f3f
using namespace             std;
using ii=                   pair<int,int>;
using u128=                 __uint128_t;
int n,q;
int u,v;
int a[50001];
int gtnn[200001],gtln[200001];

void build(int id, int l, int r, int i, int v) 
{
   if (i < l || r < i) return;// i nằm ngoài đoạn [l, r], ta bỏ qua nút i
   if (l == r) {gtln[id] = v;return ;}// Đoạn chỉ gồm 1 phần tử, không có nút con
        
   // Gọi đệ quy để xử lý các nút con của nút id
   int mid = (l + r) / 2;
   build(id*2, l, mid, i, v);
   build(id*2 + 1, mid+1, r, i, v);

   // Cập nhật lại giá trị max của đoạn [l, r] theo 2 nút con:
   gtln[id] = max(gtln[id*2], gtln[id*2 + 1]);
}

int get(int id, int l, int r, int u, int v) 
{
   if (v < l || r < u)return -inf;// Đoạn [u, v] không giao với đoạn [l, r], ta bỏ qua đoạn này
        
   if (u <= l && r <= v)return gtln[id];
   // Đoạn [l, r] nằm hoàn toàn trong đoạn [u, v] mà ta đang truy vấn, ta trả lại
   // thông tin lưu ở nút id
        
   int mid = (l + r) / 2;
   // Gọi đệ quy với các con của nút id
   return max(get(id*2, l, mid, u, v), get(id*2 + 1, mid+1, r, u, v));
}

main()
{
    cin>>n>>q;
    F(i,1,n,1)cin>>a[i];
    F(i,1,n,1)build(1,1,n,i,a[i]);
    F(i,1,q,1)
    {
        cin>>u>>v;
        cout<<get(1,1,n,u,v)<<'\n';
    }
}