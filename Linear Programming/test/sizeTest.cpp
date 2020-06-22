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
    cout<<size(-9)<<endl;
    cout<<size(10000)<<endl;

    return 0;
}