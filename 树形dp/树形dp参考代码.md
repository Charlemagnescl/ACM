---
title: 树形dp参考代码
tags: 树形dp,参考代码
grammar_cjkRuby: true
grammar_mathjax: true
---
---

POJ-2342
```javascript
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;
const int N = 6e3+100;
int head[N];
struct Edge
{
    int to,next;
    Edge(){};
    Edge(int t,int n):to(t),next(n){}
}e[N];
int tot;
void add(int u,int v)
{
    e[tot]=Edge(v,head[u]);
    head[u] = tot++;
}
int po[N]={0};
int f[N];
int finf(int x)
{
    return f[x]==-1?x:f[x]=finf(f[x]);
}
int dp[N][2];
void dfs(int r)
{
    vector<int>v;
    for(int i=head[r];i!=-1;i=e[i].next)
    {
        int vv = e[i].to;//cout << r << " " << vv << endl;
        dfs(vv);
        v.push_back(vv);
    }
    for(int i=0;i<v.size();i++)
    {
        dp[r][0]+=max(dp[v[i]][1],dp[v[i]][0]);
        dp[r][1]+=dp[v[i]][0];
    }
    dp[r][1]+=po[r];
}
int main()
{
    memset(head,-1,sizeof(head));
    memset(f,-1,sizeof(f));
    tot=0;
    int N;
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&po[i]);
    }
    int l,k;
    while(scanf("%d%d",&l,&k)==2&&l)
    {
        add(k,l);
        f[finf(l)]=finf(k);
    }
    int root;
    for(int i=1;i<=N;i++)
    {
        if(f[i]==-1)root = i;
    }
    dfs(root);
    printf("%d\n",max(dp[root][0],dp[root][1]));
    return 0;
}
```

POJ-1463
```javascript
#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int N = 1600;
int head[N],tot,dp[N][2];
struct node
{
    int to,next;
    node(){}
    node(int t,int n):to(t),next(n){}
}e[N<<1];
void add(int u,int v)
{
    e[tot] = node(v,head[u]);
    head[u]=tot++;
}
int dfs(int cur,int pre)
{
    //cout << cur << " " << pre << endl;
    dp[cur][0] = 0;
    dp[cur][1] = 1;
    int ans = 0,cntn=0;
    for(int i=head[cur];i!=-1;i=e[i].next)
    {
        int v = e[i].to;
        if(v!=pre)
        {
            dfs(v,cur);
            dp[cur][1] += min(dp[v][0],dp[v][1]);
            dp[cur][0] += dp[v][1];
        }
    }
}
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        memset(head,-1,sizeof(head));
        memset(dp,0,sizeof(dp));
        tot=0;
        for(int i=0;i<n;i++)
        {
            int no,cv;
            scanf("%d:(%d)",&no,&cv);
            for(int j=0;j<cv;j++)
            {
                int v;
                scanf("%d",&v);
                add(no,v);
                add(v,no);
            }
        }
        dfs(0,0);
        printf("%d\n",min(dp[0][1],dp[0][0]));
    }
    return 0;
}
```

POJ-2378
```javascript
#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int N = 1e4+100;
int head[N],tot,dp[N][2],n;
struct node
{
    int to,next;
    node(){}
    node(int t,int n):to(t),next(n){}
}e[N<<1];
void add(int u,int v)
{
    e[tot] = node(v,head[u]);
    head[u]=tot++;
}
vector<int>v;
int dfs(int cur,int pre)
{
    vector<int>b;
    for(int i=head[cur];i!=-1;i=e[i].next)
    {
        int vv = e[i].to;
        if(vv!=pre)
        {
            b.push_back(dfs(vv,cur));
        }
    }
    int flag=1,ans=0;
    for(int i=0;i<b.size();i++)
    {
        ans+=b[i];
        if(b[i]>(n/2))
            flag=0;
    }
    //if(flag)cout << cur<< endl;
    if(flag&&((n-ans-1)<=(n/2)))
        v.push_back(cur);
    return 1+ans;
}
int main()
{
    scanf("%d",&n);
    memset(head,-1,sizeof(head));
    tot=0;
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    dfs(1,0);
    sort(v.begin(),v.end());
    for(int i=0;i<v.size();i++)
        printf("%d\n",v[i]);
    return 0;
}
```

ZOJ-3201
```javascript
#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
typedef long long LL;
const int N = 1e2+100;
int head[N],tot;
struct node
{
    int to,next;
    node(){}
    node(int t,int n):to(t),next(n){}
}e[N<<1];
void add(int u,int v)
{
    e[tot] = node(v,head[u]);
    head[u]=tot++;
}
int siz[N],m;
LL fin,dp[N][N],nw[N];
int dfs(int cur,int pre)
{
    siz[cur] = 1,dp[cur][1]=nw[cur];
    for(int i=head[cur];i !=-1;i=e[i].next)
    {
        int v = e[i].to;
        if(v!=pre)
        {
            dfs(v,cur);
            siz[cur]+=siz[v];
            for(int j = min(m,siz[cur]);j;j--)
            {
                for(int k = max(1,j-siz[v]);k<=j;k++)
                {
                    dp[cur][j] = max(dp[cur][j],dp[cur][k] + dp[v][j-k]);
                }
            }
        }
    }
    fin = max(dp[cur][m],fin);
}
int main()
{
    int n;
    while(~scanf("%d%d",&n,&m))
    {
        memset(head,-1,sizeof(head));
        memset(dp,0,sizeof(dp));
        tot=fin=0;
        for(int i=0;i<n;i++)
        {
            scanf("%d",&nw[i]);
        }
        for(int i=0;i<n-1;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            add(u,v);
            add(v,u);
        }
        dfs(0,0);
        printf("%lld\n",fin);
    }
    return 0;
}
```

POJ-3659
```javascript
#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int N = 1e5+100;
int head[N],tot,dp[N][3];
struct node
{
    int to,next;
    node(){}
    node(int t,int n):to(t),next(n){}
}e[N<<1];
void add(int u,int v)
{
    e[tot] = node(v,head[u]);
    head[u]=tot++;
}
int dfs(int cur,int pre)
{
    //cout << cur << " " << pre << endl;
    dp[cur][0] = 0;
    dp[cur][1] = 1;
    dp[cur][2] = 0;
    int ans = 0,cntn=0,flag=1,mi=1<<30;
    for(int i=head[cur];i!=-1;i=e[i].next)
    {
        int v = e[i].to;
        if(v!=pre)
        {
            dfs(v,cur);
            dp[cur][1] += min(dp[v][0],min(dp[v][1],dp[v][2]));
            dp[cur][2] += min(dp[v][0],dp[v][1]);
            if(dp[v][1]<=dp[v][0])
            {
                dp[cur][0] += dp[v][1];
                flag = 0;
            }
            else
            {
                dp[cur][0] += dp[v][0];
                mi = min(mi,dp[v][1] - dp[v][0]);
            }
        }
    }
    if(flag)
    {
        dp[cur][0] += mi;
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));
    tot=0;
    for(int i=0;i<n-1;i++)
    {
        int no,cv;
        scanf("%d%d",&no,&cv);
        add(no,cv);
        add(cv,no);
    }
    dfs(1,0);
    printf("%d\n",min(dp[1][1],dp[1][0]));
    return 0;
}
```

HDU-2196
```javascript
#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
typedef long long LL;
const int N = 1e4+100;
int head[N],tot,id[N];
LL dp[N][3];
struct node
{
    int to,next;
    LL w;
    node(){}
    node(int t,LL l,int n):to(t),w(l),next(n){}
}e[N<<1];
void add(int u,int v,LL w)
{
    e[tot] = node(v,w,head[u]);
    head[u]=tot++;
}
void dfs1(int cur,int pre)
{
    for(int i=head[cur];i!=-1;i=e[i].next)
    {
        int v = e[i].to;
        LL w=e[i].w;
        if(v!=pre)
        {
            dfs1(v,cur);
            LL x = dp[v][0] + w;
            if(x>dp[cur][0])
            {
                dp[cur][0]=x;
                id[cur] = v;
            }
        }
    }
    for(int i=head[cur];i!=-1;i=e[i].next)
    {
        int v = e[i].to;
        LL w=e[i].w;
        if(v!=pre && v!=id[cur])
        {
            dfs1(v,cur);
            LL x = dp[v][0] + w;
            if(x>dp[cur][1])
            {
                dp[cur][1]=x;
            }
        }
    }
}
void dfs2(int cur, int pre)
{

    for(int i=head[cur]; i!=-1; i=e[i].next)
    {
        int v = e[i].to;
        LL w = e[i].w;
        if(v!=pre)
        {
            if(id[cur] == v)
            {
                dp[v][2] = max(dp[cur][1],dp[cur][2]) + w;
            }
            else
            {
                dp[v][2] = max(dp[cur][0],dp[cur][2]) + w;
            }
            dfs2(v,cur);
        }
    }
}
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        memset(head,-1,sizeof(head));
        memset(dp,0,sizeof(dp));
        tot=0;
        for(int i=2;i<=n;i++)
        {
            int v;
            LL w;
            scanf("%d%lld",&v,&w);
            add(i,v,w);
            add(v,i,w);
        }
        dfs1(1,0);
        dfs2(1,0);
        for(int i=1;i<=n;i++)
        {
            printf("%lld\n",max(dp[i][2],dp[i][0]));
        }
    }
    return 0;
}
```
