
#ifndef DBC_PP_FUN_PARSE_OPTIONAL_HPP_
#define DBC_PP_FUN_PARSE_OPTIONAL_HPP_

#include "../../seq.hpp"
#include "apply.hpp"
#include "returns.hpp"
#include <boost/preprocessor.hpp>

#define DBC_PP_FUN_PARSE_OPTIONAL_NO_(sign_traits_err, check_macro) \
    DBC_PP_FUN_PARSE_RETURN_OK_(sign_traits_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err), \
            (/* empty seq elem if no token */))

#define DBC_PP_FUN_PARSE_OPTIONAL_OP_(sign_traits_err, check_macro) \
    BOOST_PP_IF(check_macro(BOOST_PP_SEQ_HEAD( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err))), \
        DBC_PP_FUN_PARSE_RETURN_OK_(sign_traits_err, BOOST_PP_SEQ_TAIL( \
                BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)), \
                (BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)))\
                )\
    , /* else */ \
        DBC_PP_FUN_PARSE_RETURN_OK_(sign_traits_err, \
                BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err), \
                () /* empty se elem if no macth */) \
    ) /* endif */

#define DBC_PP_FUN_PARSE_OPTIONAL_(sign_traits_err, check_macro) \
    DBC_PP_FUN_PARSE_APPLY_(DBC_PP_FUN_PARSE_OPTIONAL_OP_, \
            DBC_PP_FUN_PARSE_OPTIONAL_NO_, sign_traits_err, check_macro)

#endif // DBC_PP_FUN_PARSE_OPTIONAL_HPP_

