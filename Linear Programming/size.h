#ifndef _SIZE_H_
#define _SIZE_H_

#include<boost/rational.hpp>
#include<boost/numeric/ublas/vector.hpp>
#include<boost/numeric/ublas/io.hpp>
#include<boost/numeric/ublas/matrix.hpp>

namespace ublas = boost::numeric::ublas;

long long size(long long);
long long size(boost::rational<long long>);
long long size(ublas::vector<long long>);
long long size(ublas::matrix<long long>);


#endif