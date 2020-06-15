#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>

#define eps 1e-8
#define NMAX 100
using namespace std;
typedef vector<double> vec;
typedef vector<vec> mat;
int col[NMAX];
int r;

mat gauss(mat A, vec b){
    /*
    GaussianEliminationの特殊な場合として，Ax = b を解く
    */
    int n = A.size();
    mat Z(n, vec(n+1));
    // Zの初期化
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            Z[i][j] = A[i][j];
        }
        Z[i][n] = b[i];
    }

    r = 0;
    while(r < n){
        double z_pq = Z[r][r];
        int p = r, q = r;
        for(int i=r; i<n; ++i){
            for(int j=r; j<n; ++j){
                if(abs(z_pq) < abs(Z[i][j])){
                    z_pq = Z[i][j];
                    p = i;
                    q = j;
                }
            }
        }
        if(abs(z_pq) < eps){
            break;
        }

        if(p != r){
            for(int j=0; j<n+1; ++j){
                swap(Z[p][j], Z[r][j]); //行pとrの交換
            }
            swap(row[p], row[r]);
        }

        if(q != r){
            for(int i=0; i<n; ++i){
                swap(Z[i][q], Z[i][r]); //列qとrの交換
            }
            swap(col[q], col[r]);
        }

        double alpha;
        for(int i=r+1; i<n; ++i){
            alpha = Z[i][r] / Z[r][r];
            for(int j=r; j<n+1; ++j){
                Z[i][j] -= alpha * Z[r][j];
            }
        }
        r++;
    }

    for(int k=r-1; k >= 1; --k){
        for(int i=0; i<=k-1; ++i){
            double alpha = Z[i][k] / Z[k][k];
            for(int j=k; j<n+1; ++j){
                Z[i][j] -= alpha * Z[k][j];
            }
        }
    }
    for(int k=0; k<r; ++k){
        double alpha = Z[k][k];
        for(int j=0; j<n+1; ++j){
            Z[k][j] /= alpha;
        }
    }

    return Z;
}

int main(){


    return 0;
}