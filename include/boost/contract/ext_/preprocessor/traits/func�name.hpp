
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/operator.hpp>
#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/contract/ext_/preprocessor/utility/expand.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PRIVATE */

// Precondition: sign = `(func_name) ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_(sign, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(1) sign \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_TUPLE_REM_CTOR(\
                1, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(sign))) \
    )

// Precondition: sign = `(operator_name,,,) (func_name) ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_PAREN_( \
        sign, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_( \
        BOOST_PP_TUPLE_EAT(0) sign, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_CONTRACT_EXT_PP_PAREN_FRONT(sign) BOOST_PP_EMPTY) \
    )

// This macro already remove one layer of parenthesis via the SEQ_FPR_EACH then
// if remove_all_paren is 1 it removes a second layer (removing all parenthesis
// of the double parenthesized sequence).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_TYPE_REM_( \
        r, remove_all_paren, paren_type_trait) \
    BOOST_PP_IIF(remove_all_paren, \
        BOOST_PP_TUPLE_REM_CTOR(1, paren_type_trait) \
    , \
        paren_type_trait \
    )

// Precondition: typetraits is a double parenthesized sequence of type traits
// (e.g., `((int)) ((const))`).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_TYPE_ARGS_( \
        traits, remainingsign_typetraits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_( \
        ( \
            BOOST_PP_SEQ_CAT( \
                BOOST_PP_SEQ_FOR_EACH( \
                    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_TYPE_REM_, \
                    0, \
                    BOOST_PP_TUPLE_ELEM(2, 1, remainingsign_typetraits) \
                ) \
            ) \
        ) \
        BOOST_PP_TUPLE_ELEM(2, 0, remainingsign_typetraits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
            ( \
                BOOST_PP_SEQ_FOR_EACH( \
                    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_TYPE_REM_,\
                    1, \
                    BOOST_PP_TUPLE_ELEM(2, 1, remainingsign_typetraits) \
                ) \
            ) \
            BOOST_PP_EMPTY \
        ) \
    )

// Precondition: sign = `type ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_TYPE_( \
        sign, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_TYPE_ARGS_(traits, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE_SEQ(sign))

// Precondition: sign = `operator ...`
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_YES_(sign, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_OPERATOR_REMOVE_FRONT(sign)), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_PAREN_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_TYPE_ \
    )(BOOST_CONTRACT_EXT_PP_KEYWORD_OPERATOR_REMOVE_FRONT(sign), traits)

// Add empty operator name (i.e., not an operator).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_NO_(sign, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_(sign, \
            BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
        
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_ARGS_(sign, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_OPERATOR_FRONT(sign), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_NO_ \
    )(sign, traits)

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_PARSE(sign_traits) \
    BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_ARGS_ sign_traits)

// Expand to `(operator_name,,,) | EMPTY()` (EMPTY if not an operator).
// This is the usual C++ operator's symbolic name (often NOT alphanumeric like
// `+`, etc.), use NAME macro below for operator's alphanumeric name instead.
// Wrapped within parenthesis to handle comma operator `(,)`, conversion
// operators for types with commas `(std::map<int, char>)`, etc.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_OPERATOR_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_OPERATOR_NAME_INDEX, traits)()

// Expand to `func_name`.
// This is always an alphanumeric name (also for operators like `plus`, etc.),
// but for destructors where the alphanumeric name contains a leading `~`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_NAME_INDEX, traits)

#endif // #include guard

