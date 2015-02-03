
#ifndef BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_CAPTURES_HPP_
#define BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_CAPTURES_HPP_

#include <boost/contract/ext_/preprocessor/traits/capture.hpp>

/* PRIVATE */

// Extra macro invocation needed for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARAMS_EXPAND_TRAITS_( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

// Precondition: decl = `( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_CAPTURES_( \
        d, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARAMS_EXPAND_TRAITS_(\
                BOOST_CONTRACT_EXT_PP_FIXED_LIST_TRAITS_PARSE_D(d , \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
                    BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_PARSE_D \
                ) \
            ) \
        ) \
    )

// Precondition: decl = `const( ,,, ) ...`.
#define BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_CAPTURES_PARSE_ARGS_( \
        d, decl, traits) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_CAPTURES_(d, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_CONST_REMOVE_FRONT(decl), \
        traits \
    )

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_CAPTURES_PARSE_D( \
        d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_CAPTURES_PARSE_ARGS_(d, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Expand to `pp-seq | EMPTY()`, pp-seq of capture traits to be inspected via
// PP_CAPTURE_TRAITS macros.
#define BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_CAPTURES(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_AUX_CAPTURES_INDEX, \
        traits \
    )

#endif // #include gaurd

