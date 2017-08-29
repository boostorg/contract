
#ifndef DBC_PP_FUN_PARSE_APPLY_HPP_
#define DBC_PP_FUN_PARSE_APPLY_HPP_

#include <boost/preprocessor.hpp>

// Can't use BOOST_PP_IDENTITY() because it trails with BOOST_PP_EMPTY...
#define DBC_PP_FUN_PARSE_APPLY_IDENTITY_(sign_traits_err, data) sign_traits_err

#define DBC_PP_FUN_PARSE_APPLY_(parse_macro, parse_empty_macro, \
        sign_traits_err, data) \
    BOOST_PP_IF(BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_TUPLE_ELEM( \
            3, 2, sign_traits_err)), \
        /* if error, do nothing but passing error up */ \
        DBC_PP_FUN_PARSE_APPLY_IDENTITY_ \
    , BOOST_PP_IF(BOOST_PP_SEQ_SIZE( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)), \
        parse_macro \
    , /* else (no token left to parse in signature) */ \
        parse_empty_macro \
    ))(sign_traits_err, data)

#endif // DBC_PP_FUN_PARSE_APPLY_HPP_

