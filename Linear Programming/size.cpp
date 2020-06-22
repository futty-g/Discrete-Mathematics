#include"size.h"
#include<cmath>
#include<boost/rational.hpp>
#include<boost/numeric/ublas/vector.hpp>
#include<boost/numeric/ublas/io.hpp>
#include<boost/numeric/ublas/matrix.hpp>

using namespace std;
namespace ublas = boost::numeric::ublas;

long long size(long long n){
    return 1+(long long)ceil(log2(abs(n) + 1));
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
