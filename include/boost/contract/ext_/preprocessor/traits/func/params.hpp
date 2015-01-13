
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_HPP_

#include <boost/contract/ext_/preprocessor/traits/params.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/contract/ext_/preprocessor/utility/expand.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_PARSE_ARGS_(sign, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) sign \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS( \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(sign)) \
        ) \
    )

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_PARSE(sign_traits) \
    BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_PARSE_ARGS_ sign_traits)

// Expand to pp-list of function parameters. Each single parameter in this
// pp-list is inspected using PARAM_TRAITS macros.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_PARAMS_INDEX, traits)

#endif // #include guard

