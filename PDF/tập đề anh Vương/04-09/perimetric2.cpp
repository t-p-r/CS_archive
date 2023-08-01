#include <bits/stdc++.h>

using namespace std;

#define LL long long
#define LD long double
#define PR pair<int,int>

#define Fox(i,n) for (i=0; i<n; i++)
#define Fox1(i,n) for (i=1; i<=n; i++)
#define FoxI(i,a,b) for (i=a; i<=b; i++)
#define FoxR(i,n) for (i=(n)-1; i>=0; i--)
#define FoxR1(i,n) for (i=n; i>0; i--)
#define FoxRI(i,a,b) for (i=b; i>=a; i--)
#define Foxen(i,s) for (i=s.begin(); i!=s.end(); i++)
#define Min(a,b) a=min(a,b)
#define Max(a,b) a=max(a,b)
#define Sz(s) int((s).size())
#define All(s) (s).begin(),(s).end()
#define Fill(s,v) memset(s,v,sizeof(s))
#define pb push_back
#define mp make_pair
#define x first
#define y second

const int INF = (int)1e9;

#define LIM 1000001
#define MOD 1000000007

LL cur, ans;
int L[LIM], W[LIM], H[LIM];
set<PR> S;

void ReadSeq(int* V, int N)
{
  int i;
  Fox(i, N) cin >> V[i];
}

void ProcessRect(int L, int R, int H)
{
  // find first x interval overlapping with this rectangle
  auto I = prev(S.lower_bound(mp(L, -1)));
  if (I->y < L)
    I++;
  Min(L, I->x);
  // erase all x intervals overlapping with this rectangle
  while (I->x <= R)
  {
    Max(R, I->y);
    cur -= I->y - I->x + H;
    I = S.erase(I);
  }
  // add x interval for this rectangle (and any intervals it overlapped)
  cur += R - L + H;
  S.insert(mp(L, R));
}

int main()
{
  ios_base::sync_with_stdio(0), cin.tie(0);
  int N, K, i;
  // input
  cin >> N;
  ReadSeq(L, N);
  ReadSeq(W, N);
  ReadSeq(H, N);
  // process rectangles, while maintaining set of covered x intervals
  cur = 0, ans = 1;
  S.clear();
  S.insert(mp(-1, -1));
  S.insert(mp(INF + 1, INF + 1));
  Fox(i, N)
  {
    ProcessRect(L[i], L[i] + W[i], H[i]);
    ans = (LL)ans * (cur % MOD) * 2 % MOD;
  }
  cout << ans << "\n";
  
  return(0);
}
