
#ifndef BOOST_CONTRACT_EXT_PP_ASSERTION_KEY_HPP_
#define BOOST_CONTRACT_EXT_PP_ASSERTION_KEY_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/assertion_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

/* PUBLIC */

// Expand to `namespace | using | typedef | return | ...oldof... | bool |
// const | if | static if` related assertion traits to be inspected with
// NAMESPACE_ASSERTION_TRAITS, USING_ASSERTION_TRAITS, etc. macros.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KEY(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_AUX_KEY_INDEX, traits)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KEY_PARSE(key, decl_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits), key) \
    )

#endif // #incldue guard

