#include<iostream>

namespace fio{
    void scan(int& n){
        register int c=getchar();
        bool neg=false;
        while(c!='-' && (c<'0' || c>'9'))c=getchar();
        n=0;if(c=='-')neg=true,c=getchar();

        for(;c>=48 && c<=57;c=getchar())n=10*n+c-48;
        if(neg)n=-n;
    }
    void scan(unsigned int& n){
        register int c=getchar();
        while(c<'0' || c>'9')c=getchar();n=0;
        for(;c>=48 && c<=57;c=getchar())n=10*n+c-48;
    }
	void printl(int k,const char* end_modifier=""){
		bool neg=0;
		if(k<0)neg=1,k=-k;
		char v[21];int cnt=0;

		while(k)v[++cnt]=((k%10)+'0'),k/=10;
		if(neg)putchar('-');if(!cnt)putchar('0');
		while(cnt)putchar(v[cnt--]);
		fputs(end_modifier,stdout);
	}
}
