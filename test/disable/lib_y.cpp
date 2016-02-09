
// Test contracts in .hpp so can have post (even if NO_POST in its Jamfile).

#define BOOST_CONTRACT_TEST_LIB_Y_SOURCE
#include "lib_y.hpp"

namespace lib_y_ {
    void y_body() { out("y::body\n"); }
}

