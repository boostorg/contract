
#ifndef BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_HPP_
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_HPP_

#include <boost/contract/ext_/preprocessor/traits/param/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>

/* PUBLIC */

// Precondition: name must always be the last remaining token in decl.
// NOTE: Trailing EMPTY after name is already in decl.
// Implementation: NIL used as tuples cannot have EMPTY() elems (in MSVC).
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_PARSE(decl_traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_traits), \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_traits) \
        ) \
    )

// Expand to `[...] name | EMPTY()` (ellipses `...` for variadic templates).
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_AUX_NAME_INDEX, traits)()

#endif // #include guard

