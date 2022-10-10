#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

struct chash 
{ 
    const int seed=
        (int)(make_unique<char>().get());//random memory from heap
    const int rng=
        seed^chrono::high_resolution_clock::now().time_since_epoch().count();
	const int c= 
        int(4e18*acos(0))|71;// still dont understand what this does
    int operator()(int x) const {return __builtin_bswap64((x^rng)*c);}
}st;

gp_hash_table<int,int,chash>mp;
