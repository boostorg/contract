
#ifndef BOOST_CONTRACT_EXT_PP_BASE_TRAITS_TYPE_HPP_
#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_TYPE_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/index/base.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/contract/ext_/preprocessor/utility/nil.hpp>
#include <boost/contract/ext_/preprocessor/parenthesize.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PUBLIC */

// Expand to `(,,,)`, for example: `(vector<T>)` or `(map<U, V>)`.
#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_TYPE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_BASE_TYPE, traits)

// Implementation: EXPAND and REM to force proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_TYPE_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_BASE_TRAITS_TYPE_PARSE_EXPAND_( \
            (BOOST_PP_TUPLE_REM_CTOR(2, decl_traits)))

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_TYPE_PARSE_EXPAND_(decl_traits) \
    BOOST_PP_EXPAND(BOOST_CONTRACT_EXT_PP_BASE_TRAITS_TYPE_PARSE_ARGS_ \
            decl_traits)

#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_TYPE_PARSE_ARGS_(decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_PARENTHESIZE( \
                    BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK(decl)) \
        ) \
    )

#endif // #include guard

