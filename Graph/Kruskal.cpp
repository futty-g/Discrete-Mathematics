#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>

using namespace std;
typedef pair<int,int> pii;

const int VMAX=10000,EMAX=100000;
int v,e,s,t,w,res=0;
int r[VMAX+10]={0},p[VMAX+10]={0};

void make(int v){
    for(int i=0;i<v;++i){
        r[i]=0;
        p[i]=i;
    }
}

void link(int x,int y){
    if(r[x]>r[y]){
        p[y]=x;
    }
    else{
        p[x]=y;
        if(r[x]==r[y]){
            r[y]++;
        }
    }
}

int find(int x){
    if(x!=p[x]){
        return p[x]=find(p[x]);
    }
    return x;
}

void unite(int x,int y){
    link(find(x),find(y));
}

bool same(int x,int y){
    return find(x)==find(y);
}

int main(){
    vector<pair<int,pii>>edge;
    cin>>v>>e;
    make(v);
    for(int i=0;i<e;++i){
        cin>>s>>t>>w;
        edge.push_back(make_pair(w,pii(s,t)));
    }

    sort(edge.begin(),edge.end());
    for(int i=0;i<edge.size();++i){
        if(!same(edge[i].second.second,edge[i].second.first)){
            res+=edge[i].first;
            unite(edge[i].second.second,edge[i].second.first);
        }
    }

    cout<<res<<endl;

    return 0;
}