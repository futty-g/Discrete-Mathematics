#include<iostream>
#include<vector>
#include<utility>
#include<queue>

#define NMAX 100

using namespace std;

typedef long long nat;
typedef pair<int, int> pii;
typedef pair<nat, int> pni;
typedef pair<nat, pair<int, int> > pnii;

class Dijkstra{
    // 正の重みをもつグラフの最短路を求めるアルゴリズム
    public:
        vector<vector<pni>> edge; // 辺集合
        vector<nat> l; // ポテンシャル
        vector<int> p; // 最短路における parent
        int n; // 頂点数

        Dijkstra(){}
        Dijkstra(int size){
            l.resize(size);
            p.resize(size);
            edge.resize(size);
            for(int i=0; i<size; ++i){
                edge[i].resize(0);
                l[i] = -1;
                p[i] = -1;
            }
            n = size;
        }

        void add_dir_edge(int s, int t, nat c){
            edge[s].push_back(pni (c, t));
        }

        void add_edge(int s, int t, nat c){
            add_dir_edge(s, t, c);
            add_dir_edge(t, s, c);
        }

        // 頂点 s から t への最短路を求める．
        nat solve(int s, int t){
            l[s] = 0;
            queue<pnii> q;
            int u, v;
            nat c;
            for(auto itr=edge[s].begin(); itr != edge[s].end(); ++itr){
                c = itr->first;
                u = itr->second;
                if(l[u] == -1 || l[u] > l[s]+c){
                    l[u] = l[s] + c;
                    p[u] = s;
                    q.push(pnii (c, pii (u, s)));
                }
            }
            while(!q.empty()){
                c = q.front().first;
                u = q.front().second.first;
                v = q.front().second.second;
                q.pop();

                for(auto itr=edge[u].begin(); itr != edge[u].end(); ++itr){
                    c = itr->first;
                    v = itr->second;
                    if(l[v] == -1 || l[v] > l[u]+c){
                        l[v] = l[u] + c;
                        p[v] = u;
                        q.push(pnii (c, pii (v, u)));
                    }
                }                
            }

            return l[t];
        }
};

int main(){

    int n, m, r;
    int s, t, d;

    cin>>n>>m>>r;

    Dijkstra dj = Dijkstra(n);

    for(int i=0; i<m; ++i){
        cin>>s>>t>>d;
        dj.add_dir_edge(s, t, d);
    }

    dj.solve(r, n-1);


    for(int i=0; i<n; ++i){
        if(dj.l[i] != -1){
            cout<<dj.l[i]<<endl;
        }
        else{
            cout<<"INF"<<endl;
        }
    }

    return 0;
}