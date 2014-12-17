
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_ADT_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_ADT_HPP_

#include <boost/contract/ext_/preprocessor/utility/nil.hpp>
#include <boost/contract/ext_/preprocessor/utility/expand.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/replace.hpp>

// These macros Abstract the Data Type (ADT) used to implement the traits
// (pp-sequence, pp-array, pp-list, etc.) and signature (pp-tuple, etc.).
// NOTE: These macros are typically not used by users. They are provided here
// in case users want to implement their own signature parsers using the
// ..._PARSE macros directly (instead of using the already provided macros).

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_FIRST_(sign, traits) sign

#define BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_SECOND_(sign, traits) traits

/* PUBLIC */

// Traits (sequence).

// Usage: ..._ELEM(index, traits)
#define BOOST_CONTRACT_EXT_PP_TRAITS_ELEM BOOST_PP_SEQ_ELEM

#define BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, trait) traits (trait)

// Usage: ..._REPLACE(traits, index, trait)
#define BOOST_CONTRACT_EXT_PP_TRAITS_REPLACE BOOST_PP_SEQ_REPLACE

// Signature-Traits (2-tuple).

// Create a `sign_traits` data structure to start parsing specified signature.
// Implementation: Leading NIL is used to handle empty macro params (on MSVC).
#define BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_INIT(sign) (sign, BOOST_PP_NIL)

// Expand to final traits after they have been parsed from signature.
// Implementation: Also removes leading NIL.
#define BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_DONE(sign_traits) \
    BOOST_CONTRACT_EXT_PP_NIL_REMOVE_FRONT( \
            BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_SECOND(sign_traits))

// NOTE: Using `BOOST_PP_TUPLE_ELEM(2, 0, sign_traits)` instead of this
// confuses MSVC macro expansion sometimes (OK on GCC, CLang, Wave, etc.).
#define BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_FIRST(sign_traits) \
    BOOST_CONTRACT_EXT_PP_EXPAND1( \
            BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_FIRST_ sign_traits)

// NOTE: Using `BOOST_PP_TUPLE_ELEM(2, 1, sign_traits)` instead of this
// confuses MSVC macro expansion sometimes (OK on GCC, CLang, Wave, etc.).
#define BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_SECOND(sign_traits) \
    BOOST_CONTRACT_EXT_PP_EXPAND1( \
            BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_SECOND_ sign_traits)

#endif // #include guard

