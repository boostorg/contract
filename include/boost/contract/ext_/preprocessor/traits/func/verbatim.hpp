
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/keyword_paren.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/verbatim.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

// PRIVATE //

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_SIGN_(sign, traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_SKIP( \
        sign, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VERBATIM, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_VERBATIM_REM \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_TRAIT_(sign, traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK( \
        traits, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN( \
            sign, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VERBATIM, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_VERBATIM_REM \
        ) \
        BOOST_PP_EMPTY \
    )

// PUBLIC //

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_PARSE(sign_traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_SIGN_ sign_traits \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_TRAIT_ sign_traits \
    )

// Expand to `(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FUNC_INDEX_VERBATIM, \
        traits \
    )()

#endif // #include guard

