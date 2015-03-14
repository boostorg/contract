
#ifndef BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_KEY_HPP_
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_KEY_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/index/class.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/class.hpp>
#include <boost/contract/ext_/preprocessor/keyword/struct.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PUBLIC */

// Expand to `class | struct` (cannot be empty).
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_KEY(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_KEY, traits)

#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_KEY_PARSE(decl_traits) \
    BOOST_PP_EXPAND(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_KEY_PARSE_ARGS_ \
            decl_traits)

/* PRIVATE */

// Implementation: If decl does not start with `class`, it must (and therefore
// it is here assumed to) start with `struct` (otherwise pp errors).
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_KEY_PARSE_ARGS_(decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CLASS_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_KEY_CLASS_ \
    , \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_KEY_STRUCT_ \
    )(decl, traits)

// Precondition: decl = `class ...`.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_KEY_CLASS_(decl, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_CLASS_REMOVE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK(traits, class) \
    )

// Precondition: decl = `struct ...`.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_KEY_STRUCT_(decl, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_STRUCT_REMOVE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK(traits, struct) \
    )

#endif // #include guard

