#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <set>

int read()
{
int f=1,x=0;
char ss=getchar();
while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
return f*x;
}

using namespace std;

typedef long long ll;
const ll inf1 = 0x3f3f3f3f; // inf add inf still inf
const ll inf2 = 0x7fffffff; // inf add inf overflow 

const int mx = 1e5+10;



struct po{
	ll x,y;
	po(){};

}nu[mx];

bool cmp(po a,po b){
	return a.x > b.x;
}


int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		ll mindif = 2e18+5;
		scanf("%d",&n);
		multiset<ll>s1,s2;
		for(int i=0; i<n; i++){
			ll x,y;
			scanf("%lld%lld",&x,&y);
			nu[i].x = x;
			nu[i].y = y;
			s2.insert(y);
		}
		sort(nu,nu+n,cmp);
		for(int i=0; i<n; i++){
			s2.erase(s2.find(nu[i].y));		//一个人只能选一种节目
			if(!s1.empty()){
				mindif = min(mindif,(ll)abs(*s1.rbegin() - nu[i].x));	//在s1中找最大的
			}
			if(!s2.empty()){
				multiset<ll>::iterator it = s2.lower_bound(nu[i].x);	
				if(it == s2.end()){
					--it;
				}
				ll tmp = abs(*it - nu[i].x);
				if(tmp < mindif && (s1.empty() || *it > *s1.rbegin())){
					mindif = tmp;
				}
				if(it != s2.begin()){	//第一个小于的也有可能比较接近xi
					--it;
					tmp = abs(*it - nu[i].x);
					if(tmp < mindif && (s1.empty() || *it > *s1.rbegin())){
						mindif = tmp;
					}

				}
				s1.insert(nu[i].y);
			}
		}
		printf("%lld\n",mindif);
	}
	return 0;
}
