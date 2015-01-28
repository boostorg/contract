
#ifndef BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_EXPR_HPP_
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_EXPR_HPP_

/* PRIVATE */

// Precondition: decl = `(OLDOF expr) ...`
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_EXPR_PARSE_ARGS_( \
        decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(1) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_TRAITS_OLDOF_REMOVE_FRONT( \
                BOOST_PP_TUPLE_REM_CTOR( \
                    1, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl) \
                ) \
            ) \
        ) \
    )

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_EXPR_PARSE(decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_EXPR_PARSE_ARGS_ \
        decl_traits \
    )

// Expand to `...` (tokens).
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_EXPR(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_AUX_EXPR_INDEX, traits)

#endif // #include guard

