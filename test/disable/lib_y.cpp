
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test contracts in .hpp so can have post (even if NO_POST in its Jamfile).

#define BOOST_CONTRACT_TEST_LIB_Y_SOURCE
#include "lib_y.hpp"

namespace lib_y_ {
    void y_body() { out("y::body\n"); }
}

