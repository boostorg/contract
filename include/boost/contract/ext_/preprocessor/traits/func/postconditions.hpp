
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertions.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/postcondition.hpp>
#include <boost/contract/ext_/preprocessor/variadic/enum_to_seq.hpp>

// TODO: Rename this postcondition*S* (plural, like for params, etc). The same
// applies to precondition*s*, class invariant*s*, etc (even if their keywords
// are singular, the traits should be named plural because the expand to seq).

/* PRIVATE */

// TODO: Thinks how to commonize this code with precondition() and template()
// (maybe just use keyword_paren for all of them...).

// TODO: If all TO_SEQ can be called within the params, tparams, assertion, etc.
// parsing macros, move those conversions there (so they are hidden to the
// caller).

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_EXPAND_TRAITS_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

// Precondition: decl = `(,,,) ...` from `postcondition(,,,) ...` originally in
// decl. This macro will also parse `(,,,)` into a pp-seq of assertion traits.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_(d, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_EXPAND_TRAITS_( \
                BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_PARSE_D(d, \
                    BOOST_PP_EXPAND( \
                        BOOST_CONTRACT_EXT_PP_VARIADIC_ENUM_TO_SEQ \
                        BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl) \
                    ) \
                ) \
            ) \
            BOOST_PP_EMPTY \
        ) \
    )

// Precondition: decl = `postcondition(,,,) ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_YES_(d, decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_(d, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_POSTCONDITION_REMOVE_FRONT(decl), \
        traits \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_NO_( \
        unused, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_PARSE_ARGS_( \
        d, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_POSTCONDITION_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_NO_ \
    )(d, decl, traits)

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_PARSE_D( \
        d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_PARSE_ARGS_(d, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Expand to pp-seq of postcondition assertion traits to be inspected via
// ASSERTION_TRAITS macro, or to EMPTY() if no postconditions.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_POSTCONDITIONS_INDEX, traits \
    )()

#endif // #include guard

