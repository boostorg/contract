
#ifndef BOOST_CONTRACT_EXT_PP_STRINGIZE_HPP_
#define BOOST_CONTRACT_EXT_PP_STRINGIZE_HPP_

#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/stringize.hpp>

/* PUBLIC */

// Handle tokens == EMPTY() (BOOST_PP_STRINGIZE does not).
#define BOOST_CONTRACT_EXT_PP_STRINGIZE(tokens) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(tokens), \
        "" BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_PP_STRINGIZE \
    )(tokens)

#endif // #include guard

