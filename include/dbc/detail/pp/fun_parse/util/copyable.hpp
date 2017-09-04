
#ifndef DBC_PP_FUN_PARSE_COPYABLE_HPP_
#define DBC_PP_FUN_PARSE_COPYABLE_HPP_

#include "../../keywords.hpp"
#include "../../seq.hpp"
#include "apply.hpp"
#include "required.hpp"
#include "optional.hpp"
#include <boost/preprocessor.hpp>

#define DBC_PP_FUN_PARSE_COPYABLE_OP_(sign_traits_err, data) \
    ( BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err) \
    , DBC_PP_SEQ_REST_N_TO_TUPLE_(2, \
            BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err)) \
    , BOOST_PP_TUPLE_ELEM(3, 2, sign_traits_err))
    
#define DBC_PP_FUN_PARSE_COPYABLE_(sign_traits_err, missing_token_error) \
    DBC_PP_FUN_PARSE_APPLY_(DBC_PP_FUN_PARSE_COPYABLE_OP_, \
            DBC_PP_FUN_PARSE_COPYABLE_OP_, \
            DBC_PP_FUN_PARSE_REQUIRED_( \
                    DBC_PP_FUN_PARSE_OPTIONAL_(sign_traits_err, \
                    DBC_PP_IS_COPYABLE_), missing_token_error), \
            ~)

#endif // DBC_PP_FUN_PARSE_COPYABLE_HPP_

