
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/keyword_paren.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/verbatim.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PRIVATE */

// Precondition: verbatim = `[(,,,)] EMPTY` (so trailing EMPTY already there).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_(decl_verbatim, traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_verbatim), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_verbatim)) \
    )

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_( \
        BOOST_CONTRACT_EXT_PP_TRAITS_KEYWORD_PAREN_PARSE( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VERBATIM_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_VERBATIM_REMOVE_FRONT \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Expand to `(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_VERBATIM_INDEX, traits)()

#endif // #include guard

