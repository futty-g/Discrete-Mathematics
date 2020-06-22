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

long long size(ublas::vector<boost::rational<long long>>){
    return 0;
}
long long size(ublas::matrix<long long>){
    return 0;
}
