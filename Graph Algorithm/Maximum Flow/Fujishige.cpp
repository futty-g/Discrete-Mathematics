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

class Fujishige{
    // 最大フローを求めるアルゴリズム
    public:
        struct edge{
            int to, rev;
            nat cap, flow;
        };
        vector<vector<edge> > resi_e; // 残余グラフの辺集合
        int n; // 頂点数
        

        Fujishige(){}
        Fujishige(int size){
            n = size;
            resi_e.resize(n);
            for(int i=0; i<n; ++i){
                resi_e[i].resize(0);
            }
        }

        void add_dir_edge(int s, int t, nat cap){
            edge e1 {t, (int)resi_e[t].size(), cap, 0};
            edge e2 {s, (int)resi_e[s].size(), 0, -1};
            resi_e[s].push_back(e1);
            resi_e[t].push_back(e2);
        }

        // 最大フローを求める．
        nat solve(int s, int t){
            nat ret = 0, alpha = -1;
            for(int i=0; i<n; ++i){
                for(auto itr=resi_e[i].begin(); itr!=resi_e[i].end(); ++itr){
                    //if(itr->flow != -1){
                    //    itr->flow = 0;
                    //    alpha = max(alpha, itr->cap);
                    //}
                    alpha = max(alpha, itr->cap);
                }
            }
            if(!alpha){
                return ret;
            }
            //cout<<"AAAA"<<endl;
            vector<nat> b, beta;
            vector<int> q, v, x, y;
            b.resize(n);
            q.resize(n);
            v.resize(n);
            y.resize(n);
            beta.resize(n);
          
            while(true){
                for(int i=0; i<n; ++i){
                    b[i] = 0;
                    q[i] = 0;
                    v[i] = -1;
                    y[i] = 0;
                }
                int k=0;
                v[k] = s;
                q[s] = 1;
                x.resize(0);
                //while(x.size()){
                //    x.pop_back();
                //}
                
                while(true){
                    for(auto itr=resi_e[v[k]].begin(); itr!=resi_e[v[k]].end(); ++itr){
                        if(!q[itr->to]){
                            b[itr->to] += itr->cap;
                            if(b[itr->to] >= alpha && y[itr->to] == 0){
                                y[itr->to] = 1;
                                x.push_back(itr->to);
                            }
                        }
                    }

                    if(!x.size()){
                        alpha /= 2;
                        if(!alpha){
                            return ret;
                        }
                        k = 0;
                        break;
                    }

                    v[++k] = x[x.size()-1];
                    q[v[k]] = 1;
                    x.pop_back();
                    if(v[k] == t){
                        break;
                    }
                }

                if(k){
                    beta[t] = alpha;
                    for(int i=0; i<n; ++i){
                        if(i != t){
                            beta[i] = 0;
                        }
                    }
                }
                while(k){
                    for(auto itr=resi_e[v[k]].begin(); itr!=resi_e[v[k]].end(); ++itr){
                        int p = itr->to, num = itr->rev;
                        if(!q[p]){
                            continue;
                        }
                        int num2 = resi_e[p][num].rev;
                        nat bb = min(beta[v[k]], resi_e[p][num].cap);
                        resi_e[p][num].cap -= bb;
                        if(resi_e[p][num].flow != -1){
                            resi_e[p][num].flow += bb;
                        }
                        resi_e[v[k]][num2].cap += bb;
                        if(resi_e[v[k]][num2].flow != -1){
                            resi_e[v[k]][num2].flow -= bb;
                        }
                        beta[v[k]] -= bb;
                        beta[p] += bb;
                        if(v[k] == t){
                            ret += bb;
                        }
                        q[v[k]] = 0;
                    }
                    k--;
                }
                /*
                cout<<"---alpha="<<alpha<<"---\n";
                for(int i=0; i<n; ++i){
                    for(auto itr=resi_e[i].begin(); itr!=resi_e[i].end(); ++itr){
                        cout<<i<<"->"<<itr->to<<" : "<<itr->cap<<endl;
                    }
                }
                cout<<"---\n";
                */
            }
        }
    
};

int main(){

    int n, m;
    int u, v, c;

    cin>>n>>m;
    Fujishige fj(n);
    for(int i=0; i<m; ++i){
        cin>>u>>v>>c;
        fj.add_dir_edge(u, v, c);
    }

    nat ret = fj.solve(0, n-1);

    cout<<ret<<endl;
    return 0;

    for(int i=0; i<n; ++i){
        for(auto itr=fj.resi_e[i].begin(); itr!=fj.resi_e[i].end(); ++itr){
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