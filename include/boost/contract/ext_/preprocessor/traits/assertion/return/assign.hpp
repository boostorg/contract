
#ifndef BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_ASSIGN_HPP_
#define BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_ASSIGN_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/index/assertion.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/return.hpp>
#include <boost/contract/ext_/preprocessor/utility/nil.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PUBLIC */

// Expand to `name =` (note trailing `=` that cannot be removed via pp).
#define BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_ASSIGN(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_RETURN_ASSERTION_ASSIGN, \
        traits \
    )

#define BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_ASSIGN_PARSE( \
        decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_ASSIGN_PARSE_ARGS_ \
        decl_traits \
    )
    
/* PRIVATE */

// Precondition: decl = `name = return NIL`.
#define BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_ASSIGN_PARSE_ARGS_( \
        decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK(traits, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_RETURN_REMOVE_BACK( \
            BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                decl \
            )) \
        ) \
    )

#endif // #include guard    

