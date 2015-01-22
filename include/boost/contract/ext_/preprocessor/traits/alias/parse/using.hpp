
#ifndef BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/template.hpp>
#include <boost/contract/ext_/preprocessor/keyword/using.hpp>
#include <boost/contract/ext_/preprocessor/keyword/namespace.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/as.hpp>
#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/contract/ext_/preprocessor/utility/expand.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>

/* PRIVATE */

// Name.

// Precondition: decl = `(name,,,)`.
#define BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NAME_(decl, traits) \
    ( \
        BOOST_PP_NIL \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
                decl \
            , \
                (decl) \
            ) \
        ) \
    )

// New name.

// Precondition: decl = `(new-name) as ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NEW_NAME_YES_(decl, traits) \
    BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NAME_( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_AS_REMOVE_FRONT(BOOST_PP_TUPLE_EAT(1) \
                decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl) BOOST_PP_EMPTY) \
    )

#define BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NEW_NAME_NO_(decl, traits) \
    BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NAME_(decl, \
            BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))

// TODO: Remove the trailing NIL from `EAT(1) decl NIL` below once NIL is added
// to the end of *all* decl by DECL_TRAITS_INIT.

// Precondition: decl = `(new-name) [as] ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NEW_NAME_CHECK_(decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AS_FRONT( \
            BOOST_PP_TUPLE_EAT(1) decl BOOST_PP_NIL), \
        BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NEW_NAME_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NEW_NAME_NO_ \
    )(decl, traits)

// Precondition: decl = `[(new-name) [as]] ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NEW_NAME_(decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NEW_NAME_CHECK_ \
    , \
        BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NEW_NAME_NO_ \
    )(decl, traits)

// Namespace.

// Precondition: decl = `namespace ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NAMESPACE_YES_(decl, traits) \
    BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NEW_NAME_( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_NAMESPACE_REMOVE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                namespace BOOST_PP_EMPTY) \
    )

#define BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NAMESPACE_NO_(decl, traits) \
    BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NEW_NAME_(decl, \
            BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))

// Precondition: decl = `[namespace] ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NAMESPACE_(decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NAMESPACE_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NAMESPACE_NO_ \
    )(decl, traits) \

// Template parameters.

// Precondition: decl = `( c++-template-parameter, ... ) using ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_TEMPLATE_PARAMS_PUSH_BACK_( \
        decl, traits) \
    BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NAMESPACE_( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_USING_REMOVE_FRONT( \
                BOOST_PP_TUPLE_EAT(0) decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl) BOOST_PP_EMPTY) \
    )

// Precondition: decl = `template( c++-template-parameter, ... ) using ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_TEMPLATE_PARAMS_YES_( \
        decl, traits) \
    BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_TEMPLATE_PARAMS_PUSH_BACK_( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl), traits)

// Precondition: decl = `using ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_TEMPLATE_PARAMS_NO_( \
        decl, traits) \
    BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_NAMESPACE_( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_USING_REMOVE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY) \
    )

#define BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_TEMPLATE_PARAMS_( \
        decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT(decl),  \
        BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_TEMPLATE_PARAMS_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_TEMPLATE_PARAMS_NO_ \
    )(decl, traits)

// Kind.

// Implementation: Pushes back kind = `using`.
#define BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_PARSE_ARGS_(decl, traits) \
    BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_TEMPLATE_PARAMS_(decl, \
            BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, using))

/* PRIVATE */

// Precondition: decl = `[template( c++-template-parameter, ... )]
//                       using [namespace | (new-name) as] wrapped-name`.
// Implementation: Invocation of these parsing macros must follow index.hpp.
#define BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
            BOOST_CONTRACT_EXT_PP_USING_ALIAS_TRAITS_PARSE_ARGS_ decl_traits)

// Inspect these traits using PP_ALIAS_TRAITS_... macros.

#endif // #include guard

