#include"size.h"
#include<iostream>
#include<cassert>
#include<boost/rational.hpp>
#include<boost/numeric/ublas/vector.hpp>
#include<boost/numeric/ublas/io.hpp>
#include<boost/numeric/ublas/matrix.hpp>

using namespace std;
namespace ublas = boost::numeric::ublas;

int main(){
    assert(size(0) == 1);
    assert(size(1) == 2);
    assert(size(2) == 3);
    assert(size(3) == 3);
    assert(size(4) == 4);
    assert(size(10) == 5);
    assert(size(100) == 8);

    assert(size(-1) == 2);
    assert(size(-2) == 3);
    assert(size(-100) == 8);
    
    boost::rational<long long> a(3);
    assert(size(a) == 2+3);
    boost::rational<long long> b(12, 16);
    assert(size(b) == 3+4);
    boost::rational<long long> c(0, 100100);
    assert(size(c) == 3);
    boost::rational<long long> d(-16, 3);
    assert(size(d) == 6+3);

    
    ublas::vector<boost::rational<long long> > u(3);
    // 各要素の参照と代入
    boost::rational<long long> x(3, 1); // x
    u[0] = x;
    boost::rational<long long> y(0, 1); // y
    u[1] = y;
    boost::rational<long long> z(4, 1); // z
    u[2] = z;
    assert(size(u) == 3+(3+2)+(1+2)+(4+2));
    
   
   ublas::vector<long long> v(3);
   v[0] = 3;
   v[1] = 0;
   v[2] = 4;
   assert(size(v) == 11+6);
   
    ublas::matrix<boost::rational<long long>> A(2, 3);
    int cnt = 0;
    for(int i=0; i<2; ++i){
        for(int j=0; j<3; ++j){
            A(i, j) = cnt;
            cnt++;
        }
    }
    assert(size(A) == 6+(1+2)+(2+2)+(3+2)+(3+2)+(4+2)+(4+2));

    return 0;
}