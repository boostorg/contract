
#ifndef BOOST_CONTRACT_ASSERT_HPP_
#define BOOST_CONTRACT_ASSERT_HPP_

#include <boost/contract/aux_/exception.hpp>
#include <boost/contract/aux_/name.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/config/config.hpp>
#include <sstream>

/* PUBLIC */

#if BOOST_PP_VARIADICS
#   define BOOST_CONTRACT_ASSERT(...) BOOST_CONTRACT_ASSERT_((__VA_ARGS__))
#else
#   define BOOST_CONTRACT_ASSERT(cond) BOOST_CONTRACT_ASSERT_((cond))
#endif

/* PRIVATE */

#define BOOST_CONTRACT_ASSERT_(cond) \
    if(!cond) { \
        std::ostringstream BOOST_CONTRACT_AUX_NAME1(error); \
        BOOST_CONTRACT_AUX_NAME1(error) << "failed \"" << BOOST_PP_STRINGIZE( \
                cond) << "\" at " << __FILE__ << ":" << __LINE__; \
        throw boost::contract::aux::assertion_failure( \
                BOOST_CONTRACT_AUX_NAME1(error.str().c_str())); \
    }

#endif // #include guard

