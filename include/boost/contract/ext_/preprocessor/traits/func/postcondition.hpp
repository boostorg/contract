
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITION_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITION_HPP_

#include <boost/contract/ext_/preprocessor/traits/aliases.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/postcondition.hpp>
#include <boost/contract/ext_/preprocessor/variadic/enum_to_seq.hpp>

/* PRIVATE */

// TODO: Thinks how to commonize this code with precondition() and template()
// (maybe just use keyword_paren for all of them...).

// TODO: If assertions need to be parsed as seq for consistency parse params
// as seq too. Then these PARSE macros can work on an arg named decl_seq
// instead of just decl. Shall all the PARSE macro take decl_traits (the called
// can pass TRAITS_INIT to FUNC_TRAITS_PARSE, etc)?

// TODO: All macros that return decl_traits should be named PARSE, and probably
// they should all do that (not just FUNC_TRAITS, but FUNC_TRAITS_PARSE with
// decl != EMPTY() in case of error, and same for params, etc).

// Precondition: decl = `(,,,) ...` from `postcondition(,,,) ...` originally in
// decl. This macro will also parse `(,,,)` into a pp-seq of assertion traits.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITION_(decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_PARSE( \
            ( \
                BOOST_PP_EXPAND( \
                    BOOST_CONTRACT_EXT_PP_SEQ_FROM_ENUM \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl) \
                ), \
                traits \
            ) \
        ) \
    )

// Precondition: decl = `postcondition(,,,) ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITION_YES_(decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITION_( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_POSTCONDITION_REMOVE_FRONT(decl), \
        traits \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITION_NO_(decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_NIL))

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITION_PARSE_ARGS_( \
        decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_POSTCONDITION_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITION_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITION_NO_ \
    )(decl, traits)

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITION_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITION_PARSE_ARGS_ \
        decl_traits \
    )

#endif // #include guard

