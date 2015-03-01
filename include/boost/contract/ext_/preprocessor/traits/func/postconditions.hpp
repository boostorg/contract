
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/postcondition.hpp>

// TODO: Think how to commonize this code with precondition() and template()
// (maybe just use keyword_paren for all of them...).

/* PUBLIC */

// Expand to pp-seq of postcondition assertion traits to be inspected via
// ASSERTION_TRAITS macro, or to EMPTY() if no postconditions.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_POSTCONDITIONS_INDEX, traits \
    )()

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_PARSE_D( \
        d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_PARSE_ARGS_(d, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_PARSE_ARGS_( \
        d, decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_POSTCONDITION_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_NO_ \
    )(d, decl, traits)

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_NO_( \
        unused, decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))

// Precondition: decl = `postcondition(,,,) ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_YES_(d, decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_(d, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_POSTCONDITION_REMOVE_FRONT(decl), \
        traits \
    )

// Precondition: decl = `(,,,) ...` from `postcondition(,,,) ...` originally in
// decl. This macro will also parse `(,,,)` into a pp-seq of assertion traits.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_(d, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_EXPAND_TRAITS_( \
                BOOST_CONTRACT_EXT_PP_ENUM_LIST_TRAITS_PARSE_D_1(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_1, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_1, \
  BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_1 \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_IS_OLDOF_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl)

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_REPLACE_OLDOF_PARSE_( \
        d, l, decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_EXPAND_TRAITS_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

#endif // #include guard

