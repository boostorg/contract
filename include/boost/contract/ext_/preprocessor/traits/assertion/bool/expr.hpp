
#ifndef BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_EXPR_HPP_
#define BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_EXPR_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/assertion_index.hpp>

/* PRIVATE */

// Precondition: decl = `... NIL`.
#define BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_EXPR_PARSE_ARGS_( \
        decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK(decl)) \
    )

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_EXPR_PARSE(decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_EXPR_PARSE_ARGS_ \
        decl_traits \
    )
    
// Expand to `...` (tokens).
#define BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_EXPR(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_AUX_EXPR_INDEX, traits)

#endif // #include guard    

