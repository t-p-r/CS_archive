#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
using namespace __gnu_cxx;
using namespace __gnu_pbds;

typedef tree<int,
             null_type,
             std::less<int>,
             rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;
typedef tree<int,
             int,
             std::less<int>,
             rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_map;
typedef trie<std::string,
             null_type,
             trie_string_access_traits<>,
             pat_trie_tag,
             trie_prefix_search_node_update>
    prefix_trie;

prefix_trie st;

void lmao(){
    st.insert("");
}
