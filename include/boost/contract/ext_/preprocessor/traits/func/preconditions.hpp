
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITIONS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITIONS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/func_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/keyword_list.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/list.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/precondition.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PUBLIC */

// Expand to pp-seq of precondition assertion traits to be inspected via
// ASSERTION_TRAITS macro, or to EMPTY() if no preconditions.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITIONS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_PRECONDITIONS_INDEX, traits)()

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITIONS_PARSE_D( \
        d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_LIST_PARSE_D(d, \
        decl_traits, \
        BOOST_PP_EMPTY(), \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PRECONDITION_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_PRECONDITION_REMOVE_FRONT, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITIONS_ \
    )

/* PRIVATE */

// Precondition: decl = `(,,,) ...` from `precondition(,,,) ...` originally in
// decl. This macro will also parse `(,,,)` into a pp-seq of assertion traits.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITIONS_(d, decl) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_1(d, \
        decl, \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_1, \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_1, \
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_1 \
    )

#endif // #include guard

