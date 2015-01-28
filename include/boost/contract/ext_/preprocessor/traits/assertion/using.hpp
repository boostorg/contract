
#ifndef BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion/using/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/using/new_name.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/using/namespace.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/using/template_params.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/kind.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_DONE_(decl_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

/* PUBLIC */

// Precondition: decl = `[template( c++-template-parameter, ... )]
//                       using [namespace | (new-name) as] wrapped-name`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_DONE_( \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_PARSE( \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_PARSE( \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE(using, \
        (decl BOOST_PP_NIL, BOOST_CONTRACT_EXT_PP_TRAITS_INIT) \
    ))))))

// ASSERTION_TRAITS_KIND(traits) expands to `using` for this assertion.

#endif // #include guard

