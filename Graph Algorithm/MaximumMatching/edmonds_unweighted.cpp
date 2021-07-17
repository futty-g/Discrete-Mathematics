#include<iostream>
#include<algorithm>
#include<vector>
#include<utility>

//using namespace std;

class Graph{
    public:
        std::vector<std::vector<int>> edges; // 辺集合
        std::vector<int> matching; // マッチングの辺を管理する
        std::vector<int> alt_edges; // 交互森の辺のうち, マッチングに含まれないものを管理する
        std::vector<int> basis; // 偶花の基を管理する
        std::vector<bool> scanned; // 走査済みの頂点を管理する
        bool show;

        Graph(int n){
            this->edges.resize(n);
            this->alt_edges.resize(n);
            this->basis.resize(n);
            this->matching.resize(n);
            this->scanned.resize(n);
            this->reset_alt_edges(n);
            this->reset_basis(n);
            this->reset_matching(n);
            this->reset_scanned(n);
            this->vsize = n; // 頂点数
            this->show = false; 
        }

        void add_edge(int u, int v){
            this->edges[u].push_back(v);
            this->edges[v].push_back(u);
        }

        int Edmonds(bool greedy = false){
            // 初期化
            int vsize = this->vsize;
            this->reset_alt_edges(vsize);
            this->reset_basis(vsize);
            this->reset_matching(vsize);
            this->reset_scanned(vsize);
            bool show = this->show;


            std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> e; 
            for(int u=0; u<vsize; u++){
                for(auto itr=this->edges[u].begin(); itr != this->edges[u].end(); itr++){
                    int t = *itr;
                    int du = this->edges[u].size();
                    int dt = this->edges[t].size();
                    int d = du < dt ? du : dt;
                    int D = du >= dt ? du : dt;
                    e.push_back({{d, D}, {u, t}});
                }
            }
            std::sort(e.begin(), e.end());
            for(auto itr = e.begin(); itr != e.end(); itr++){
                //std::cout<<itr->first.first<<' '<<itr->first.second<<' '<<itr->second.first<<' '<<itr->second.second<<std::endl;
                int u = itr->second.first, t = itr->second.second;
                if(this->matching[u] == u && this->matching[t] == t){
                    this->matching[u] = t;
                    this->matching[t] = u;
                }
            }


            int v, y;
            bool f1, f2, f3;
            while((v = this->allScanned()) != -1){
            //while(!v_outer.empty()){
                //v = v_outer.front();
                //if(show) std::cout<<"outer: "<<v<<std::endl;
                for(auto itr=this->edges[v].begin(); itr!=this->edges[v].end(); itr++){
                    /*
                    for(int i=0; i<vsize; i++){
                        std::cout<<this->basis[i]<<" ";
                    }
                    std::cout<<std::endl;
                    */
                    y = *itr;
                    f1 = this->isOuter(y);
                    f2 = this->basis[v] != this->basis[y];
                    f3 = this->isOutOfForest(y);
                    if(f3){
                        //if(show) std::cout<<"grow: "<<y<<std::endl;
                        this->grow(v, y);
                        bool f = true;
                    }
                    else if(f1 && f2){
                        if(get_pv(v, 0) != get_pv(y, 1)){
                            //if(show) std::cout<<"augment: "<<y<<std::endl;
                            this->augment(v, y);
                            v = -1;
                            break;
                        }
                        else{
                            //if(show) std::cout<<"shrink: "<<y<<std::endl;
                            int r = this->get_first_base();
                            this->shrink(v, y, r);
                        }
                    }
                }
                if(v > -1){
                    this->scanned[v] = true;
                }
            }

            return this->countMatching();
        }

    private:
        enum{
            OUTER, 
            INNER, 
            OUT_OF_FOREST,  
        };
        std::vector<int> path[2];
        int vsize;

        int allScanned(){
            for(int i=0; i<this->vsize; i++){
            //for(int i=this->vsize-1; i>=0; i--){
                if(!this->scanned[i] && this->isOuter(i)){
                    return i;
                }
            }
            return -1;
        }

        void augment(int x, int y){
            // 交互パスに沿って増加操作を行う
            int v, w;
            for(int num=0; num<2; num++){
                std::vector<int> pv = this->path[num];
                for(int i=0; i<(int)pv.size(); i++){
                    if(i & 1){
                        v = pv[i];
                        w = this->alt_edges[v];
                        this->matching[w] = v;
                        this->matching[v] = w;
                    }
                }
            }
            this->matching[x] = y;
            this->matching[y] = x;
            this->reset_alt_edges(this->vsize);
            this->reset_basis(this->vsize);
            this->reset_scanned(this->vsize);
        }

        int countMatching(){
            // マッチングに含まれる辺数を数える
            int ret = 0, to, vsize=this->vsize;
            for(int i=0; i<vsize; i++){
                to = this->matching[i];
                ret += (to < i) ? 1 : 0;
            }
            return ret;
        }

        int get_first_base(){
            // px と py を根に向かってたどった際に, 
            // px と py 両方に現れる最初の基を求める
            std::vector<bool> flag(this->vsize, false);
            std::vector<int> px = this->path[0];
            std::vector<int> py = this->path[1];
            for(auto itr=px.begin(); itr!=px.end(); itr++){
                flag[*itr] = true;
            }
            int v, r = -1;
            for(int i=py.size()-1; i>=0; i--){
                v = py[i];
                if(flag[v] && this->basis[v] == v){
                    r = v;
                }
            }
            return r;
        }

        int get_pv(int v, int num){
            // v から交互森の根へのパスを求める
            this->path[num].clear();
            int x = v, cnt=0;
            while(true){
                this->path[num].push_back(x);
                if(this->alt_edges[x] == x && this->matching[x] == x){
                    break;
                }
                if(cnt){
                    x = this->alt_edges[x];
                }
                else{
                    x = this->matching[x];
                }
                cnt ^= 1;
            }
            if(this->show){
                for(auto itr=this->path[num].begin(); itr!=this->path[num].end(); itr++){
                    std::cout<<*itr<<"->";
                }
                std::cout<<std::endl;
            }

            return x;
        }

        void grow(int x, int y){
            // 交互森を拡張する
            this->alt_edges[y] = x;
        }

        bool isOuter(int n){
            // 頂点 n が偶点であるか否か判定
            bool f1, f2;
            f1 = this->matching[n] == n;
            f2 = this->alt_edges[this->matching[n]] != this->matching[n];
            return f1 || f2;
        }

        bool isInner(int n){
            // 頂点 n が奇点であるか否か判定
            bool f1, f2;
            f1 = this->alt_edges[this->matching[n]] == this->matching[n];
            f2 = this->alt_edges[n] != n;
            return f1 && f2;
        }

        bool isOutOfForest(int n){
            // 頂点 n が森外であるか否か判定
            bool f1, f2, f3;
            f1 = this->matching[n] != n;
            f2 = this->alt_edges[this->matching[n]] == this->matching[n];
            f3 = this->alt_edges[n] == n;
            return f1 && f2 && f3;
        }

        void reset_alt_edges(int n){
            //this->alt_edges.resize(n);
            for(int i=0; i<n; i++){
                this->alt_edges[i] = i;
            }
        }

        void reset_basis(int n){
            //this->basis.resize(n);
            for(int i=0; i<n; i++){
                this->basis[i] = i;
            }
        }
        
        void reset_matching(int n){
            //this->matching.resize(n);
            for(int i=0; i<n; i++){
                this->matching[i] = i;
            }
        }
        
        void reset_scanned(int n){
            //this->scanned.resize(n);
            for(int i=0; i<n; i++){
                this->scanned[i] = false;
            }
        }

        void shrink(int x, int y, int r){
            // 偶花 x->r, y->r, x->y を基 r に縮約
            int v, w;
            std::vector<bool> flag(this->vsize, false);
            for(int num=0; num<2; num++){
                std::vector<int> pv = this->path[num];
                for(int i=0;; i++){
                    v = pv[i];
                    w = this->alt_edges[v];
                    if((i & 1) && (this->basis[w] != r)){
                        this->alt_edges[w] = v;
                    }
                    flag[v] = true;
                    if(v == r){
                        break;
                    }
                }
            }
            if(this->basis[x] != r){
                this->alt_edges[x] = y;
            }
            if(this->basis[y] != r){
                this->alt_edges[y] = x;
            }
            /*
            std::vector<bool> flag(this->vsize, false);
            for(int num=0; num<2; num++){
                std::vector<int> pv = this->path[num];
                for(int i=0;; i++){
                    v = pv[i];
                    flag[v] = true;
                    if(v == r){
                        break;
                    }
                }
            }
            */
            for(int i=0; i<this->vsize; i++){
                if(flag[this->basis[i]]){
                    this->basis[i] = r;
                }
            }
        }
};

void query(bool show){

    int n, m;
    std::cin>>n>>m;
    Graph g = Graph(n);
    
    int u, v;
    for(int i=0; i<m; i++){
        std::cin>>u>>v;
        g.add_edge(u, v);
    }

    g.show = show;
    //g.Edmonds();
    std::cout<<g.Edmonds(true)<<std::endl;;
    for(int i=0; i<n; i++){
        //int m = i == g.matching[i] ? -1 : g.matching[i];
        //std::cout<<m<<" ";
        if(i < g.matching[i]){
            std::cout<<i<<" "<<g.matching[i]<<std::endl;
        }
    }
    //std::cout<<std::endl;

    //return 0;
}


signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); 

    int t;
    t = 1;
    //std::cin>>t;
    //bool f = true;
    bool f = false;
    while(t){
        query(f);    
        t--;
    }
    
    return 0;
}