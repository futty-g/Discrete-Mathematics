#include<iostream>
#include<vector>
#include<utility>

#define INFTY 10101010101010101

using namespace std;

typedef long long nat;
typedef pair<int, int> pii;
typedef pair<nat, int> pni;
typedef pair<nat, pair<int, int> > pnii;

class FloydWarshall{
    // 負閉路をもたない有向グラフの最短路を求めるアルゴリズム
    public:
        vector<pnii> edge; // 辺集合
        vector<vector<nat> > l; // ポテンシャル
        vector<vector<int> > p; // 最短路における parent
        int n; // 頂点数

        FloydWarshall(){}
        FloydWarshall(int size){
            l.resize(size);
            p.resize(size);
            edge.resize(0);
            for(int i=0; i<size; ++i){
                l[i].resize(size);
                p[i].resize(size);
                for(int j=0; j<size; ++j){
                    l[i][j] = INFTY;
                    p[i][j] = -1;
                }
            }
            n = size;
        }

        void add_dir_edge(int s, int t, nat c){
            edge.push_back(pnii (c, pii (s, t)));
        }

        // 全点間の最短路を求める．
        int solve(){
            int s, t;
            nat c;
            for(int i=0; i<n; ++i){
                l[i][i] = 0;
                p[i][i] = i;
            }
            for(auto itr=edge.begin(); itr != edge.end(); ++itr){
                c = itr->first;
                s = itr->second.first;
                t = itr->second.second;
                l[s][t] = c;
                p[s][t] = s;
            }

            for(int j=0; j<n; ++j){
                for(int i=0; i<n; ++i){
                    if(l[i][j] == INFTY){
                        continue;
                    }
                    for(int k=0; k<n; ++k){
                        if(l[j][k] == INFTY){
                            continue;
                        }
                        if(l[i][k] > l[i][j]+l[j][k]){
                            l[i][k] = l[i][j]+l[j][k];
                            p[i][k] = p[j][k];
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
            

            int s=-1, t=-1, u, v;
            nat c;
            for(int i=0; i<n; ++i){
                for(int i=0; i<n; ++i){
                    visited[i] = 0;
                }    
                for(auto itr=edge.begin(); itr!=edge.end(); ++itr){
                    u = itr->second.first;
                    v = itr->second.second;
                    c = itr->first;
                    if(l[i][u] == INFTY || l[i][v] == INFTY){
                        continue;
                    }
                    if(l[i][v] > l[i][u]+c){
                        return 0;
                    }
                }
            }
            
            return -1;
        }
};

int main(){

    int n, m, r;
    int s, t, d;

    cin>>n>>m;

    FloydWarshall fw = FloydWarshall(n);

    for(int i=0; i<m; ++i){
        cin>>s>>t>>d;
        fw.add_dir_edge(s, t, d);
    }

    
    int f = fw.solve();
    if(f != -1){
        cout<<"NEGATIVE CYCLE"<<endl;
        return 0;
    }

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(fw.l[i][j] != INFTY){
                cout<<fw.l[i][j];
            }
            else{
                cout<<"INF";
            }
            if(j != n-1){
                cout<<" ";
            }
        }
        cout<<endl;
    }

    return 0;
}