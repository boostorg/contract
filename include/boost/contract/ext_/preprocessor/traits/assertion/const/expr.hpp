
#ifndef BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_EXPR_HPP_
#define BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_EXPR_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/index/assertion.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/contract/ext_/preprocessor/utility/nil.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PUBLIC */

// Expand to `expr` (expr might or not be in parenthesis, like all bool expr).
#define BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_EXPR(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CONST_ASSERTION_EXPR, traits)

#define BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_EXPR_PARSE(decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_EXPR_PARSE_ARGS_ \
        decl_traits \
    )
    
/* PRIVATE */

// Precondition: decl = `... NIL`.
#define BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_EXPR_PARSE_ARGS_( \
        decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK(traits, \
                BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK(decl)) \
    )

#endif // #include guard    

