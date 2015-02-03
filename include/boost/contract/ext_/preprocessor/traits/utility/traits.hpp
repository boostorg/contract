
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_TRAITS_HPP_

#include <boost/preprocessor/seq/pop_front.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/pop_back.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

// TODO: IIF(c, X, Y)(a, b) does not need to be wrapped by EXPAND
// (Boost.PP docs).

// TODO: #define macro order does NOT matter, so I can put PUBLIC before
// PRIVATE (Boost.PP docs).

// TODO: BOOST_PP_EXPAND has been used pervasively in many/most places by all
// the traits/* macros. This is an *EXPERIMENT* to see if I can get MSVC to
// expand better (e.g., never needed DEC_TRAITS_FIRST/SECOND instead of
// BOOST_PP_TUPLE_ELEM). At the end, clean this up by removing the EXPAND
// macros that are not actually needed. There are TODO comments where it was
// for some not clear reason not possible to use EXPAND. It seems that EXPAND
// should truly be needed only in the following cases:
//  EXPAND(X BOOST_PP_IIF(c, (a), (b))) --> X(a | b)
//  EXPAND(X a) --> X(b), where a = (b)
// And *NOT* by:
//  IIF(c, X, Y)(a) --> X(a) | Y(a)
//  EAT(n) ...
//  REM(n) ...
// But I still have to fully understand these... plus MSVC occasionally needs
// an extra EXPAND or level of indirection for proper expansion without an
// apparent logic for it (these might just be MSVC expansions bugs I have to
// deal with on a case-by-case bases, they seem to be limited in number...).

// TODO: Rename this file adt.hpp.

/* PUBLIC */

// These macros are not usually used by the users (unless they re-implement
// their own parsing macros).

// WARNING: PP_TUPLE_ELEM does not handle EMPTY() elements. Therefore, it is
// necessary to always postfix decl with NIL, (NIL), etc. (for declaration
// tokens, sequences, etc.) and to never apply DONE(traits) while these are
// elements inside decl_traits = (decl, triats) 2-tuple (or other pp-tuples).

// NOTE: In this library PARSE macros are so that:
// * PARSE(...) all expand to 2-tuple `(remaining-decl, parsed-traits)`.
// * PARSE(decl) starts parsing declaration tokens (init. decl_traits).
// * PARSE(decl_seq) start parsing pp-seq of declarations (init. decl_traits).
// * PARSE(decl_traits) interim parsing of declarations (no init. decl_traits).
// Some PARSE macros (the ones in utility/) do no parse multiple traits but only
// a single trait so they do not use the PP_TRAITS macros below but just report
// trait as tokens (this is documented by these macros).

// IMPLEMENTATION: In theory, it is possible to change traits representation
// just changing these macros however Boost.Preprocessor docs say that pp-seq
// are the fastest (always close to random access performance because they use
// iteration instead of recursion) and largest (up to 256 elements) data
// structure so there should be no reason to change representation from pp-seq.

// TODO: Can I make this private to this file (i.e., postfix it with "_")?
#define BOOST_CONTRACT_EXT_PP_TRAITS_INIT (BOOST_PP_NIL)
        
// TODO: Can I make this private to this file (i.e., postfix it with "_")?
// Usage: DONE(traits) (could expand to EMPTY()).
#define BOOST_CONTRACT_EXT_PP_TRAITS_DONE BOOST_PP_SEQ_POP_FRONT

// Usage: ELEM(index, traits)
#define BOOST_CONTRACT_EXT_PP_TRAITS_ELEM BOOST_PP_SEQ_ELEM

// TODO: Can I make this private to this file (i.e., postfix it with "_")?
#define BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, trait) traits (trait)

// Usage: POP_BACK(taits)
#define BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK BOOST_PP_SEQ_POP_BACK

#define BOOST_CONTRACT_EXT_PP_TRAITS_BACK(traits) \
    BOOST_PP_SEQ_ELEM(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(traits)), traits)

// DECLaration TRAITS.

// IMPORTANT: These DECL_TRAITS macros must not modify decl, they can only
// operate on traits. That is because different algorithms represent decl
// differently (as tokens, pp-seq, etc.) so it is up these algorithms using
// these DECL_TRAITS macro to maintain decl (which is here just passed along).
// Thus, these DECL_TRAITS macros are provided here just for convenience, they
// do not really add any functionality on top of the TRAITS macros #define
// above (but when possible use the DECL_TRAITS macros instead of re-writing
// them from scratch using the TRAITS macros above).

#define BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT(decl) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_INIT)

#define BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE(decl_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(2, 1, \
                decl_traits)) \
    )

#define BOOST_CONTRACT_EXT_PP_DECL_TRAITS_PUSH_BACK(decl_trait, traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_trait), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_trait)) \
    )

#endif // #include guard

