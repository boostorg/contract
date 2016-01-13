
#ifndef BOOST_CONTRACT_ASSERT_HPP_
#define BOOST_CONTRACT_ASSERT_HPP_

/** @file */

#include <boost/contract/core/config.hpp>

/* PUBLIC */

// Must use ternary operator expr here (instead of if-statement) so this macro
// can always be used with if-statements and all other C++ constructs.
#if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
        BOOST_CONTRACT_INVARIANTS
    #include <boost/contract/core/exception.hpp>
    #include <boost/preprocessor/stringize.hpp>
    #define BOOST_CONTRACT_ASSERT(condition) \
        ((condition) ? (void*)0 : throw boost::contract::assertion_failure( \
                __FILE__, __LINE__, BOOST_PP_STRINGIZE(condition)))
#else
    #define BOOST_CONTRACT_ASSERT(condition) /* nothing */
#endif

#endif // #include guard

