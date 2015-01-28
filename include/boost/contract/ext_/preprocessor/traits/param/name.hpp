
#ifndef BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_HPP_
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_HPP_

#include <boost/contract/ext_/preprocessor/traits/param/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>

/* PUBLIC */

// Precondition: name must always be the last remaining token in decl.
// Implementation: Must remove trailing NIL from decl to get actual name
// (NIL added so to avoid pp-tuple empty elems even after decl fully parsed).
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_PARSE(decl_traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits), \
            BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
            BOOST_PP_EMPTY \
        ) \
    )

// Expand to `[...] name | EMPTY()` (ellipses `...` for variadic templates).
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_AUX_NAME_INDEX, traits)()

#endif // #include guard

