
#ifndef BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_KIND_HPP_
#define BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_KIND_HPP_

#include <boost/contract/ext_/preprocessor/traits/tparam/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/keyword/typename.hpp>
#include <boost/contract/ext_/preprocessor/keyword/class.hpp>
#include <boost/contract/ext_/preprocessor/keyword/template.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/keyword_paren.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

#define BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_KIND_SIGN_(sign, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPENAME_FRONT(sign), \
        BOOST_CONTRACT_EXT_PP_KEYWORD_TYPENAME_REMOVE_FRONT \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CLASS_FRONT(sign), \
        BOOST_CONTRACT_EXT_PP_KEYWORD_CLASS_REMOVE_FRONT \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT(sign), \
        BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_KIND_TEMPLATE_SIGN_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PAREN_TYPE_SKIP \
    )))(sign)
        
#define BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_KIND_TRAIT_(sign, traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK( \
        traits, \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPENAME_FRONT(sign), \
            typename BOOST_PP_TUPLE_EAT(1) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CLASS_FRONT(sign), \
            class BOOST_PP_TUPLE_EAT(1) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT(sign), \
            BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_KIND_TEMPLATE_TRAIT_ \
        , \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PAREN_TYPE \
        )))(sign) \
    )

// PUBLIC //
    
#define BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_KIND_PARSE(sign_traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_KIND_SIGN_ sign_traits, \
        BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_KIND_TRAIT_ sign_traits \
    )

// Expand to `typename | class | (,,,) | template( ,,, ) class` (for type,
// value, and template template parameters respectively). See also
// KIND_TEMPLATE macros below for template template parameters.
#define BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_KIND(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
        BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_AUX_KIND_INDEX, \
        traits \
    )

// Expand `template( ,,, ) ...` to `( ,,, )` (this is useful to get the
// pp-tuple with the template parameters of a template template parameter).
// Precondition: tokens are `template( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_KIND_TEMPLATE_PARAMS(tokens) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN( \
        tokens, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT \
    )

// Expand `template( ,,, ) ...` to `...` (this is useful to get the class
// specifier of a template template parameter, without assuming it is `class`).
// Precondition: tokens are `template( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_KIND_TEMPLATE_CLASS(tokens) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_SKIP( \
        tokens, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT \
    )

#endif // #include guard

