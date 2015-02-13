
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/func_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/return.hpp>
#include <boost/contract/ext_/preprocessor/keyword/operator.hpp>
#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/control/iif.hpp>

/* PUBLIC */

// Expand to `result_type | void | auto | EMPTY()` (`auto` for alternative
// function syntax, see also `..._TRAILING_RETURN`).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_RETURN_INDEX, traits)()

// Expand to `result_type | void | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TRAILING_RETURN(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_TRAILING_RETURN_INDEX, \
        traits \
    )()

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_PARSE_D(d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_PARSE_ARGS_(d, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TRAILING_RETURN_PARSE_D( \
        d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TRAILING_RETURN_PARSE_ARGS_(d, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TRAILING_RETURN_PARSE_ARGS_( \
        d, decl, traits) \
    BOOST_PP_IIF( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_FRONT(decl), \
        BOST_CONTRACT_EXT_PP_FUNC_TRAITS_TRAILING_RETURN_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_NO_ \
    )(d, decl, traits)

// Precondition: decl = `return ...`.
#define BOST_CONTRACT_EXT_PP_FUNC_TRAITS_TRAILING_RETURN_YES_(d, decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_( \
        BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_PARSE_D(d, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_RETURN_REMOVE_FRONT(decl) \
        ), \
        traits \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_PARSE_ARGS_(d, decl, traits) \
    BOOST_PP_IIF( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_HAS_RETURN_(decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_NO_ \
    )(d, decl, traits)

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_YES_(d, decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUTO_TYPE_PARSE_D(d, decl), traits)

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_(decl_return, traits) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_PUSH_BACK( \
        ( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_return), \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_return) BOOST_PP_EMPTY \
        ), \
        traits \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_NO_(d, decl, traits) \
    ( \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY) \
    )

// Constructors, destructors, type conversion operators, etc. do no have a
// return type so this checks first if this declaration is supposed to have
// a return type or not (based on upcoming number of parenthesis, etc.).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_HAS_RETURN_(decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_PEEK_NAME_AND_PARAMS_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_OPERATOR_FRONT(decl), \
        0 BOOST_PP_TUPLE_EAT(1) \
    , \
        1 BOOST_PP_TUPLE_EAT(1) \
    ))(decl)

// Precondition: decl = `(result_type?) ...`
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_PEEK_NAME_AND_PARAMS_(decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(BOOST_PP_TUPLE_EAT(0) decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_PEEK_PARAMS_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_OPERATOR_FRONT( \
            BOOST_PP_TUPLE_EAT(0) decl), \
        1 BOOST_PP_TUPLE_EAT(1) \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    ))(BOOST_PP_TUPLE_EAT(0) decl)

// Precondition: decl = `(func_name?) ...`
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_PEEK_PARAMS_(decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(BOOST_PP_TUPLE_EAT(0) decl), \
        1 \
    , \
        0 \
    )
    
#endif // #include guard

