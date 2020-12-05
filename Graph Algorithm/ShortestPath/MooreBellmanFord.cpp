#include<iostream>
#include<vector>
#include<utility>

#define NMAX 100
#define INFTY 101010101

using namespace std;

typedef long long nat;
typedef pair<int, int> pii;
typedef pair<nat, int> pni;
typedef pair<nat, pair<int, int> > pnii;

class MooreBellmanFord{
    // 負閉路をもたない有向グラフの最短路を求めるアルゴリズム
    public:
        vector<vector<pni>> edge; // 辺集合
        vector<nat> l; // ポテンシャル
        vector<int> p; // 最短路における parent
        int n; // 頂点数

        MooreBellmanFord(){}
        MooreBellmanFord(int size){
            l.resize(size);
            p.resize(size);
            edge.resize(size);
            for(int i=0; i<size; ++i){
                edge[i].resize(0);
                l[i] = INFTY;
                p[i] = -1;
            }
            n = size;
        }

        void add_dir_edge(int s, int t, nat c){
            edge[s].push_back(pni (c, t));
        }

        // 頂点 s から t への最短路を求める．
        int solve(int s){
            int v;
            nat c;
            l[s] = 0;
            for(int i=0; i<n; ++i){
                for(int u=0; u<n; ++u){
                    if(l[u] == INFTY){
                        continue;
                    }
                    for(auto itr=edge[u].begin(); itr!=edge[u].end(); ++itr){
                        v = itr->second;
                        c = itr->first;
                        if(l[v] > l[u]+c){
                            l[v] = l[u]+c;
                            p[v] = u;
                        }      
                    }
                }
            }

            return detect_cycle();
        }

    private:

        vector<int> visited;

        int detect_cycle(){
            visited.resize(n);
            for(int i=0; i<n; ++i){
                visited[i] = 0;
            }

            int s=-1, t=-1, v;
            nat c;
            for(int u=0; u<n-1; ++u){
                if(l[u] == INFTY){
                    continue;
                }
                for(auto itr=edge[u].begin(); itr!=edge[u].end(); ++itr){
                    v = itr->second;
                    c = itr->first;
                    if(l[v] > l[u]+c){
                        s = u;
                        t = v;
                    }  
                }
            }
            if(s != -1){
                visited[s] = 1;
                visited[t] = 1;
                while(!visited[p[s]]){
                    visited[p[s]] = 1;
                    s = p[s];
                }
            }
            return s;
        }
};

int main(){

    int n, m, r;
    int s, t, d;

    cin>>n>>m>>r;

    MooreBellmanFord mbf = MooreBellmanFord(n);

    for(int i=0; i<m; ++i){
        cin>>s>>t>>d;
        mbf.add_dir_edge(s, t, d);
    }

    
    int f = mbf.solve(r);
    if(f != -1){
        cout<<"NEGATIVE CYCLE"<<endl;
        return 0;
    }

    for(int i=0; i<n; ++i){
        if(mbf.l[i] != INFTY){
            cout<<mbf.l[i]<<endl;
        }
        else{
            cout<<"INF"<<endl;
        }
    }

    return 0;
}