#include <vector>
using namespace std;

template <int mn>
struct three_dimensions_fenwick_tree {
    vector<int> pre_node[mn];
    vector<vector<int>> real_node[mn];
    vector<vector<int>> ft[mn];

    inline int lsb(int i) { return i & -i; }
    void pre_alloc(int _i, int j) {
        for (int i = _i; i <= n; i += lsb(i))
            pre_node[i].emplace_back(j);
        for (int i = _i; i; i -= lsb(i))
            pre_node[i].emplace_back(j);
    }
    void pre_alloc(int _i, int _j, int k) {
        for (int i = _i; i <= n; i += lsb(i)) {
            for (int j = lower_bound(allof(pre_node[i]), _j) -
                         pre_node[i].begin() + 1;
                 j <= pre_node[i].size(); j += lsb(j))
                real_node[i][j - 1].emplace_back(k);
            for (int j = lower_bound(allof(pre_node[i]), _j) -
                         pre_node[i].begin() + 1;
                 j; j -= lsb(j))
                real_node[i][j - 1].emplace_back(k);
        }
        for (int i = _i; i; i -= lsb(i)) {
            for (int j = lower_bound(allof(pre_node[i]), _j) -
                         pre_node[i].begin() + 1;
                 j <= pre_node[i].size(); j += lsb(j))
                real_node[i][j - 1].emplace_back(k);
            for (int j = lower_bound(allof(pre_node[i]), _j) -
                         pre_node[i].begin() + 1;
                 j; j -= lsb(j))
                real_node[i][j - 1].emplace_back(k);
        }
    }
    void update(int i, int _j, int _k) {
        for (; i <= n; i += lsb(i))
            for (int j = lower_bound(allof(pre_node[i]), _j) -
                         pre_node[i].begin() + 1;
                 j <= pre_node[i].size(); j += lsb(j))
                for (int k = lower_bound(allof(real_node[i][j - 1]), _k) -
                             real_node[i][j - 1].begin() + 1;
                     k <= real_node[i][j - 1].size(); k += lsb(k))
                    ft[i][j - 1][k - 1]++;
    }
    int get(int i, int _j, int _k) {
        int res = 0;
        for (; i; i -= lsb(i))
            for (int j = lower_bound(allof(pre_node[i]), _j) -
                         pre_node[i].begin() + 1;
                 j; j -= lsb(j))
                for (int k = lower_bound(allof(real_node[i][j - 1]), _k) -
                             real_node[i][j - 1].begin() + 1;
                     k; k -= lsb(k))
                    res += ft[i][j - 1][k - 1];
        return res;
    }
};
