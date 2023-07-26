#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

typedef tree<int,
             null_type,
             less<int>,
             rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;
typedef tree<int,
             int,
             less<int>,
             rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_map;
typedef trie<string,
             null_type,
             trie_string_access_traits<>,
             pat_trie_tag,
             trie_prefix_search_node_update>
    prefix_trie;

gp_hash_table<int, int> better_unordered_map;
