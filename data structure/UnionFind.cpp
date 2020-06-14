#include<iostream>
#include<vector>

using namespace std;

const int NMAX=10100;
int n,q,c,x,y;
int r[NMAX]={0},p[NMAX]={0};

void make(int x){
    for(int i=0;i<x;++i){
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
    cin>>n>>q;

    make(n);

    for(int i=0;i<q;++i){
        cin>>c>>x>>y;
        if(c==0){
            unite(x,y);
        }
        else{
            if(same(x,y)){
                cout<<1<<endl;
            }
            else{
                cout<<0<<endl;
            }
        }
    }

    return 0;
}