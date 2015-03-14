
#ifndef BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/param/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/param/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/param/default.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_PARSE_D(d, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_DONE( \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_EMPTY_DEFAULT_PARSE( \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_PARSE_D(d, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_INIT( \
        decl BOOST_PP_NIL \
    )))))

#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_PARSE_D(d, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_DONE( \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_EMPTY_DEFAULT_PARSE( \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_PARSE_D(d, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_INIT( \
        decl BOOST_PP_NIL \
    )))))

#endif // #include guard

