/*
  只要旋律中数与数的差值相同就可以满足旋律转调的条件。
  题目转化为求差值序列中不可重叠最长重复字串。
  二分长度k，利用后缀数组的性质来判断是否符合条件：
  1.存在height[i]>=k
  2.满足条件1的同时，sa[i] - sa[i-1] > k;  //不重叠 
*/
#include<vector>
#include<map>
#include<string>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+50;

int s[N];
int y[N],x[N],c[N],sa[N],rk[N],height[N],wt[30],n,m;
//c数组是桶, x[i]代表第i个元素的第一关键字

void init(){
    memset(y,0,sizeof(y));
    memset(x,0,sizeof(x));
    memset(rk,0,sizeof(rk));
    memset(height,0,sizeof(height));
    memset(c,0,sizeof(c));
}

void putout(int x){
    if(!x){
        printf("%c",48);
        return ;
    }
    int l = 0;
    while(x) wt[++l]=x%10,x/=10;
    while(l)printf("%c",wt[l--]+48);
}

void get_SA(){
    for(int i=1;i<=n;++i)
        ++c[x[i]=s[i]];
    for(int i = 2; i<=m ; ++i)
        c[i]+=c[i-1];
    for(int i = n; i>=1; --i)
        sa[c[x[i]]--] = i;
    for(int k=1; k<=n; k<<=1){ //倍增排序
        int num = 0;
        for(int i=n-k+1; i<=n; ++i)   //y[i]表示第二关键字排名为i的数，第一关键字的位置
            y[++num] = i;           //第n-k+1到第n位是没有第二关键字的 所以排名在最前面
        for(int i=1; i<=n; ++i){
            if(sa[i]>k)
                y[++num] = sa[i]-k;
        }       //下标大于k才可作为第二关键字

        for(int i=1; i<=m; ++i)
            c[i] = 0;
        for(int i=1; i<=n; ++i)
            ++c[x[i]];
        for(int i=2; i<=m; ++i) c[i]+=c[i-1];
        for(int i=n; i>=1; --i)
            sa[c[x[y[i]]]--] = y[i],y[i]=0;         //基数排序

        swap(x,y);
        x[sa[1]] = 1;
        num = 1;
        for(int i=2; i<=n; ++i)
            x[sa[i]] = (y[sa[i]]==y[sa[i-1]] && y[sa[i]+k] == y[sa[i-1]+k]) ? num : ++num;
        if(num == n)
            break;
        m = num;
    }
//    for(int i=1; i<=n; ++i){
//        putout(sa[i]);
//        printf(" ");
//    }

}

void get_height(){
    int k = 0;
    for (int i=1; i<=n; ++i) rk[sa[i]] = i;
    for(int i=1; i<=n; ++i){
        if(rk[i]==1) continue; //第一名height为0
        if(k) --k;  //h[i]>=h[i-1]-1;
        int j=sa[rk[i]-1];
        while(j+k<=n && i+k<=n && s[i+k]==s[j+k]) ++k;
        height[rk[i]] = k; //h[i] = height[rk[i]];
    }

}

bool judge(int mid){
    int Max = sa[1] , Min = sa[1];
    for(int i = 1; i<=n; i++){
        if(height[i]>=mid)
            Max = max(Max,sa[i]), Min = min(Min,sa[i]);
        else
            Max = sa[i],Min = sa[i];
        if(Max - Min >= mid+1)
            return true;
    }
    return false;
}

int main(){
//    ios::sync_with_stdio(0);
//    cin.tie(0);
//    cout.tie(0);
    while(scanf("%d",&n)&&n){
        init();
        for(int i =1; i<=n; i++){
            scanf("%d",&s[i]);
            if(i>1)
                s[i-1] = s[i] - s[i-1] + 88;
            m = max(m,s[i-1]);
        }
        s[n] = 0; n--; m++;
        get_SA();
        get_height();
        int L=0,R = n, ans = 0;
        while(L<=R){
            int mid = (L+R)/2;
            if(judge(mid))
                L = mid+1,ans = max(ans,mid);
            else
                R = mid -1;
        }
        if(ans<4)
            puts("0");
        else
            printf("%d\n",ans+1);
    }
    return 0;
}
