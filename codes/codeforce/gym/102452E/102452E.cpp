/*
* author: charlemagnescl
* date ac: 2020.5.19
* question Id: cf gym 102452E
* tag: thinking, Find regularity， structure
*/
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

typedef long long ll;

const int mx = 2e5;

int nu[mx];
bool re[mx];
bool ju[mx];
int n;
void solve(){
    memset(re,0,sizeof(re));
    for(int i=0; i<n; i++){
        int cntd = 0;
        int cnt = 0;
        int si = nu[i] < (n+1)/2;    
        int dif = abs(nu[i] - (n+1)/2); //denote how much delete operations should happen if we want nu[i] to survive
        for(int j=0; j<n; j++){
            if(j == i){
                cnt = 0;
                continue;
            }
            int sj = nu[j] < nu[i];      
            if(si == sj){   //obviously that if nu[i] smaller than median we should delete the numbers bigger than nu[i],versa, we should delete the numbers
                            //smaller than nu[i], therefore , if nu[j] smaller/bigger than nu[i],we won't consider them as deleting candidate.
                cnt = max(cnt-1,0);
            }
            else{
                ++cnt;
                if(cnt == 3){
                    ++cntd,cnt-=2;
                }
            }
        }
        if(cntd >= dif){
            re[i] = 1;
        }
    }
}


int main()
{
    int T;
    scanf("%d",&T);
    while(T--){

        scanf("%d",&n);
        for(int i=0; i<n; i++){
            scanf("%d",&nu[i]);
        }
        solve();
        for(int i=0; i<n; i++){
            printf("%d",re[i]);
        }
        printf("\n");
    }
    //cout << endl;
    return 0;
}
