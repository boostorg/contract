
#ifndef BOOST_CONTRACT_EXT_PP_BASE_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/base/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/base/classifiers.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
    
/* PUBLIC */

// Precondition: decl = `{[public | protected | private] [virtual] | [virtual]
// [public | protected | private]} wrapped-type`.
#define BOOST_CONTRACT_EXT_PP_BASE_TRAITS_PARSE(decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_DONE( \
    BOOST_CONTRACT_EXT_PP_BASE_TRAITS_TYPE_PARSE( \
    BOOST_CONTRACT_EXT_PP_BASE_TRAITS_CLASSIFIERS_PARSE( \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_INIT( \
        decl BOOST_PP_NIL \
    ))))

#endif // #include guard

