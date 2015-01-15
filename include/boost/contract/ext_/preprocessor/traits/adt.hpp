
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_ADT_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_ADT_HPP_

#include <boost/contract/ext_/preprocessor/utility/nil.hpp>
#include <boost/contract/ext_/preprocessor/utility/expand.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/replace.hpp>

// These macros Abstract the Data Type (ADT) used to represent declaration
// traits (pp-sequence, etc.).
// NOTE: These macros are typically not used by users. They are provided here
// in case users want to implement their own declaration parsers using the
// ..._PARSE macros directly (instead of using the already provided parsers).

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST_(decl, traits) decl

#define BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND_(decl, traits) traits

/* PUBLIC */

// Traits (pp-sequence).
// NOTE: It is in theory possible to change the traits representation (e.g.,
// from pp-sequence to pp-array) just changing theses macros (without changing
// any other macro in this library or in user code).

// Usage: ..._ELEM(index, traits)
#define BOOST_CONTRACT_EXT_PP_TRAITS_ELEM BOOST_PP_SEQ_ELEM

#define BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, trait) traits (trait)

// Usage: ..._REPLACE(traits, index, trait)
#define BOOST_CONTRACT_EXT_PP_TRAITS_REPLACE BOOST_PP_SEQ_REPLACE

// Declaration and traits (2-tuple).

// Create a `decl_traits` data structure to start parsing specified declaration.
// Implementation: Leading NIL needed to handle empty macro params (on MSVC).
#define BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT(decl) (decl, BOOST_PP_NIL)

// Expand to final traits after they have been parsed from declaration.
// Implementation: Also removes leading NIL.
#define BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_NIL_REMOVE_FRONT( \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_traits))

// NOTE: Using `BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)` instead of this
// confuses MSVC macro expansion sometimes (OK on GCC, CLang, Wave, etc.).
#define BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_traits) \
    BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST_ decl_traits)

// NOTE: Using `BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)` instead of this
// confuses MSVC macro expansion sometimes (OK on GCC, CLang, Wave, etc.).
#define BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_traits) \
    BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND_ decl_traits)

#endif // #include guard

