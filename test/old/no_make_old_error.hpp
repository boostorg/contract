
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test error when make_old(...) not used by mistake.

#ifndef BOOST_CONTRACT_TEST_OLD_PTR_TYPE
    #error "must define BOOST_CONTRACT_TEST_OLD_PTR_TYPE"
#endif

#include <boost/contract/old.hpp>

int main() {
    int x = 1;
    // Error (missing outer make_old(...)).
    BOOST_CONTRACT_TEST_OLD_PTR_TYPE<int> old_x = boost::contract::copy_old() ?
            x : boost::contract::null_old();
    return 0;
}

