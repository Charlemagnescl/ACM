### maximum flow templete

```java
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
const int N = 5e5+100;
const LL inf = 1e15;
int head[N],tot,dpt[N];
struct Edge
{
    int to,next;
    LL w;
    Edge(){}
    Edge(int t,int n,LL ww):to(t),w(ww),next(n){}
}e[N<<1];
void add(int u,int v,LL w)
{
    e[tot]=Edge(v,head[u],w);
    head[u]= tot++;

    e[tot]=Edge(u,head[v],0);
    head[v]=tot++;
}
bool bfs(int s,int t)
{
    memset(dpt,0,sizeof(dpt));
    queue<int>q;
    while(!q.empty())
        q.pop();
    dpt[s] = 1;
    q.push(s);
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        for(int i=head[cur];i!=-1;i=e[i].next)
        {
            int v = e[i].to;
            int w = e[i].w;
            if(e[i].w>0&&dpt[v]==0)
            {
                dpt[v] = dpt[cur]+1;
                if(v==t)
                {
                    return 1;
                }
                q.push(v);
            }
        }
    }
    return dpt[t]!=0;
}


LL dfs(int s, LL flow, int t)
{
    if(s==t||flow<=0)
    {
        return flow;
    }
    LL rest = flow;
    for(int i=head[s];i!=-1;i=e[i].next)
    {
        int v = e[i].to;
        LL w = e[i].w;
        if(e[i].w>0&&dpt[v]==dpt[s]+1)
        {
            LL tmp = dfs(v,min(rest,w),t);
            if(tmp<=0)
                dpt[v]=0;
            rest-=tmp;
            e[i].w -= tmp;
            e[i^1].w += tmp;
            if(rest<=0)
                break;
        }
    }
    return flow - rest;
}
LL Dinic(int s,int t)
{
    LL ans = 0;
    while(bfs(s,t))
        ans += dfs(s,inf,t);
    return ans;
}
int main()
{
    int n,m,s,t;
    scanf("%d%d%d%d",&n,&m,&s,&t);
    memset(head,-1,sizeof(head));
    tot = 0;
    for(int i=0 ; i<m; i++)
    {
        int u,v;
        LL w;
        scanf("%d%d%lld",&u,&v,&w);
        add(u,v,w);
    }

    printf("%lld\n",Dinic(s,t));
    return 0;
}

```
