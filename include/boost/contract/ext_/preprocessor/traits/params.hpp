
#ifndef BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/param/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/param/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/param/default.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/params.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_PARAM_PARSE_D_S_( \
        d, s, sign_traits) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_PARSE_EMPTY( \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_PARSE( \
        sign_traits \
    )))

#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_TEMPLATE_PARAM_PARSE_D_S_( \
        d, s, sign_traits) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_PARSE_EMPTY( \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_PARSE( \
        sign_traits \
    )))

/* PUBLIC */

// Function formal (not template) parameters (handle `(void)` and empty `()`).
#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_D_S(d, s, sign) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_VOID_PARAMS_D_S(d, s, \
        sign, \
        BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_PARAM_PARSE_D_S_, \
        BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_PARSE_D_S \
    )

// Expand specified pp-tuple with template parameters signature into pp-list
// of template parameter traits to inspect using PARAM_TRAITS macros.
#define BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS(sign) \
    BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_D_S(1, 1, sign)

// Template parameters (handle empty `()`).
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAMS_TRAITS_D_S(d, s, sign) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_D_S(d, s, \
        sign, \
        BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_TEMPLATE_PARAM_PARSE_D_S_, \
        BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_PARSE_D_S \
    )

// Expand specified pp-tuple with template parameters signature into pp-list
// of template parameter traits to inspect using PARAM_TRAITS macros.
#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAMS_TRAITS(sign) \
    BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAMS_TRAITS_D_S(1, 1, sign)

#endif // #include guard

