#include<iostream>
#include<vector>
#include<utility>
#include<queue>

#define NMAX 100

using namespace std;
typedef pair<int, int> pii;

int main(){

    /*
        Dijlstra法
        頂点集合V = {0, ..., n-1}, 辺集合E = edge[NMAX]からなる
        有向グラフG = (V, E)において
        頂点0からの最短経路を求める
    */
    vector<pii> edge[NMAX]; 
    priority_queue<pii, vector<pii>, greater<pii> > q;
    int c[NMAX] = {0}, d[NMAX];

    edge[0].push_back(pii(10, 1));
    edge[0].push_back(pii(5, 2));
    edge[1].push_back(pii(1, 3));
    edge[1].push_back(pii(2, 2));
    edge[2].push_back(pii(3, 1));
    edge[2].push_back(pii(9, 3));
    edge[2].push_back(pii(2, 4));
    edge[3].push_back(pii(4, 4));
    edge[4].push_back(pii(7, 0));
    edge[4].push_back(pii(6, 3));

    q.push(pii(0, 0));
    pii p, r;
    while(!q.empty()){
        p = q.top();
        q.pop();

        if(c[p.second] == 1){
            continue;
        }

        for(auto itr = edge[p.second].begin(); itr != edge[p.second].end(); ++itr){
            if(c[itr->second] == 0){
                r.first = itr->first + p.first;
                r.second = itr->second;
                q.push(r);
                //cout<<p.second<<" "<<r.first<<" "<<r.second<<endl;
            }
        }

        d[p.second] = p.first;
        c[p.second] = 1;
    }

    for(int i=0; i<5; ++i){
        cout<<d[i]<<" ";
    }
    cout<<endl;

    return 0;
}