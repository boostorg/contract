
#ifndef BOOST_CONTRACT_EXT_PP_BASE_TRAITS_CLASSIFIERS_HPP_
#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_CLASSIFIERS_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/base_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/keyword.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/virtual.hpp>
#include <boost/contract/ext_/preprocessor/keyword/private.hpp>
#include <boost/contract/ext_/preprocessor/keyword/protected.hpp>
#include <boost/contract/ext_/preprocessor/keyword/public.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PUBLIC */

// Expand to `public | protected | private | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_ACCESS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_BASE_TRAITS_AUX_ACCESS_INDEX, traits)()

// Expand to `virtual | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_BASE_TRAITS_AUX_VIRTUAL_INDEX, traits)()

// Implementation: Do NOT use EXPAND here for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_CLASSIFIERS_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL_1ST_CHECK_ decl_traits

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL_1ST_CHECK_(decl, traits)\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VIRTUAL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL_1ST_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL_1ST_NO_ \
    )(decl, traits)

// Precondition: decl = `virtual ...`.
#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL_1ST_YES_(decl, traits) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL_1ST_PUSH_BACK_ \
        BOOST_CONTRACT_EXT_PP_BASE_TRAITS_ACCESS_( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_VIRTUAL_REMOVE_FRONT(decl), \
            traits \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL_1ST_PUSH_BACK_(decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
            virtual BOOST_PP_EMPTY))

#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL_1ST_NO_(decl, traits) \
    BOOST_PP_EXPAND(BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL_2ND_CHECK_ \
            BOOST_CONTRACT_EXT_PP_BASE_TRAITS_ACCESS_(decl, traits))
    
#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL_2ND_CHECK_(decl, traits)\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VIRTUAL_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL_2ND_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL_2ND_NO_ \
    )(decl, traits)

// Precondition: decl = `virtual ...`.
#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL_2ND_YES_(decl, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_VIRTUAL_REMOVE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, virtual BOOST_PP_EMPTY) \
    )

#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL_2ND_NO_(decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))

#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_ACCESS_(decl, traits) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_KEYWORD3_TRAITS_PARSE( \
            decl, \
            public, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PUBLIC_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_PUBLIC_REMOVE_FRONT, \
            protected, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PROTECTED_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_REMOVE_FRONT, \
            private, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PRIVATE_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_PRIVATE_REMOVE_FRONT \
        ), \
        traits \
    )

#endif // #include guard

