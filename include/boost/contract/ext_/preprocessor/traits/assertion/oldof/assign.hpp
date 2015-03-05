
#ifndef BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_ASSIGN_HPP_
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_ASSIGN_HPP_

#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/assertion_index.hpp>
#include <boost/contract/ext_/preprocessor/utility/nil.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PUBLIC */

// Expand to `name = ` (note trailing `=` that cannot be removed via pp).
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_ASSIGN(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_AUX_ASSIGN_INDEX, \
        traits \
    )

#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_ASSIGN_PARSE( \
        decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_ASSIGN_PARSE_ARGS_ \
        decl_traits \
    )
    
/* PRIVATE */

// Precondition: decl = `name = OLDOF_OPERATOR_ NIL`.
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_ASSIGN_PARSE_ARGS_( \
        decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
            BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_OPERATOR_REMOVE_BACK( \
            BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                decl \
            )) \
        ) \
    )

#endif // #include guard    

