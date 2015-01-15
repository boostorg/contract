
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/keyword_paren.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/verbatim.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_(decl_verbatim, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_verbatim) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_verbatim) \
            BOOST_PP_EMPTY \
        ) \
    )

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN( \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_traits), \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VERBATIM_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_VERBATIM_REMOVE_FRONT \
        ), \
        BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_traits) \
    )

// Expand to `(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_VERBATIM_INDEX, traits)()

#endif // #include guard

