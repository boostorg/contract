
#ifndef BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ_HPP_
#define BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ_HPP_

#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/control/iif.hpp>

/* PUBLIC */

// Expand EMPTY() to EMPTY(), otherwise expand variadic data to pp-seq.
#define BOOST_CONTRACT_EXT_PP_VARIADIC_TO_SEQ(...) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(__VA_ARGS__), \
        BOOST_PP_EMPTY \
    , \
        BOOST_PP_VARIADIC_TO_SEQ \
    )(__VA_ARGS__)

#endif // #include guard

