
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_HPP_

#include <boost/contract/ext_/preprocessor/traits/tparams.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/keyword_paren.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/template.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_SIGN_(sign, traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_SKIP( \
        sign, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_TRAIT_YES_(sign, traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            template BOOST_PP_EMPTY \
        ), \
        BOOST_CONTRACT_EXT_PP_TPARAMS_TRAITS( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN( \
                sign, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT, \
                BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_TRAIT_NO_(sign, traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_EMPTY \
        ), \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_TRAIT_(sign, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT(sign), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_TRAIT_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_TRAIT_NO_ \
    )(sign, traits)

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_PARSE(sign_traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_SIGN_ sign_traits \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_TRAIT_ sign_traits \
    )

// Expand to `template | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_TEMPLATE_INDEX, \
        traits \
    )()

// Expand to pp-list of function template parameters. Each single template
// parameter in this pp-list is inspected using TPARAM_TRAITS macros.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TPARAMS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_TPARAMS_INDEX, \
        traits \
    )

#endif // #include guard

