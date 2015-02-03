
#ifndef BOOST_CONTRACT_EXT_PP_PARENTHESIZE_HPP_
#define BOOST_CONTRACT_EXT_PP_PARENTHESIZE_HPP_

#include <boost/contract/ext_/preprocessor/paren/has.hpp>

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_PARENTHESIZE(tokens) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(tokens), \
        tokens \
    , \
        (tokens) \
    )

#endif // #include guard

