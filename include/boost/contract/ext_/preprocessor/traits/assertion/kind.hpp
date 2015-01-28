
#ifndef BOOST_CONTRACT_EXT_PP_ASSERTION_KIND_HPP_
#define BOOST_CONTRACT_EXT_PP_ASSERTION_KIND_HPP_

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
        kind, decl_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits), kind) \
    )

// Expand to `namespace | using | typedef | return | ...oldof... | bool |
// const | if | static if` related assertion traits to be inspected with
// NAMESPACE_ASSERTION_TRAITS, USING_ASSERTION_TRAITS, etc. macros.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_AUX_KIND_INDEX, traits)

#endif // #incldue guard

