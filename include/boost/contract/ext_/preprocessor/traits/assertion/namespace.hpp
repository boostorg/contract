
#ifndef BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion/kind.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/namespace.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/as.hpp>
#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

/* PUBLIC */

// Precondition: decl = `name`.
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NAME_PARSE( \
        decl_traits) \
    ( \
        BOOST_PP_NIL \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_traits), \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_traits) \
        ) \
    )

// NOTE: This extra macro is needed for proper expansion (on MSVC).
// Precondition: decl = `(new-name) as ...`.
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_REMOVE_PAREN_AS_(decl)\
    BOOST_CONTRACT_EXT_PP_KEYWORD_AS_REMOVE_FRONT(BOOST_PP_TUPLE_EAT(1) decl)
        
// Precondition: decl = `namespace (new-name) as ...`.
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NEW_NAME_PARSE( \
        decl_traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_REMOVE_PAREN_AS_( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_NAMESPACE_REMOVE_FRONT( \
                BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST( \
                    decl_traits \
                ) \
            ) \
        ) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_traits), \
            BOOST_PP_TUPLE_REM_CTOR(1, \
                BOOST_CONTRACT_EXT_PP_PAREN_FRONT( \
                    BOOST_CONTRACT_EXT_PP_KEYWORD_NAMESPACE_REMOVE_FRONT( \
                        BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_traits) \
                    ) \
                ) \
            ) \
        ) \
    )

// decl = namespace (new-name) as name
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS(decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NEW_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND_SET(namespace, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl \
    )))))

// Index 0 below already used and reserved for ASSERTION_TRAITS_KIND.

// Expand to `token`.
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NEW_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM(1, traits)

// Expand to `token`.
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM(2, traits)

#endif // #include guard

