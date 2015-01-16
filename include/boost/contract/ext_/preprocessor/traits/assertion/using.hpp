
#ifndef BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion/kind.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/namespace.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/as.hpp>
#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

/* PRIVATE */
            
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_NAME_PAREN_(name) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(name), \
        name \
    , \
        (name) \
    )
        
// Precondition: decl = `(new-name) as ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_YES_( \
        decl, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_AS_REMOVE_FRONT( \
                BOOST_PP_TUPLE_EAT(1) decl) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl) BOOST_PP_EMPTY) \
    )

#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_NO_( \
        decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))

// Precondition: decl = `(new-name) ...`.
// Implementation: NIL after decl in case EAT removes last tokens in decl.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_MAYBE_( \
        decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AS_FRONT( \
            BOOST_PP_TUPLE_EAT(1) decl BOOST_PP_NIL), \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_NO_ \
    )(decl, traits)

// Precondition: decl = `using namespace ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_YES_( \
        decl, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_NAMESPACE_REMOVE_FRONT( \
                BOOST_CONTRACT_EXT_PP_KEYWORD_USING_REMOVE_FRONT(decl)) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                namespace BOOST_PP_EMPTY) \
    )

// Precondition: decl = `using ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_NO_( \
        decl, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_USING_REMOVE_FRONT(decl) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY) \
    )
    
// Precondition: decl = `template( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_YES_( \
        decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) \
        BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_PAREN_FRONT( \
                    BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl)) \
            BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_NO_( \
        decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))

/* PUBLIC */

// Precondition: decl = `wrapped-name`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME_PARSE( \
        decl_traits) \
    ( \
        BOOST_PP_NIL \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_traits), \
            BOOST_CONTRACT_EXT_PP_USING_ASSERTION_NAME_PAREN_( \
                    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_traits)) \
        ) \
    )
    
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_PARSE( \
        decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
                BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_traits)), \
            BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_MAYBE_ \
        , \
            BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_NO_ \
        ) decl_traits \
    )

// Precondition: decl = `using ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_PARSE( \
        decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_PP_IIF( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_USING_REMOVE_FRONT( \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST( \
                decl_traits \
            ))) \
        , \
            BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_YES_ \
        , \
            BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_NO_ \
        ) decl_traits \
    )

// TODO: Do I really need all these PP_EXPAND here?

#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_PARSE( \
        decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT( \
                BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_traits)), \
            BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_YES_ \
        , \
            BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_NO_ \
        ) decl_traits \
    )

// decl =   [template( c++-template-parameter, ... )]
//          using [namespace | (new-name) as] wrapped-name
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS(decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_PARSE( \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_PARSE( \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND_SET(using, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl \
    )))))))

// Index 0 below already used and reserved for ASSERTION_TRAITS_KIND.

// Expand to `(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM(1, traits)()

// Expand to `namespace | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM(2, traits)()

// Expand to `token | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM(3, traits)()

// Expand to `(,,,)`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM(4, traits)

#endif // #include guard

