
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_OLDOF_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_OLDOF_HPP_

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_TRAITS_OLDOF_CAT_TO_COMMABOOST_CONTRACT_EXT_PP_TRAITS_OLDOF ,
// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_TRAITS_OLDOF_CAT_TO_EMPTYBOOST_CONTRACT_EXT_PP_TRAITS_OLDOF

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_TRAITS_IS_OLDOF_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT( \
            BOOST_CONTRACT_EXT_PP_TRAITS_OLDOF_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `..._TRAITS_ODLOF` (this can be
//               checked with `..._TRAITS_IS_OLDOF_FRONT` macro above).
#define BOOST_CONTRACT_EXT_PP_TRAITS_OLDOF_REMOVE_FRONT(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_EXT_PP_TRAITS_OLDOF_CAT_TO_EMPTY, tokens)

// This is the operator that decl. syntax must use to prefix old-of expressions:
// `{auto | wrapper-type} var = OLDOF_OPERATOR exr`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_OLDOF_OPERATOR \
    , BOOST_CONTRACT_EXT_PP_TRAITS_OLDOF

#endif // #include guard

