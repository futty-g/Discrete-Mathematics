#include<iostream>

#define NMAX 1000
#define D 300
using namespace std;

/*
    開平計算
*/


int a[NMAX] = {0}, b[NMAX] = {0}, c[NMAX] = {0};
int d[NMAX] = {0}, e[NMAX] = {0}, f[NMAX] = {0};

int leq(int *x, int *y){
    for(int i=NMAX-1; i>=0; --i){
        if(x[i] > y[i]){
            return 0;
        }
        else if(x[i] < y[i]){
            return 1;
        }
    }
    return 1;
}

void append(int *x, int n){
    for(int i=NMAX-1; i>0; --i){
        x[i] = x[i-1];
    }
    x[0] = n;
}

void update(int *f){
    for(int i=0; i<NMAX-2; ++i){
        f[i] = f[i+2];
    }
    f[NMAX-2] = 0;
    f[NMAX-1] = 0;
}

int find(int *x, int *y){
    int s = 0;
    for(int i=9; i>=0; --i){
        e[0] = i*i;
        s = e[0] / 10;
        e[0] %= 10;
        for(int j=0; j<NMAX-1; ++j){
            e[j+1] = x[j] * i + s;
            s = e[j+1] / 10;
            e[j+1] %= 10;
        }
        for(int j=0; j<NMAX; ++j){
            d[j] = y[j];
        }

        if(leq(e, d)){
            for(int j=0; j<NMAX-1; ++j){
                y[j] = 0;
                if(d[j] < e[j]){
                    y[j] = 10;
                    d[j+1]--;
                }
                y[j] += d[j] - e[j];
            }
            append(y, f[0]);
            append(y, f[1]);
            update(f);

            return i;
        }
    }
    return -1;
}

int calc(int n){
    for(int i=0; i<NMAX; ++i){
        a[i] = 0;
        b[i] = 0;
        c[i] = 0;
        d[i] = 0;
        e[i] = 0;
        f[i] = 0;
    }

    int k = 0;
    while(n >= 100){
        f[k++] = n % 10;
        n /= 10;
        f[k++] = n % 10;
        n /= 10;
    }
    a[0] = n % 10;
    a[1] = n / 10;

    for(int i=0; i<D; ++i){
        int m = find(b, a);
        append(b, 2*m);
        append(c, m);
        for(int j=0; j<NMAX-1; ++j){
            b[j+1] += b[j] / 10;
            b[j] %= 10;
        }
    }

    for(int i=0; i<D; ++i){
        cout<<c[D - i - 1];
        if(i == k/2){
            cout<<'.';
        }
    }
    cout<<endl;
}

int main(){

    calc(2);

    return 0;
}