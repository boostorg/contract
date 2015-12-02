
#ifndef BOOST_CONTRACT_ASSERT_HPP_
#define BOOST_CONTRACT_ASSERT_HPP_

/** @file */

#include <boost/contract/core/exception.hpp>
/** @cond */
#include <boost/preprocessor/stringize.hpp>
/** @endcond */

/* PUBLIC */

// Must use ternary operator expr here (instead of if-statement) so this macro
// can always be used with if-statements and all other C++ constructs.
#define BOOST_CONTRACT_ASSERT(condition) \
    ((condition) ? (void*)0 : throw boost::contract::assertion_failure( \
            __FILE__, __LINE__, BOOST_PP_STRINGIZE(condition)))

#endif // #include guard

