/*
* author: charlemagnescl
* date ac: 2020.5.15
* question Id: HDU 1495
* tag: bfs, number theory
*/
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;

const int mx = 1e3+10;

int s,m,n;

struct point{
    int curs,curm,curn,step;
    point(){}
    point(int s,int mm,int nn,int st){
        curs = s;
        curm = mm;
        curn = nn;
        step = st;
    }
};

queue<point>q;

bool vis[200][200];

int bfs(){
    memset(vis,0,sizeof(vis));
    while(!q.empty()){
        q.pop();
    }

    q.push(point(s,0,0,0));

    while(!q.empty()){

        point cur = q.front();
        q.pop();
        //cout << "now:" << " curs=" << cur.curs << " curm=" << cur.curm << " curn=" << cur.curn << " step=" << cur.step << endl;

        if((cur.curm == cur.curn && cur.curn != 0 && cur.curs == 0) || (cur.curn == cur.curs && cur.curn!=0 && cur.curm == 0) || (cur.curm == cur.curs && cur.curm!=0 && cur.curn == 0)){
            return cur.step;
        }
        int curs = cur.curs, curm = cur.curm, curn = cur.curn,step = cur.step;
        if(cur.curs >= (m - cur.curm)){
            if(!vis[curs-(m-curm)][m]){
                vis[curs-(m-curm)][m] = 1;
                q.push(point(curs-(m-curm),m,curn,cur.step+1));
            }
            
        }
        else{
            if(!vis[0][curm+curs]){
                vis[0][curm+curs] = 1;
                q.push(point(0,curm+curs,curn,cur.step+1));
            }
        }

        if(cur.curs >= (n - curn)){
            if(!vis[curs - (n-curn)][curm]){
                vis[curs - (n-curn)][curm] = 1;
                q.push(point(curs-(n-curn),curm,n,step+1));
            }
        }
        else{
            if(!vis[0][curm]){
                vis[0][curm] = 1;
                q.push(point(0,curm,curn+curs,step+1));
            }
            
        }
        if(!vis[curs+curm][0]){
            vis[curs+curm][0] = 1;
            q.push(point(curs + curm,0,curn,cur.step+1));
        }
        if(!vis[curs+curn][curm]){
            vis[curs+curn][curm] = 1;
            q.push(point(curs + curn,curm,0,cur.step+1));
        }
        

        if(curm >= (n - curn)){
            if(!vis[curs][curm-(n-curn)]){
                vis[curs][curm-(n-curn)] = 1;
                q.push(point(curs,curm-(n-curn),n,step+1));
            }
            
        }
        else {
            if(!vis[curs][0]){
                vis[curs][0] = 1;
                q.push(point(curs,0,curn+curm,step+1));
            }
            
        }

        if(curn >= (m-curm)){
            if(!vis[curs][m]){
                vis[curs][m] = 1;
                q.push(point(curs,m,curn-(m-curm),step+1));
            }
        }
        else {
            if(!vis[curs][curm+curn]){
                vis[curs][curm+curn] = 1;
                q.push(point(curs,curm+curn,0,step+1));
            }
            
        }


    }

    return 0;
}

int main()
{
    while(cin >> s >> m >> n){
        if(s == 0){
            break;
        }
        int rsl = bfs();
        if(rsl){
            cout << rsl << endl;
        }
        else {
            cout << "NO" <<  endl;
        }
    }
    return 0;
}
