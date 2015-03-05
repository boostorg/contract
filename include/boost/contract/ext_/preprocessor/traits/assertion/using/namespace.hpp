
#ifndef BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_HPP_
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/assertion_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/namespace.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PUBLIC */

// Expand to `namespace | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_AUX_NAMESPACE_INDEX,\
        traits \
    )()

// TODO: The EXPAND below seem to be needed at least on MSVC (and at least most
// of the times...). Apply EXPAND everywhere based on following rule: The
// general rule could be to use EXPAND whenever the macro invocation does not
// explicitly read the parameter list's parenthesis, for example:
//  F(x) // explicit paren => no expand
//  IF(c, F, G)(x, y) // explicit paren (after the IF) => no expand
//  EXPAND(M IF(c, (x, y), (a, b))) // no explicit paren (they are "hidden"
//                                  // inside IF(...)) => use expand
//  M args // no explicit paren (they are "hidden" inside args = (x, y)) =>
//         // use expand

#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_PARSE( \
        decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_PARSE_ARGS_ \
        decl_traits \
    )

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_PARSE_ARGS_( \
        decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_NO_ \
    )(decl, traits)

// Precondition: decl = `namespace ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_YES_( \
        decl, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_NAMESPACE_REMOVE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                namespace BOOST_PP_EMPTY) \
    )

#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_NO_( \
        decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))

#endif // #include guard

