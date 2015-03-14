
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/func_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/keyword_list.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/list.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/postcondition.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PUBLIC */

// Expand to pp-seq of postcondition assertion traits to be inspected via
// ASSERTION_TRAITS macro, or to EMPTY() if no postconditions.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_POSTCONDITIONS_INDEX, traits \
    )()

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_PARSE_D( \
        d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_LIST_PARSE_D(d, \
        decl_traits, \
        BOOST_PP_EMPTY(), \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_POSTCONDITION_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_POSTCONDITION_REMOVE_FRONT, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_ \
    )

/* PRIVATE */

// Precondition: decl = `(,,,) ...` from `postcondition(,,,) ...` originally in
// decl. This macro will also parse `(,,,)` into a pp-seq of assertion traits.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_(d, decl) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_LIST_PARSE_D_1(d, \
        decl, \
        BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_1, \
        BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_1, \
        BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_1 \
    )

#endif // #include guard

