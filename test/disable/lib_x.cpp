
// Test contracts in .cpp so never has post (because NO_POST in its Jamfile).

#define BOOST_CONTRACT_TEST_LIB_X_SOURCE
#include "lib_x.hpp"
#include <boost/contract/function.hpp>
#include <boost/contract/guard.hpp>
#include <iostream>

BOOST_CONTRACT_TEST_AUX_OTESTSTREAM_STR_DEF(out)

void x() {
    boost::contract::guard c = boost::contract::function()
        .precondition([] { out("x::pre\n"); })
        .old([] { out("x::old\n"); })
        .postcondition([] { out("x::post\n"); })
    ;
    out("x::body\n");
}

