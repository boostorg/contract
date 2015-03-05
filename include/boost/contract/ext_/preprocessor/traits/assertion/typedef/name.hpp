
#ifndef BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NAME_HPP_
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NAME_HPP_

#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/assertion_index.hpp>
#include <boost/contract/ext_/preprocessor/keyword/typedef.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

/* PUBLIC */

// Expand to `(type,,,)`.
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_AUX_NAME_INDEX, \
        traits \
    )

// Precondition: decl = `typedef wrapped-type ...`.
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NAME_PARSE_D(d, \
        decl_traits) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_PARSE_D(d, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_TYPEDEF_REMOVE_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) \
            ) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )
    
#endif // #include guard    

