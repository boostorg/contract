
// Test all invariants (static, cv, and const-only).

#undef BOOST_CONTRACT_AUX_TEST_STATIC_INV
#undef BOOST_CONTRACT_AUX_TEST_CV_INV
#define BOOST_CONTRACT_AUX_TEST_CONST_INV
#include "decl.hpp"

