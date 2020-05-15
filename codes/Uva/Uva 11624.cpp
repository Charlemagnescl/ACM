/*
* author: charlemagnescl
* date ac: 2020.5.15
* question Id: Uva 11624
* tag: bfs
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

const int inf = 0x3f3f3f3f;

int mp[mx][mx];
string mpp[mx];

struct point {
    int x,y,step;
    point(){step = 0;}
    point(int xx,int yy){
        x = xx;
        y = yy;
        step = 0;
    }
    point(int xx,int yy,int s){
        x = xx;
        y = yy;
        step = s;
    }
};

point fires[mx];
bool vis[mx][mx];

queue<point>q;

point J;

int dir[][2] = {-1,0,0,1,1,0,0,-1};

void bfs1(int fs,int mx,int my){
    while(!q.empty()){
        q.pop();
    }
    memset(mp,inf,sizeof(mp));
    for(int i=0; i<fs; i++){
        q.push(fires[i]);
        mp[fires[i].x][fires[i].y] = 0;
    }
    while(!q.empty()){
        point cur = q.front();
        q.pop();
        for(int i=0; i<4; i++){
            int x = cur.x + dir[i][0], y = cur.y + dir[i][1], step = mp[cur.x][cur.y] + 1;
            if(x >=0 && x <mx && y>=0 && y < my && mpp[x][y] != '#' && (mp[x][y] > step)){
                q.push(point(x,y));
                mp[x][y] = step;
            }
        }
    }
}

int bfs2(int mx,int my){
    while(!q.empty()){
        q.pop();
    }
    memset(vis,0,sizeof(vis));
    q.push(J);
    while(!q.empty()){
        point cur = q.front();
        q.pop();
        for(int i=0; i<4; i++){
            int x = cur.x + dir[i][0], y = cur.y + dir[i][1], step = cur.step + 1;
            
            if(x < 0 || y < 0 || x >= mx || y >= my){
                return step;
            }
            if(step >= mp[x][y]){
                continue;
            }
            if( mpp[x][y] != '#' && !vis[x][y]){
                q.push(point(x,y,step));
                vis[x][y] = 1;
            }
        }
    }
    return false;
}

int main()
{
    //cout << 1%2 << endl;
    int n;
    cin >> n;
    while(n--){
        int mmx,mmy;
        cin >> mmx >> mmy;
        int cf = 0;
        for(int i = 0; i<mmx; i++){
            cin >> mpp[i];
            for(int j=0; j<mmy; j++){
                if(mpp[i][j] == 'J'){
                    J.x = i;
                    J.y = j;
                    J.step = 0;
                }
                if(mpp[i][j] == 'F'){
                    fires[cf] = point(i,j);
                    ++ cf;
                }
            }
        }
        bfs1(cf, mmx,mmy);
        int fnl = bfs2(mmx, mmy);
        if(fnl){
            cout << fnl << endl;
        }
        else {
            
            cout << "IMPOSSIBLE" << endl;
            
        }
    }
    return 0;
}
