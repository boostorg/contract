
#ifndef BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME_HPP_
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/assertion_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/assertion_index.hpp>
#include <boost/contract/ext_/preprocessor/utility/nil.hpp>
#include <boost/contract/ext_/preprocessor/parenthesize.hpp>

/* PUBLIC */

// Expand to `(name,,,)` (this name is wrapped within parenthesis because in
// general it can contain commas, for example for template aliases).
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_AUX_NAME_INDEX, \
        traits \
    )

#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME_PARSE( \
        decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME_PARSE_ARGS_ \
        decl_traits \
    )
    
/* PRIVATE */

// Precondition: decl = `name NIL`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME_PARSE_ARGS_( \
        decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
            BOOST_CONTRACT_EXT_PP_PARENTHESIZE( \
                    BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK(decl)) \
        ) \
    )

#endif // #include guard    

