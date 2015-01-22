
#ifndef BOOST_CONTRACT_EXT_PP_NAMESPACE_ALIAS_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ALIAS_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/namespace.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/as.hpp>
#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/contract/ext_/preprocessor/utility/expand.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PRIVATE */

// Precondition: decl = `name` (this name must be wrapped with extra paren.
// because in general (i.e., for other aliases) it can contain commas.
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ALIAS_TRAITS_NAME_(decl, traits) \
    ( \
        BOOST_PP_NIL \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, (decl)) \
    )

// Precondition: decl = `(new-name) as ...`.
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ALIAS_TRAITS_NEW_NAME_(decl, traits) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ALIAS_TRAITS_NAME_( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_AS_REMOVE_FRONT(BOOST_PP_TUPLE_EAT(1) \
                decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_REM_CTOR(1, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl))\
            BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `namespace ...`.
// Implementation: Pushes back traits: kind = `namespace`, template-params =
// EMPTY, and namespace = EMPTY (then ready for new-name and name traits).
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ALIAS_TRAITS_PARSE_ARGS_(decl, traits) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ALIAS_TRAITS_NEW_NAME_( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_NAMESPACE_REMOVE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
                BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
                    traits, \
                    namespace \
                ), \
                BOOST_PP_EMPTY \
            ), \
            BOOST_PP_EMPTY \
        ) \
    )

/* PUBLIC */

// Precondition: decl = `namespace (new-name) as name`.
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ALIAS_TRAITS_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
        BOOST_CONTRACT_EXT_PP_NAMESPACE_ALIAS_TRAITS_PARSE_ARGS_ \
        decl_traits \
    )

// Inspect these traits using PP_ALIAS_TRAITS_... macros.

#endif // #include guard

