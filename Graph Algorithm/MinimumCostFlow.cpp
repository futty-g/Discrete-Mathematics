#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

#define NMAX 110
#define CMAX 1000000007
using namespace std;
typedef pair<int, int> pii;
int c[110][110] = {0};
int d[110][110] = {0};
int dist[110];
int path[110];

int Dijkstra(vector<int> *g, int s, int t){
    priority_queue<pair<int, pii>, vector<pair<int, pii> >, greater<pair<int, pii> > > q;
    q.push(make_pair(0, pii(s, s)));
    for(int i=0; i<NMAX; ++i){
        dist[i] = CMAX;
        path[i] = -1;
    }
    dist[s] = 0;
    int u, v, w;
    while(!q.empty()){
        u = q.top().second.second;
        v = q.top().second.first;
        w = q.top().first;
        dist[u] = min(dist[u], w);
        if(path[u] == -1)path[u] = v;
        q.pop();
        for(int i=0; i<g[u].size(); ++i){
            if(c[u][g[u][i]] && path[g[u][i]] == -1){
                q.push(make_pair(dist[u]+d[u][g[u][i]], pii(u,g[u][i])));
            }
        }
    }
    return dist[t];
}

int main(){
    // 逐次最短路法により最小費用流問題を解く．

    vector<int> g[NMAX], resig[NMAX];
    int u, v, s, t;
    int n, m, f;
    int x = 0, p[NMAX] = {0}, res = 0;
    int r[NMAX][NMAX] = {0}, e[NMAX][NMAX] = {0};
    cin>>n>>m>>f;
    for(int i=0; i<m; ++i){
        cin>>u>>v>>s>>t;
        c[u][v] = s;
        d[u][v] = t, d[v][u] = -t;
        r[u][v] = t, r[v][u] = -t;
        e[u][v] = 1, e[v][u] = -1;
        g[u].push_back(v);
        resig[u].push_back(v);
        resig[v].push_back(u);
    }

    int a, dx = 0, k;
    while(dx != f){
        if(Dijkstra(resig, 0, n-1) == CMAX){
            cout<<-1<<endl;
            return 0;
        }
        for(int i=0; i<n; ++i){
            p[i] -= dist[i];
        }
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                if(e[i][j])d[i][j] = r[i][j] + p[j] - p[i];
            }
        }
        a = f - dx;
        k = n-1;
        while(true){
            if(k == path[k]){
                break;
            }
            a = min(a, c[path[k]][k]);
            k = path[k];
        }

        k = n-1;
        while(true){
            if(k == path[k]){
                break;
            }
            c[k][path[k]] += a;
            c[path[k]][k] -= a;
            res += r[path[k]][k]*a;
            k = path[k];
        }
        dx += a;
    }

    cout<<res<<endl;

    return 0;
}