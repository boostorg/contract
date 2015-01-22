
#ifndef BOOST_CONTRACT_EXT_PP_TYPEDEF_ALIAS_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ALIAS_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/type.hpp>
#include <boost/contract/ext_/preprocessor/keyword/typedef.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
            
/* PRIVATE */

// Precondition: decl = `new-name`.
// Implementation: First we have to push back the new name that is parsed now.
// After that, we push back the previously parsed type as the name (this is
// because the new name trait must come before the name trait, see also
// index.hpp).
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ALIAS_TRAITS_NEW_NAME_AND_NAME_( \
        decl_type, traits) \
    ( \
        BOOST_PP_NIL \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
                traits, \
                BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_type) \
                BOOST_PP_EMPTY \
            ), \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_type) \
        ) \
    )

// Precondition: decl = `wrapped-type ...`.
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ALIAS_TRAITS_TYPE_(d, decl, traits) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ALIAS_TRAITS_NEW_NAME_AND_NAME_( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_D(d, decl), traits)

// Precondition: decl = `typedef ...`.
// Implementation: Pushes back traits: kind = `typedef`, template-params =
// EMPTY, and namespace = EMPTY (then ready for new-name and name traits).
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ALIAS_TRAITS_PARSE_(d, decl, traits) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ALIAS_TRAITS_TYPE_( \
        d, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_TYPEDEF_REMOVE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
                BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
                    traits, \
                    typedef \
                ), \
                BOOST_PP_EMPTY \
            ), \
            BOOST_PP_EMPTY \
        ) \
    )
    
/* PUBLIC */

// Precondition: decl = `typedef wrapped-type new-name`.
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ALIAS_TRAITS_PARSE_D(d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ALIAS_TRAITS_PARSE_( \
        d, \
        BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_traits), \
        BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_traits) \
    )

// Inspect these traits using PP_ALIAS_TRAITS_... macros.

#endif // #include guard

