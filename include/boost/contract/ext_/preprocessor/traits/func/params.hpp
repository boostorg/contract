
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_HPP_

#include <boost/contract/ext_/preprocessor/traits/param.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/func_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/keyword_list.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/list.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PUBLIC */

// Expand to EMPTY() if no function formal parameters, otherwise expand to
// pp-seq of param. traits (each pp-seq elem. to be inspected via PARAM_TRAITS).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_PARAMS_INDEX, traits)()

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_PARSE_D(d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_LIST_TRAITS_PUSH_BACK_PARSE_D(d, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits), \
        BOOST_PP_EMPTY(), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_ \
    )

/* PRIVATE */
            
// Precondition: decl = `(,,,) ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_(d, decl) \
    BOOST_CONTRACT_EXT_PP_VOID_LIST_TRAITS_PARSE_D_1(d, \
        decl, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_PARAM_PARSE_, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_IS_DEFAULT_, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_REPLACE_DEFAULT_PARSE_ \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_PARAM_PARSE_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_IS_DEFAULT_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_IS_DEFAULT_FRONT(decl)

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_REPLACE_DEFAULT_PARSE_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_REPLACE_DEFAULT_PARSE_D(d, decl)

#endif // #include guard

