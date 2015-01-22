
#ifndef BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/param/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/param/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/param/default.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DONE_(decl_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_PARSE_D(d, decl) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DONE_( \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_PARSE_EMPTY( \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE_PARSE_D(d, \
        (decl BOOST_PP_NIL, BOOST_CONTRACT_EXT_PP_TRAITS_INIT) \
    ))))

#define BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_PARSE_D(d, decl) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DONE_( \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_PARSE_EMPTY( \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_PARSE_D(d, \
        (decl BOOST_PP_NIL, BOOST_CONTRACT_EXT_PP_TRAITS_INIT) \
    ))))

#endif // #include guard

