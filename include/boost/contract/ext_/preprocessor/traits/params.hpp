
#ifndef BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/param/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/param/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/param/default.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/params.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_PARAM_PARSE_D_S_( \
        d, s, decl_traits) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_PARSE_EMPTY( \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_PARSE( \
        decl_traits \
    )))

#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_TEMPLATE_PARAM_PARSE_D_S_( \
        d, s, decl_traits) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_PARSE_EMPTY( \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_PARSE( \
        decl_traits \
    )))

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_D_S(d, s, decl) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_PARAMS_D_S(d, s, \
        decl, \
        BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_PARAM_PARSE_D_S_, \
        BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_PARSE_D_S \
    )

// Expand decl = `(,,,)` containing (function formal, not template) parameter
// declarations into pp-list of parameter traits (to then be inspected using
// PARAM_TRAITS macros). Handle both `(void)` and empty `()`.
#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS(decl) \
    BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_D_S(1, 1, decl)

#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAMS_TRAITS_D_S(d, s, decl) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_D_S(d, s, \
        decl, \
        BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_TEMPLATE_PARAM_PARSE_D_S_, \
        BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_PARSE_D_S \
    )

// Expand decl = `(,,,)` containing template parameter declarations into pp-list
// of template parameter traits (to then be inspected using PARAM_TRAITS
// macros). Handle empty `()`.
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAMS_TRAITS(decl) \
    BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAMS_TRAITS_D_S(1, 1, decl)

#endif // #include guard

