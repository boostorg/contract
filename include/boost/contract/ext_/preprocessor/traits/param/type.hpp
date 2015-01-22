
#ifndef BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_HPP_
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_HPP_

#include <boost/contract/ext_/preprocessor/traits/param/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/typename.hpp>
#include <boost/contract/ext_/preprocessor/keyword/class.hpp>
#include <boost/contract/ext_/preprocessor/keyword/template.hpp>
#include <boost/contract/ext_/preprocessor/utility/expand.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

// NOTE: This file contains macros for the type (or "kind") of both function
// formal parameters and template parameters.

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_PUSH_BACK_( \
        template_template_class_etc, template_template_params, traits) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CLASS_FRONT( \
                template_template_class_etc), \
            BOOST_CONTRACT_EXT_PP_KEYWORD_CLASS_REMOVE_FRONT \
        , \
            BOOST_PP_TUPLE_REM(1) \
        )(template_template_class_etc), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            template \
            template_template_params \
            BOOST_PP_EXPR_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CLASS_FRONT( \
                    template_template_class_etc), \
                class \
            ) \
        ) \
    )

// Precondition: decl = `template(,,,) ...`.
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_( \
        d, decl, traits) \
    BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_PUSH_BACK_( \
        BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_CLASS_ETC( \
                decl), \
        BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_PARAMS( \
                decl), \
        traits \
    )

// Precondition: decl = `class ...`.
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_CLASS_( \
        d, decl, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_CLASS_REMOVE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, class) \
    )

// Precondition: decl = `typename ...`.
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TYPENAME_( \
        d, decl, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_TYPENAME_REMOVE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, typename) \
    )
            
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_(decl_type, traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_type), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)) \
    )

// Precondition: decl = `wrapped-type`.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_PARSE_ARGS_(d, decl, traits) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_( \
            BOOST_CONTRACT_EXT_PP_TRAITS_TYPE_PARSE_D(d, decl), traits)
    
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_PARSE_ARGS_( \
        d, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPENAME_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TYPENAME_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CLASS_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_CLASS_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_ \
    , \
        BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_PARSE_ARGS_ \
    )))(d, decl, traits)

/* PUBLIC */

// Parse type for (function formal, not template) parameters.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_PARSE_D(d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_PARSE_ARGS_(d, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Parse "type" (or "kind") for template parameters.
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_PARSE_D( \
        d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_PARSE_ARGS_(d, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Expand to `typename | class | (,,,) | template( ,,, ) class` (for
// type template parameters, value template parameter or function formal
// parameters, and template template parameters respectively).
// See also TEMPLATE_PARAM macros below for template template parameters.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_AUX_TYPE_INDEX, traits)

// Helper macros for template template parameters.

// Expand `template( ,,, ) ...` to `( ,,, )` (this is useful to get the
// pp-tuple with the template parameters of a template template parameter).
// Expand to `(...)` for variadic function parameters.
// Precondition: decl = `template( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_PARAMS(decl) \
    BOOST_CONTRACT_EXT_PP_PAREN_FRONT( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl))

// Expand `template( ,,, ) ...` to `...` (this is useful to get the class
// specifier of a template template parameter, without assuming it is `class`).
// Precondition: decl = `template( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_CLASS_ETC( \
        decl) \
    BOOST_PP_TUPLE_EAT(0) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl)

#endif // #include guard

