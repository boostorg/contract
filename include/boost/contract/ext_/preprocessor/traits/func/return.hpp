
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/type.hpp>
#include <boost/contract/ext_/preprocessor/keyword/operator.hpp>
#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/contract/ext_/preprocessor/utility/expand.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/control/iif.hpp>

/* PRIVATE */

// Precondition: sign = `(func_name?) ...`
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_HAS_PARAMS_(sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(BOOST_PP_TUPLE_EAT(0) sign), \
        1 \
    , \
        0 \
    )
        
// Precondition: sign = `(result_type?) ...`
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_HAS_NAME_AND_PARAMS_(sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(BOOST_PP_TUPLE_EAT(0) sign), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_HAS_PARAMS_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    )(BOOST_PP_TUPLE_EAT(0) sign)

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_HAS_RETURN_(sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(sign), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_HAS_NAME_AND_PARAMS_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_OPERATOR_FRONT(sign), \
        0 BOOST_PP_TUPLE_EAT(1) \
    , \
        1 BOOST_PP_TUPLE_EAT(1) \
    ))(sign)

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_TYPE_(traits, sign_type) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, sign_type) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, sign_type) BOOST_PP_EMPTY) \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_YES_(sign, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_TYPE_(traits, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PRASE(sign))

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_NO_(sign, traits) \
    (sign, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_(sign, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_HAS_RETURN_(sign), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_NO_ \
    )(sign, traits)

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_PARSE(sign_traits) \
    BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_ sign_traits)

// Expand to `result_type | void | auto | EMPTY()` (auto for unified function
// syntax in which case for the result type trait use `..._UNIFIED_RETURN`).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN(traits) \

#endif // #include guard

