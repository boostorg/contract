
#ifndef DBC_PP_FUN_PARSE_REQUIRED_HPP_
#define DBC_PP_FUN_PARSE_REQUIRED_HPP_

#include "../../seq.hpp"
#include "apply.hpp"
#include "returns.hpp"
#include <boost/preprocessor.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>

#define DBC_PP_FUN_PARSE_REQUIRED_NO_(sign_traits_err, missing_token_err) \
    DBC_PP_FUN_PARSE_RETURN_ERR_(sign_traits_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err), \
            (/* empty seq elem in case of error */), \
            missing_token_err) \

#define DBC_PP_FUN_PARSE_REQUIRED_OP_(sign_traits_err, \
        missing_token_err) \
    BOOST_PP_IF(BOOST_PP_IS_EMPTY(BOOST_PP_SEQ_HEAD( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err))), \
        DBC_PP_FUN_PARSE_RETURN_ERR_(sign_traits_err, BOOST_PP_SEQ_TAIL( \
                BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)), \
                BOOST_PP_EMPTY(), \
                missing_token_err) \
    , /* else */ \
        DBC_PP_FUN_PARSE_RETURN_OK_(sign_traits_err, BOOST_PP_SEQ_TAIL( \
                BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)), \
                ( BOOST_PP_SEQ_HEAD( \
                BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)) )) \
    ) /* endif */

#define DBC_PP_FUN_PARSE_REQUIRED_(sign_traits_err, missing_token_err) \
    DBC_PP_FUN_PARSE_APPLY_(DBC_PP_FUN_PARSE_REQUIRED_OP_, \
            DBC_PP_FUN_PARSE_REQUIRED_NO_, sign_traits_err, \
            missing_token_err)

#endif // DBC_PP_FUN_PARSE_REQUIRED_HPP_

