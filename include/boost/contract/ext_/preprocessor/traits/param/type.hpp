
#ifndef BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_HPP_
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_HPP_

#include <boost/contract/ext_/preprocessor/traits/param/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/keyword/typename.hpp>
#include <boost/contract/ext_/preprocessor/keyword/class.hpp>
#include <boost/contract/ext_/preprocessor/keyword/template.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/keyword_paren.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/utility/expand.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>

// NOTE: This file contains macro for the type (or "kind") of both function
// parameters and template parameters.

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_REMOVE_CLASS_(tokens) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CLASS_FRONT(tokens), \
        BOOST_CONTRACT_EXT_PP_KEYWORD_CLASS_REMOVE_FRONT \
    , \
        BOOST_PP_TUPLE_REM(1) \
    )(tokens)
        
// For template template parameters.
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_SIGN_(sign) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_REMOVE_CLASS_( \
        BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_CLASS(sign) \
    )

// For template template parameters.
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_TRAIT_(sign) \
    template \
    BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_PARAMS(sign) \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CLASS_FRONT( \
            BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_CLASS( \
                    sign)), \
        class \
    )

#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_SIGN_(sign, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPENAME_FRONT(sign), \
        BOOST_CONTRACT_EXT_PP_KEYWORD_TYPENAME_REMOVE_FRONT \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CLASS_FRONT(sign), \
        BOOST_CONTRACT_EXT_PP_KEYWORD_CLASS_REMOVE_FRONT \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT(sign), \
        BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_SIGN_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_SKIP \
    )))(sign)
        
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TRAIT_(sign, traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
        traits, \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPENAME_FRONT(sign), \
            typename BOOST_PP_TUPLE_EAT(1) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CLASS_FRONT(sign), \
            class BOOST_PP_TUPLE_EAT(1) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT(sign), \
            BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_TRAIT_ \
        , \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE \
        )))(sign) \
    )

#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_PARSE_(sign_type, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_FIRST(sign_type) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_SECOND(sign_type)) \
    )
            

/* PUBLIC */

// Parse type for function parameters.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_PARSE(sign_traits) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_PARSE_( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE( \
                BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_FIRST(sign_traits)), \
        BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_SECOND(sign_traits) \
    )

// Parse "type" (or "kind") for template parameters.
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_PARSE(sign_traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
            BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_SIGN_ \
            sign_traits \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
            BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TRAIT_ \
            sign_traits \
        ) \
    )

// Expand to `typename | class | (,,,) | template( ,,, ) class` (for
// type template parameters, value template and function parameters, and
// template template parameters respectively).
// See also TEMPLATE_PARAM macros below for template template parameters.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_AUX_TYPE_INDEX, \
        traits \
    )

// Helper macros for template template parameters.

// Expand `template( ,,, ) ...` to `( ,,, )` (this is useful to get the
// pp-tuple with the template parameters of a template template parameter).
// Expand to `(...)` for variadic function parameters.
// Precondition: tokens are `template( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_PARAMS( \
        tokens) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN( \
        tokens, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT \
    )

// Expand `template( ,,, ) ...` to `...` (this is useful to get the class
// specifier of a template template parameter, without assuming it is `class`).
// Precondition: tokens are `template( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_CLASS( \
        tokens) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_SKIP( \
        tokens, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT \
    )

#endif // #include guard

