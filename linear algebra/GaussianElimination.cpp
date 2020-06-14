#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>

#define eps 1e-8
#define NMAX 100
#define MMAX 100
using namespace std;
typedef vector<double> vec;
typedef vector<vec> mat;
int row[NMAX], col[MMAX];
int r;
double d;


mat gauss(mat A){
    /*
    行列A \in R^{m*n}の極大な正則部分行列A', rank A', det A', A'^(-1)を求める
    */
    int m = A.size();
    int n = A[0].size();
    mat Z(m, vec(n+m));
    // Zの初期化
    for(int i=0; i<m; ++i){
        for(int j=0; j<n; ++j){
            Z[i][j] = A[i][j];
            if(i == j){
                Z[i][n+j] = 1;
            }
            else{
                Z[i][n+j] = 0;
            }
        }
    }

    while(r < n-1 && r < m - 1){
        double z_pq = Z[r][r];
        int p = r, q = r;
        for(int i=r; i<m; ++i){
            for(int j=r; j<n; ++j){
                if(z_pq < Z[i][j]){
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
            for(int j=0; j<n+m; ++j){
                swap(Z[p][j], Z[r][j]); //行pとrの交換
            }
            for(int i=0; i<m; ++i){
                swap(Z[i][n+p], Z[i][n+r]); //列n+pとrn+の交換
            }
            swap(row[p], row[r]);
        }

        if(q != r){
            for(int i=0; i<m; ++i){
                swap(Z[i][q], Z[i][r]); //列qとrの交換
            }
            swap(col[q], col[r]);
        }

        double alpha;
        for(int i=r+1; i<m; ++i){
            alpha = Z[i][r] / Z[r][r];
            for(int j=r; j<n+m; ++j){
                Z[i][j] -= alpha * Z[r][j];
            }
        }
        d *= Z[r][r];
        r++;
    }

    for(int k=r-1; k >= 1; --k){
        for(int i=0; i<k-1; ++i){
            int alpha = Z[i][k] / Z[k][k];
            for(int j=k; j<n+r; ++j){
                Z[i][j] -= alpha * Z[k][j];
            }
        }
    }
    for(int k=0; k<r; ++k){
        double alpha = Z[k][k];
        for(int j=0; j<n+r; ++j){
            Z[k][j] /= alpha;
        }
    }

    return Z;
}

int main(){
    int m, n;
    cin>>m>>n;

    mat A(m, vec(n));
    for(int i=0; i<m; ++i){
        for(int j=0; j<n; ++j){
            cin>>A[i][j];
        }
    }
    for(int i=0; i<m; ++i){
        row[i] = i;
    }
    for(int j=0; j<n; ++j){
        col[j] = j;
    }

    r = 0;
    d = 1.0;
    mat B = gauss(A);
    for(int i=0; i<m; ++i){
        for(int j=0; j<m+n; ++j){
            printf("%.5lf ", B[i][j]);
        }
        cout<<endl;
    }

    for(int i=0; i<m; ++i){
        for(int j=0; j<n; ++j){
            printf("%.5lf ", A[row[i]][col[j]]);
        }
        cout<<endl;
    }
    printf("%d %.5lf\n", r, d);

    return 0;
}