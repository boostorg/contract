
#ifndef BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_VERBATIM_HPP_
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_VERBATIM_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/index/class.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/keyword_paren.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/verbatim.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PUBLIC */

// Expand to `(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_VERBATIM(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_VERBATIM, traits)()

// Implementation: Trailing EMPTY already put by KEYWORD_PAREN.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_VERBATIM_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_PARSE( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VERBATIM_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_VERBATIM_REMOVE_FRONT \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#endif // #include guard

