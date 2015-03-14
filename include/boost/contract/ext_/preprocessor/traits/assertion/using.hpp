
#ifndef BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion/using/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/using/new_name.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/using/namespace.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/using/template_params.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/key.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>

/* PUBLIC */

// ASSERTION_TRAITS_KEY(traits) expands to `using` for this assertion.

// Precondition: decl = `[template( c++-template-parameter, ... )]
//                       using [namespace | (new-name) as] wrapped-name`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_DONE( \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE_PARSE( \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_PARSE( \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KEY_PARSE(using, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_INIT( \
        decl BOOST_PP_NIL \
    )))))))

#endif // #include guard

