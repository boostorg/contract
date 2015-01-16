
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITION_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITION_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertions.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/precondition.hpp>

/* PRIVATE */

// Precondition: decl = `(,,,) ...` from `precondition(,,,) ...` originally in
// decl. This macro will also parse `(,,,)` into a pp-list of assertion traits.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITION_(decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS( \
                BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
    )

// Precondition: decl = `precondition(,,,) ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITION_YES_(decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITION_( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_PRECONDITION_REMOVE_FRONT(decl), \
        traits \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITION_NO_(decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_NIL))

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITION_PARSE_ARGS_( \
        decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PRECONDITION_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITION_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITION_NO_ \
    )(decl, traits)

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITION_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITION_PARSE_ARGS_ \
        decl_traits \
    )

#endif // #include guard

