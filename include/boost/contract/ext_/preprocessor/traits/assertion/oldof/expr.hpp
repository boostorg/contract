
#ifndef BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_EXPR_HPP_
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_EXPR_HPP_

#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/assertion_index.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>

/* PUBLIC */

// Expand to `...` (tokens).
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_EXPR(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_AUX_EXPR_INDEX, traits)

#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_EXPR_PARSE(decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_EXPR_PARSE_ARGS_ \
        decl_traits \
    )

/* PRIVATE */

// Precondition: decl = `(OLDOF expr) ...`
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_EXPR_PARSE_ARGS_( \
        decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(1) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_OPERATOR_REMOVE_FRONT(\
                BOOST_PP_TUPLE_REM_CTOR( \
                    1, BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl) \
                ) \
            ) \
        ) \
    )

#endif // #include guard

