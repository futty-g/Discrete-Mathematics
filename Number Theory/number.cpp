#include<iostream>
#include<utility>
#include<cmath>

using namespace std;

long long gcd(long long p, long long q){
    if(p < q){
        return gcd(q, p);
    }
    if(!q){
        return p;
    }
    return gcd(q, p%q);
}

//有理数p/qに対して，分母がn以下で|p/q - b|が最小となる有理数bを求める
pair<long long, long long> sfe(long long p, long long q, long long n){
    long long g1 = 1, g2 = 0, g3;
    long long h1 = 0, h2 = 1, h3;
    long long a;
    long double x = (long double) p / (long double) q;

    long long tmp;
    while(q && h1 <= n){
        a = p / q;
        
        tmp = g1;
        g3 = g2;
        g1 = a * g1 + g2;
        g2 = tmp;
        tmp = h1;
        h3 = h2;
        h1 = a * h1 + h2;
        h2 = tmp;

        tmp = q;
        q = p - a * q;
        p = tmp;

        /*
        cout<<"a="<<a<<endl;
        cout<<"g="<<g1<<endl;;
        cout<<"h="<<h1<<endl;
        cout<<"p="<<p<<endl;
        cout<<"q="<<q<<endl;
        cout<<endl;
        */

    }

    if(h1 <= n){
        tmp = gcd(g1, h1);
        return make_pair(g1 / tmp, h1 / tmp);
    }
    long double y, z;
    long long t = (n - h3) / h2;
    y = (long double) g2 / (long double) h2;
    z = ((long double) (t * g2 + g3)) / ((long double) (t * h2 + h3));

    //cout<<x<<" "<<y<<" "<<z<<endl;

    return abs(x - y) < abs(x - z) ? make_pair(g2 / gcd(g2, h2), h2 / gcd(g2, h2)) : make_pair((t*g2+g3) / gcd(t*g2+g3, t*h2+h3), (t*h2+h3) / gcd(t*g2+g3, t*h2+h3));
}

int main(){

    pair<long long, long long> p = sfe(7, 1, 4);

    cout<<p.first<<" "<<p.second<<endl;

    return 0;
}