
#ifndef BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_TYPE_HPP_
#define BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_TYPE_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/assertion_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

/* PUBLIC */

// Expand to `auto | (type,,,)`.
#define BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_TYPE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_AUX_TYPE_INDEX, \
        traits \
    )

// Precondition: decl = `{auto | wrapped-type} ...`.
#define BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_TYPE_PARSE_D(d, \
        decl_traits) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D(d, \
                BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )
    
#endif // #include guard    

