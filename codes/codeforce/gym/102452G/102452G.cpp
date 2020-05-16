/*
* author: charlemagnescl
* date ac: 2020.5.15
* question Id: cf gym 102452
* tag: Binery tree, thinking, structure
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

const int mx = 1e6;


struct node{
    int par,cs;
    node(){};
    node(int p,int c){
        par = p;
        cs = c;
    }
}tree[mx];
int tot = 1;

void dfs(int cur,int rm){
    if(rm == 1){
        tree[cur].cs = 1;
        return;
    }
    --rm;
    if(rm&1){
        int s = ++tot;
        dfs(s,rm);
        tree[s].par = cur;
        tree[cur].cs = tree[s].cs;
    }
    else{
        
        int s1 = ++tot;
        int s2 = ++tot;
        dfs(s1,2);
        dfs(s2,rm/2);
        tree[s1].par = cur;
        tree[s2].par = cur;
        tree[cur].cs = tree[s1].cs + tree[s2].cs;
    }

}


int main()
{
    //cout << (1&1) << endl;
    ll k;
    cin >> k;
    if(k==1){
        cout << "2\n1\n1 2\n";
        return 0;
    }
    tot = 1;
    dfs(tot,k);
    cout << tot << endl;
    for(int i=2;i<=tot;i++){
        cout << tree[i].par << " ";
    }
    cout << endl;
    for(int j=1;j<=tot;j++){
        cout << tree[j].cs << " ";
    }
    //cout << endl;
    return 0;
}
