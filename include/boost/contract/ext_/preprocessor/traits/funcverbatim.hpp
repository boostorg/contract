
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/func_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/keyword_paren.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/verbatim.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PUBLIC */

// Expand to `(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_VERBATIM_INDEX, traits)()

// Implementation: Trailing EMPTY already put by KEYWORD_PAREN.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_PAREN_TRAITS_PARSE( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VERBATIM_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_VERBATIM_REMOVE_FRONT \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#endif // #include guard

