
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/param.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/list.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/variadic/to_seq.hpp>
#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PRIVATE */
            
// Extra macro invocation needed for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_EXPAND_TRAITS_(decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

// Precondition: decl = `(,,,) ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_PARSE_ARGS_(d, decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_EXPAND_TRAITS_( \
                BOOST_CONTRACT_EXT_PP_VOID_LIST_TRAITS_PARSE_D(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
                    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_PARSE_D, \
                    BOOST_CONTRACT_EXT_PP_KEYWORD_IS_DEFAULT_FRONT, \
                    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_REPLACE_DEFAULT_PARSE_D \
                ) \
            ) \
        ) \
    )

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_PARSE_D(d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_PARSE_ARGS_(d, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Expand to EMPTY() if no function formal parameters, otherwise expand to
// pp-seq of param. traits (each pp-seq elem. to be inspected via PARAM_TRAITS).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_PARAMS_INDEX, traits)()

#endif // #include guard

