/*
* author: charlemagnescl
* date ac: 2020.5.21
* question Id: cf gym 102452J
* tag: digits dp
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


const int mod = 1e9 + 7;
const int mxi = 5101, mxj=63,mxt=2;
int dp[mxi][mxj][mxj][mxt],m;

int p[mxi];



int solve(char *a,int r){
    int k = strlen(a),nt;
    for(int i=0;i<k;i++){
        a[i] -= '0';
    }
    p[0]=1;
    for(int i=1;i<=k;i++){
        p[i] = 10 * p[i-1] % m;
    }
    for(int i=1;i<=k;i++)
        for(int j=0;j<m;j++)
            for(int s=0;s<m;s++)
                for(int t=0;t<2;t++)
                    dp[i][j][s][t]=0;
    dp[0][0][0][1] = 1;
    for(int i=0; i<k; i++){

        for(int j=0; j<m; j++){

            for(int s = 0; s<m ;s++){

                for(int t=0; t<2; t++){
                    if(!dp[i][j][s][t]){
                        continue;
                    }
                    for(int x=0; x<10; x++){
                        if(t){
                            if(x > a[i]){
                                
                                break;
                            }
                            
                            nt = x == a[i];
                            
                        }else{
                            nt = 0;
                        }
                        int tmp = dp[i+1][((j+x*(s - p[k-i-1]))%m+m)%m][(s+x)%m][nt] + dp[i][j][s][t];
                        if(tmp >= mod) tmp -= mod;
                        dp[i+1][((j+x*(s - p[k-i-1]))%m+m)%m][(s+x)%m][nt] = tmp;
                    }
                
                }
            }
        }

    }

    int cnt = 0;
    for(int s=0;s<m;s++){
        for(int t=0; t<=r; t++){
            cnt += dp[k][0][s][t];
            cnt %= mod;
        }
    }
    return cnt;
}


int main()
{
    int T;
    scanf("%d",&T);
    while(T--){

        char l[mxi], r[mxi];
        scanf("%s%s%d",l,r,&m);

        printf("%d\n",(solve(r,1)-solve(l,0)+mod)%mod);
    }
    //cout << endl;
    return 0;
}
