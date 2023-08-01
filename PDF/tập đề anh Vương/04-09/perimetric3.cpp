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

template<typename T> T Abs(T x) { return(x < 0 ? -x : x); }

const int INF = (int)1e9;

#define LIM 1000001
#define MOD 1000000007

#define TR pair<int, PR>

LL cur, ans;
int L[LIM], W[LIM], H[LIM];
set<TR> S;

void ReadSeq(int* V, int N)
{
  int i, A, B, C, D;
  Fox(i, N) cin >> V[i];
}

void ProcessRect(int L, int R, int H)
{
  // tentatively add full rectangle perimeter
  cur += 2 * (R - L + H);
  // iterate over union height changes overlapping with this rectangle
  auto I = prev(S.lower_bound(mp(L, mp(-1, -1))));
  auto J = S.lower_bound(mp(R + 1, mp(-1, -1)));
  TR A = *I, B = *J;
  while (I->x < B.x)
  {
    J = I, I++;
    if (J->y.y)
      cur -= 2 * (min(R, I->x) - max(L, J->x)); // subtract swallowed-up horizontal perimeter
    if (J->x >= L)
    {
      cur -= Abs(J->y.x - J->y.y); // subtract swallowed-up vertical perimeter
      S.erase(J);
    }
  }
  cur -= A.y.y + B.y.x; // subtract swallowed-up vertical perimeter at either end of this rectangle
  // insert new union height changes at either end of this rectangle
  if (A.y.y != H)
    S.insert(mp(L, mp(A.y.y, H)));
  if (B.y.x != H)
    S.insert(mp(R, mp(H, B.y.x)));
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
  // process rectangles, while maintaining set of union height changes
  cur = 0, ans = 1;
  S.clear();
  S.insert(mp(-1, mp(0, 0)));
  S.insert(mp(INF + 1, mp(0, 0)));
  Fox(i, N)
  {
    ProcessRect(L[i], L[i] + W[i], H[i]);
    ans = (LL)ans * (cur % MOD) % MOD;
  }
  cout << ans << "\n";
  return(0);
}
