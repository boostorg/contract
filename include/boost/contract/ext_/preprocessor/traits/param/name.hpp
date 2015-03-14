
#ifndef BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_HPP_
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/index/param.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

/* PUBLIC */

// Expand to `[...] name | EMPTY()` (ellipses `...` for variadic templates).
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_PARAM_NAME, traits)()

// Precondition: name must always be the last remaining token in decl.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_PARSE(decl_traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK( \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_traits), \
            BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                    BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)) \
            BOOST_PP_EMPTY \
        ) \
    )

#endif // #include guard

