#include <algorithm>
#include <vector>
using namespace std;

const double EPS = 1e-9;
const int inf = 0x3f3f3f3f;

int gauss(vector<vector<int>> a, vector<int>& ans) {
    // return the number of solutions for the SLAE held in (a),
    // and put into (ans) a solution if there is any.

    int n = a.size(), m = (int)a[0].size() - 1;
    vector<int> where(m, -1);

    for (int col = 0, row = 0; col < m && row < n; col++) {
        int pos = row;
        for (int i = row; i < n; i++)
            if (abs(a[i][col]) > abs(a[pos][col])) pos = i;

        if (abs(a[pos][col]) < EPS) continue;
        // no pivot row found, x[col] is an independant variable
        a[pos].swap(a[row]);
        where[col] = row;

        for (int i = 0; i < n; i++)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j = col; j <= m; j++)
                    a[i][j] -= a[row][j] * c;
                // after this step a[i][col] becomes 0
            }
        row++;
    }

    ans.assign(m, 0);

    for (int i = 0; i < m; i++)
        if (where[i] != -1) ans[i] = a[where[i]][m] / a[where[i]][i];
    // now that we have found all variables that we can, simply ignore all other
    // variables (i.e let them equates 0), and see if the variables that we
    // found can be a solution to the SLAE

    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < m; j++)
            sum += ans[j] * a[i][j];
        // just plug it in

        if (abs(sum - a[i][m]) > EPS) return 0;
        // this part is obvious
    }

    for (int i = 0; i < m; i++)
        if (where[i] == -1) return inf;

    return 1;
    // no independant variable found, thus there is one unique solution,
    // stored in (ans).
}