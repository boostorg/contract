
#ifndef BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NEW_NAME_HPP_
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NEW_NAME_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/index/assertion.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/as.hpp>
#include <boost/contract/ext_/preprocessor/keyword/namespace.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>

/* PUBLIC */

// Expand to `new-name`.
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NEW_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_NAMESPACE_ASSERTION_NEW_NAME, \
        traits \
    )

// Precondition: decl = `namespace (new-name) as ...`.
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NEW_NAME_PARSE( \
        decl_traits) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NEW_NAME_( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_NAMESPACE_REMOVE_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )
    
/* PRIVATE */

// Precondition: decl = `(new-name) as ...`.
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NEW_NAME_( \
        decl, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_AS_REMOVE_FRONT( \
                BOOST_PP_TUPLE_EAT(1) decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_REM_CTOR(1, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
        ) \
    )

#endif // #include guard

