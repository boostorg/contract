
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

//[n1962_sqrt
#include <boost/contract.hpp>
#include <cmath>
#include <cassert>

double mysqrt(double x, double precision = 1e-6) {
    double result;
    boost::contract::guard c = boost::contract::function()
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(x >= 0.0);
        })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(fabs(result * result - x) <= precision);
        })
    ;

    return result = sqrt(x);
}

int main() {
    double const precision = 1e-6;
    assert(fabs(mysqrt(4.0, precision) - 2.0) <= precision);
    return 0;
}
//]

