
// Test other contract checking but pre disabled within contract checking.

#define BOOST_CONTRACT_CONFIG_PRECONDITIONS_DISABLE_NOTHING
#include "lib_a.hpp"
#include "lib_a_inlined.hpp"
#include "lib_b.hpp"
#include "lib_b_inlined.hpp"
#include "lib_ab.hpp"

