
#ifndef BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/oldof.hpp>

// TODO: Try to commonize this and params.hpp (if at all possible).


// TODO: I should try to find a pattern for macro expansion that reliably works
// on MSVC (and GCC, and CLang). Try to wrap all the IF construct below with
// EXPAND but they look like they require a double expansion: 1st expansion to
// the macro to execute, and 2nd expansion to execute it.
// In theory instead, constructs like `M args` do not need EXPAND because they
// do not require a double expansion. Maybe, after EXPAND is added to all 
// `IF(cond, M1, M2)(args)` then EXPAND will not longer be needed by `M args`,
// so try to remove EXPAND for `M args` then.

// TODO: Do I really need those? Decide that *after* I fix all EXPANDs.

//#define BOOST_CONTRACT_EXT_PP_EXPAND_ONCE(tokens) tokens

#define BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND_(decl, traits) traits

#define BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_traits) \
    BOOST_PP_EXPAND(BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND_ decl_traits)

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_REPLACE_OLDOF_( \
        d, decl_seq, traits) \
    ( \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D( \
                    d, \
                    ( \
                        BOOST_PP_SEQ_HEAD(decl_seq), \
                        BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits) \
                    ) \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_PUSH_BACK_ASSERTION_( \
        d, decl_seq, traits) \
    ( \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND( \
                BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_D(d, \
                    BOOST_PP_SEQ_HEAD(decl_seq) \
                ) \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_OP_ARGS_(d, decl_seq, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_TRAITS_IS_OLDOF_FRONT( \
            BOOST_PP_SEQ_HEAD(decl_seq)), \
        BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_REPLACE_OLDOF_ \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_PUSH_BACK_ASSERTION_ \
    )(d, decl_seq, traits)

#define BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_OP_(d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_OP_ARGS_(d, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )
        
#define BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_PRED_(d, decl_traits) \
    BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM( \
            2, 0, decl_traits)), 1)

// Implementation: SEQ_POP_BACK removes trailing NIL just added below.
#define BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_RETURN_(decl_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(2, 1, \
                decl_traits)) \
    )

// TODO: If all assertions, params, tparams, etc use the WHILE to iterate the
// entire decl_seq then SEQ_FOLD_LEFT could be used instead. Otherwise, use
// WHILE here because more generic anyway so this lib uses _D while users can
// use SEQ_FOLD_LEFT and other SEQ alg with all their _S, _Z, etc iterations.

#define BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_(d, decl_seq) \
    BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_RETURN_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_PRED_, \
            BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_OP_, \
            ( \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT \
            ) \
        ) \
    )

/* PUBLIC */

// Expand decl_seq = `(assrtion1)...(assertion-n)` to pp-seq of assertion
// traits, otherwise expand decl_seq = `EMPTY()` to EMPTY().
// NOTE: Variadic assertion enum. `( ) | ( assertion1, ..., assertion-n[,] )`
// can be transformed to EMPTY() or pp-seq using EXT_PP_VARIADIC_ENUM_TO_SEQ.
#define BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_PARSE_D(d, decl_seq) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        ((BOOST_PP_NIL), BOOST_PP_EMPTY) BOOST_PP_TUPLE_EAT(2) \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_ \
    )(d, decl_seq)

#endif // #include guard

