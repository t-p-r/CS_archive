#include<bits/stdc++.h>

using namespace std;

struct suffix_array{
    vector<int>sa,rnk,lcp;

    suffix_array(string s):sa(s.size()+1),rnk(s.size()),lcp(s.size()){
        s.push_back('$');
        
        int n=s.size();
        vector<int>cnt(max(n,256)),bucket(n);
        vector<int>new_sa(n),new_bucket(n);

        for(int i=0;i<n;i++)
            cnt[s[i]]++;
        for(int i=1;i<256;i++)
            cnt[i]+=cnt[i-1];
        for(int i=n-1;i>=0;i--)
            sa[--cnt[s[i]]]=i;
        
        for(int i=1;i<n;i++){
            bucket[sa[i]]=bucket[sa[i-1]];
            if(s[sa[i]]!=s[sa[i-1]])bucket[sa[i]]++;
        }

        for(int len=1;len<n;len<<=1){
            fill(cnt.begin(),cnt.end(),0);

            for(int i=0;i<n;i++)
                cnt[bucket[i]]++;
            for(int i=1;i<n;i++)
                cnt[i]+=cnt[i-1];

            for(int i=n-1;i>=0;i--){
                int j=(sa[i]-len+n)%n;
                new_sa[--cnt[bucket[j]]]=j;
            }

            sa.swap(new_sa);
            new_bucket[sa[0]]=0;

            for(int i=1;i<n;i++){
                new_bucket[sa[i]]=new_bucket[sa[i-1]];
                if(bucket[sa[i]]!=bucket[sa[i-1]] || bucket[(sa[i]+len)%n]!=bucket[(sa[i-1]+len)%n])
                    new_bucket[sa[i]]++;
            }
            bucket.swap(new_bucket);
        }

        sa.erase(sa.begin());n--;

        for(int i=0;i<n;i++)
            rnk[sa[i]]=i;

        for(int i=0,k=0;i<n;i++){
            if(rnk[i]==n-1)k=0;
            else{
                int j=sa[rnk[i]+1];
                while(i+k<n && j+k<n && s[i+k]==s[j+k])k++;

                lcp[rnk[i]]=k;
                if(k!=0)k--;
            }
        }
    }
};