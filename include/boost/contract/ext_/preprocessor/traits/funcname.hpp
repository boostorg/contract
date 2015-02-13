
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/func_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/operator.hpp>
#include <boost/contract/ext_/preprocessor/keyword/new.hpp>
#include <boost/contract/ext_/preprocessor/keyword/delete.hpp>
#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PUBLIC */

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
// but for destructors where name has the leading symbol `~`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_NAME_INDEX, traits)

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_PARSE_D(d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_ARGS_(d, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_ARGS_(d, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_OPERATOR_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_NO_ \
    )(d, decl, traits)
// Precondition: decl = `operator ...`
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_YES_(d, decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_(d, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_OPERATOR_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_(d, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_PAREN_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NEW_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_NEW_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_DELETE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_DELETE_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_TYPE_ \
    )))(d, decl, traits)

// Precondition: decl = `parenthesized-type ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_TYPE_(d, decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_TYPE_SEQ_( \
            BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_SEQ_PARSE_D(d, decl), traits)

// Precondition: SECOND(decl_type) is a double parenthesized sequence of type
// traits (e.g., `((int)) ((const))`).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_TYPE_SEQ_( \
        decl_type, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_PAREN_(~, \
        ( \
            BOOST_PP_SEQ_FOR_EACH( \
                BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_TYPE_REM_,\
                1, \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type) \
            ) \
        ) \
        ( \
            BOOST_PP_SEQ_CAT( \
                BOOST_PP_SEQ_FOR_EACH( \
                    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_TYPE_REM_, \
                    0, \
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type) \
                ) \
            ) \
        ) \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_type), \
        traits \
    )

// This macro already removes one set of parenthesis via the SEQ_FOR_EACH
// (from `((elem))` to `(elem)`). Furthermore, if remove_all_paren is 1, it also
// removes a second set of parenthesis (removing all parenthesis of a double
// parenthesized sequence element, from `((elem))` to `elem`).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_TYPE_REM_( \
        r, remove_all_paren, paren_type_trait) \
    BOOST_PP_EXPR_IIF(remove_all_paren, \
        BOOST_PP_TUPLE_REM(1) \
    ) paren_type_trait

// Precondition: decl = `delete ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_DELETE_( \
        unused, decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_PAREN_(~, (delete)(delete) \
            BOOST_CONTRACT_EXT_PP_KEYWORD_DELETE_REMOVE_FRONT(decl), traits)

// Precondition: decl = `new ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_NEW_( \
        unused, decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_PAREN_(~, (new)(new) \
            BOOST_CONTRACT_EXT_PP_KEYWORD_NEW_REMOVE_FRONT(decl), traits)

// Precondition: decl = `(operator_name,,,) (func_name) ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_PAREN_( \
        unused, decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl) BOOST_PP_EMPTY) \
    )

// Add empty operator name (i.e., not an operator).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_OPERATOR_NO_( \
        unused, decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_(decl, \
            BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))

// Precondition: decl = `(func_name) ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_(decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(1) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_REM_CTOR(1, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
        ) \
    )

#endif // #include guard

