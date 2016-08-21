
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test contracts in .cpp so never has post (because NO_POST in its Jamfile).

// Test contracts in .cpp so never post (as NO_POST/EXCEPTS here).
#define BOOST_CONTRACT_NO_POSTCONDITIONS
#define BOOST_CONTRACT_NO_EXCEPTS

#define BOOST_CONTRACT_TEST_LIB_X_SOURCE
#include "lib_x.hpp"
#include <boost/contract/function.hpp>
#include <boost/contract/check.hpp>

BOOST_CONTRACT_TEST_DETAIL_OTESTSTREAM_STR_DEF(out)

void x() {
    boost::contract::check c = boost::contract::function()
        .precondition([] { out("x::pre\n"); })
        .old([] { out("x::old\n"); })
        .postcondition([] { out("x::post\n"); })
    ;
    out("x::body\n");
}

