
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test other contract checking but pre disabled within contract checking.

#define BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION
#include "lib_a.hpp"
#include "lib_a_inlined.hpp"
#include "lib_b.hpp"
#include "lib_b_inlined.hpp"
#include "lib_ab.hpp"

