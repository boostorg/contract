
#ifndef BOOST_CONTRACT_EXT_PP_IS_EMPTY_HPP_
#define BOOST_CONTRACT_EXT_PP_IS_EMPTY_HPP_

#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/control/iif.hpp>

// PUBLIC //

// Expand to 1 if tokens are EMPTY(), 0 otherwise (handle tokens with paren).
#define BOOST_CONTRACT_EXT_PP_IS_EMPTY(tokens) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(tokens), \
        0 BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_PP_IS_EMPTY \
    )(tokens)

#endif // #include guard

