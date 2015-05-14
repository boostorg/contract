
#ifndef BOOST_CONTRACT_ASSERT_HPP_
#define BOOST_CONTRACT_ASSERT_HPP_

/** @file */

#include <boost/contract/core/exception.hpp>
/** @cond */
#include <boost/preprocessor/stringize.hpp>
/** @endcond */

/* PUBLIC */

#define BOOST_CONTRACT_ASSERT(condition) \
    if(!(condition)) { \
        throw boost::contract::assertion_failure(__FILE__, __LINE__, \
                BOOST_PP_STRINGIZE(condition)); \
    }

#endif // #include guard

