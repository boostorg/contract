
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/keyword.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/ref.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/refref.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_(decl_ref, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_ref) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_ref) \
            BOOST_PP_EMPTY \
        ) \
    )

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2( \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_traits), \
            ref, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_REF_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_REF_REMOVE_FRONT, \
            refref, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_REFREF_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_REFREF_REMOVE_FRONT \
        ), \
        BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_traits) \
    )

// Expand to `ref | refref | EMPTY()` (ref for lvalue &, refref for rvalue &&).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_REF_INDEX, traits)()

#endif // #include guard

