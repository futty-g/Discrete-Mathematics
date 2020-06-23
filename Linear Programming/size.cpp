#include"size.h"
#include<cmath>
#include<boost/rational.hpp>
#include<boost/numeric/ublas/vector.hpp>
#include<boost/numeric/ublas/io.hpp>
#include<boost/numeric/ublas/matrix.hpp>

using namespace std;
namespace ublas = boost::numeric::ublas;

long long size(long long n){
    long long m = 1 + (n >= 0 ? n : -n);
    long long s = 0;
    long long cnt = 0;
    while(m > 1){
        s |= (m % 2);
        m /= 2;
        cnt++;
    } 
    return 1+cnt+s;
}

long long size(boost::rational<long long> r){
    long long p = r.numerator();
    long long q = r.denominator();
    return size(p) + size(q);
}
/*
long long size(ublas::vector<long long> b){
    long long m = b.size();
    long long r = 0;
    for(int i = 0; i<m; ++i){
        r += size(b[i]);
    }
    return r + m;
}
*/

long long size(ublas::vector<boost::rational<long long>> b){
    long long m = b.size();
    for(auto itr = b.begin(); itr != b.end(); ++itr){
        m += size(*itr);
    }
    return m;
}

long long size(ublas::matrix<boost::rational<long long>> A){
    long long m = 0;

    for(auto itr1 = A.begin1(); itr1 != A.end1(); ++itr1){
        for(auto itr2 = itr1.begin(); itr2 != itr1.end(); ++itr2){
            m += 1+size((*itr2));
        }
    }
    return m;
}
