#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<utility>
#include<queue>

#define NMAX 100
#define INFTY 10101010101

using namespace std;

typedef long long nat;
typedef pair<int, int> pii;
typedef pair<nat, int> pni;
typedef pair<nat, pair<int, int> > pnii;

class EdmondsKarp{
    // 最大フローを求めるアルゴリズム
    public:
        struct edge{
            int to, rev;
            nat cap, flow;
        };
        vector<vector<edge> > resi_e; // 残余グラフの集合
        int n; // 頂点数

        EdmondsKarp(){}
        EdmondsKarp(int size){
            n = size;
            resi_e.resize(n);
            for(int i=0; i<n; ++i){
                resi_e[i].resize(0);
            }
            visited.resize(n);
            p.resize(n);
            aug.resize(n);
        }

        void add_dir_edge(int s, int t, nat cap){
            edge e1 {t, (int)resi_e[t].size(), cap, 0};
            edge e2 {s, (int)resi_e[s].size(), 0, -1};
            resi_e[s].push_back(e1);
            resi_e[t].push_back(e2);
        }

        // 最大フローを求める．
        nat solve(int s, int t){
            nat ret = 0, f;
            while((f = breadth_first_search(s, t)) > 0){
                //cout<<f<<endl;
                ret += f;
                int to = t, from, num;
                while(p[to] != -1){
                    from = resi_e[to][p[to]].to;
                    num = resi_e[to][p[to]].rev;
                    //cout<<from<<" "<<to<<endl;
                    if(resi_e[from][num].flow != -1){
                        resi_e[from][num].flow += f;
                    }
                    else{
                        resi_e[to][p[to]].flow += f;
                    }
                    resi_e[from][num].cap -= f;
                    resi_e[to][p[to]].cap += f;
                    to = from;
                }
            }

            return ret;
        }

        private:
            vector<bool> visited;
            vector<int> p;
            vector<nat> aug;
            nat breadth_first_search(int s, int t){
                queue<int> q;
                q.push(s);
                aug[s] = INFTY;
                
                for(int i=0; i<n; ++i){
                    p[i] = -1;
                    visited[i] = false;
                }
                visited[s] = true;


                int from;
                while(!q.empty()){
                    from = q.front();
                    q.pop();
                    for(auto itr=resi_e[from].begin(); itr!=resi_e[from].end(); ++itr){
                        if(!visited[itr->to] && itr->cap > 0){
                            q.push(itr->to);
                            p[itr->to] = itr->rev;
                            aug[itr->to] = min(aug[from], itr->cap);
                            visited[itr->to] = true;
                        }
                    }
                    if(visited[t]){
                        return aug[t];
                    }
                }

                return -1;
            }
};

int main(){

    int n, m;
    int u, v, c;

    cin>>n>>m;
    EdmondsKarp ek(n);
    for(int i=0; i<m; ++i){
        cin>>u>>v>>c;
        ek.add_dir_edge(u, v, c);
    }

    nat ret = ek.solve(0, n-1);

    cout<<ret<<endl;

    for(int i=0; i<n; ++i){
        for(auto itr=ek.resi_e[i].begin(); itr!=ek.resi_e[i].end(); ++itr){
            int from = i;
            int to = itr->to;
            nat flow = itr->flow;
            if(flow > 0){
                cout<<from<<"->"<<to<<" : "<<flow<<endl;
            }
        }
    }
    
    return 0;
}