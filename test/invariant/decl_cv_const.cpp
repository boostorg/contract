
// Test all invariants (static, cv, and const-only).

#undef BOOST_CONTRACT_TEST_STATIC_INV
#define BOOST_CONTRACT_TEST_CV_INV
#define BOOST_CONTRACT_TEST_CONST_INV
#include "decl.hpp"

