#include<iostream>
#include<cmath>

using namespace std;

/*
    素数列挙(エラトステネスの篩)，
    素因数分解，
    Eulerの\phi関数
*/

int prime[20000] = {0};
int e[20000];
int pn;

int eratos(int n){
    int k = 0;
    int f;
    for(int i=2; i<=n; ++i){
        f = 1;
        for(int j=0; j<k; ++j){
            if(!(i%prime[j])){
                f = 0;
                break;
            }
        }
        if(f){
            prime[k++] = i;
        }
    }
    return k;
}

void factorize(int n){
    for(int i=0; i<pn+1; ++i){
        e[i] = 0;
    }
    for(int i=0; i<pn; ++i){
        while(!(n%prime[i])){
            e[i]++;
            n /= prime[i];
        }
    }
    e[pn] = n;
}

long long phi(int n){
    factorize(n);
    long long res = 1;
    long long s, t;
    for(int i=0; i<pn; ++i){
        if(e[i]){
            s = (long long)pow(prime[i], e[i]);
            t = (long long)pow(prime[i], e[i] - 1);
            res *= (s - t);
        }
    }
    if(e[pn] != 1){
        res *= (e[pn] - 1);
    }

    return res;
}

int main(){
    pn = eratos(1000);

    for(int i=2; i<=1000; ++i){
        cout<<phi(i)<<endl;
    }

    return 0;
}