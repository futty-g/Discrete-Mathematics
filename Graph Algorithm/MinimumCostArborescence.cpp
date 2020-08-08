#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>

#define VMAX 110
#define EMAX 1010
using namespace std;

struct edge{
    int to, cap;
};

int flag = 0;

vector<edge> g_p[VMAX], g_j[VMAX], g_o[VMAX], g_i[VMAX];
int dist[VMAX], prevv[VMAX+EMAX], numb[VMAX], done[VMAX], found[VMAX], ccl;
vector<int> equi[VMAX];

void init(int n){
    for(int i=0; i<n; ++i){
        numb[i] = i;
        equi[i].clear();
        equi[i].push_back(i);
    }
}

void adde(int from, int to, int cap){
    g_p[from].push_back((edge){to, cap});
    g_j[to].push_back((edge){from, (int)g_p[from].size() - 1});
}

void update(int n, int r){
    vector<edge> g[VMAX], h[VMAX];
    for(int i=0; i<n; ++i){
        done[i] = 0;
    }
    int to, cap;
    for(int i=0; i<n; ++i){
        g[i].clear();
        h[i].clear();
    }
    for(int i=0; i<n; ++i){
        if(i == r){
            continue;
        }
        if(!done[numb[i]]){
            cap = 1000000007;
            for(int j=0; j<equi[numb[i]].size(); ++j){
                for(int k=0; k<g_j[equi[numb[i]][j]].size(); ++k){
                    if(numb[i] != numb[g_j[equi[numb[i]][j]][k].to] && g_p[g_j[equi[numb[i]][j]][k].to][g_j[equi[numb[i]][j]][k].cap].cap < cap){
                        to = g_j[equi[numb[i]][j]][k].to;
                        cap = g_p[g_j[equi[numb[i]][j]][k].to][g_j[equi[numb[i]][j]][k].cap].cap;
                    }
                }
            }
            g[i].push_back((edge){to, (int)h[to].size()});
            h[to].push_back((edge){i, cap});
            done[numb[i]] = 1;
        }
    }
    for(int i=0; i<n; ++i){
        g_i[i] = g[i];
        g_o[i] = h[i];
    }
}

void contract(int u, int v){
    /*
        頂点 u と v を縮約する．
    */
    //
    if(flag)cout<<"contract "<<u<<" "<<v<<endl;
    int s = numb[min(u, v)], t = numb[max(u, v)], b;
    while(!equi[t].empty()){
        b = equi[t].back();
        numb[b] = s;
        equi[s].push_back(b);
        equi[t].pop_back();
    }    
}

void contract_cycle(int s, int w){
    int v = s, u = prevv[s], k, f;
    //
    if(flag)cout<<"v, u, prev[u]= "<<v<<" "<<u<<" "<<prevv[u]<<endl;
    for(int i=0; i<equi[numb[v]].size(); ++i){
        for(int j=0; j<g_j[equi[numb[v]][i]].size(); ++j){
            if(numb[v] != numb[g_j[equi[numb[v]][i]][j].to] && numb[u] != numb[g_j[equi[numb[v]][i]][j].to]){
                f = g_j[equi[numb[v]][i]][j].to;
                k = g_j[equi[numb[v]][i]][j].cap;
                g_p[f][k].cap += dist[numb[u]] - dist[numb[v]];
                //
                if(flag)cout<<"[u= "<<f<<"] "<<g_p[f][k].to<<" "<<g_p[f][k].cap<<endl;
            }
        }
    }
    //contract(v, u);
    while(true){
        v = u;
        u = prevv[u];
        //
        if(flag)cout<<"v, u, prev[u]= "<<v<<" "<<u<<" "<<prevv[u]<<endl;
        
        for(int i=0; i<equi[numb[v]].size(); ++i){
            for(int j=0; j<g_j[equi[numb[v]][i]].size(); ++j){
                if(numb[v] != numb[g_j[equi[numb[v]][i]][j].to] && numb[u] != numb[g_j[equi[numb[v]][i]][j].to]){
                    f = g_j[equi[numb[v]][i]][j].to;
                    k = g_j[equi[numb[v]][i]][j].cap;
                    g_p[f][k].cap += w + dist[numb[u]] - dist[numb[v]];
                    //
                    if(flag)cout<<"[u= "<<f<<"] "<<g_p[f][k].to<<" "<<g_p[f][k].cap<<endl;
                }
            }
        }
        if(u == s){
            break;
        }
        //contract(v, u);
    }
    while(true){
        v = u;
        u = prevv[u];
        if(u == s){
            break;
        }
        contract(v, u);
    }
    return;
}

int find_cycle(int n, int root){
    int ret = 0;
    for(int i=0; i<VMAX; ++i){
        dist[i] = -1;
        prevv[i] = -1;
        found[i] = -1;
    }
    stack<int> st;
    int u, v, w;
    for(int k=0; k<n; ++k){
        if(found[k] < 0){
            st.push(k);
            dist[numb[k]] = 0;
            prevv[k] = k;
            found[k] = k;
            while(!st.empty()){
                u = st.top();
                st.pop();
                //
                if(flag)cout<<"u = "<<u<<endl;
                for(int j=0; j<equi[u].size(); ++j){
                    for(int i=0; i<g_o[equi[u][j]].size(); ++i){
                        v = g_o[equi[u][j]][i].to;
                        w = g_o[equi[u][j]][i].cap;
                        ret += w;
                        prevv[numb[v]] = numb[u];
                        //
                        if(flag)cout<<"v,w= "<<v<<" "<<w<<endl;
                        if(found[numb[v]] < 0){
                            st.push(numb[v]);
                            found[numb[v]] = k;
                            dist[numb[v]] = dist[numb[u]] + w;
                        }
                        else if(found[numb[v]] == k){
                            ccl = numb[v];
                            return w + dist[numb[u]] - dist[numb[v]];
                        }
                    }
                }
            }
        }
    }

    return -1-ret;
}

void print_graph(int n);

int edmonds(int n, int r){
    int ret;
    init(n);
    while(true){
        update(n, r);
        //
        if(flag)print_graph(n);
        if((ret = find_cycle(n, r)) < 0){
            return -(ret + 1);
        }
        //cout<<"ret= "<<ret<<endl;
        contract_cycle(ccl, ret);

        //
        if(flag){
            cout<<"====numb[]===="<<endl;
            for(int i=0; i<n; ++i){
                cout<<"[v= "<<i<<"] " <<numb[i]<<endl;
            }
            cout<<"============"<<endl;
        }
    }
}

int main(){
    int e, v, r, s, t, w;
    cin>>v>>e>>r;
    for(int i=0; i<e; ++i){
        cin>>s>>t>>w;
        adde(s, t, w);
    }

    //print_graph(v);
    int res = edmonds(v, r);
    cout<<res<<endl;

    return 0;
}

void print_graph(int n){
    for(int i=0; i<n; ++i){
        cout<<"[v= "<<i<<"] ";
        for(int j=0; j<g_o[i].size(); ++j){
            cout<<g_o[i][j].to<<" "<<g_o[i][j].cap<<", ";
        }
        cout<<endl;
    }
    cout<<"-----------"<<endl;
    for(int i=0; i<n; ++i){
        cout<<"[v= "<<i<<"] ";
        for(int j=0; j<g_i[i].size(); ++j){
            cout<<g_i[i][j].to<<" "<<g_i[i][j].cap<<", ";
        }
        cout<<endl;
    }
    cout<<"============"<<endl;
}