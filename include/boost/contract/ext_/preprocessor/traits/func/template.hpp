
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/param.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/list.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/template.hpp>
#include <boost/contract/ext_/preprocessor/keyword/default.hpp>
#include <boost/contract/ext_/preprocessor/variadic/to_seq.hpp>
#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PRIVATE */

// Extra macro invocation needed for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_EXPAND_TRAITS_(decl_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)

// Precondition: decl = `(,,,) ...` from `template(,,,) ...` originally in decl.
// This macro will also parse `(,,,)` into a pp-seq of template param traits.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_(d, decl, traits) \
    ( \
        BOOST_PP_EXPAND(BOOST_PP_TUPLE_EAT(0) decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                    template BOOST_PP_EMPTY), \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_EXPAND_TRAITS_( \
                BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_D(d, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl), \
                    BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_PARSE_D, \
                    BOOST_CONTRACT_EXT_PP_KEYWORD_IS_DEFAULT_FRONT, \
                    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_REPLACE_DEFAULT_PARSE_D \
                ) \
            ) \
        ) \
    )

// Precondition: decl = `template(,,,) ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_YES_(d, decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_(d, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_NO_(unused, decl, traits) \
    ( \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY), \
            BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_PARSE_ARGS_( \
        d, decl, traits) \
    BOOST_PP_EXPAND(BOOST_PP_IIF( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_NO_ \
    )(d, decl, traits))

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_PARSE_D(d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_PARSE_ARGS_(d, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Expand to `template | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_TEMPLATE_INDEX, traits)()

// Expand to EMPTY() if no function template parameters, otherwise expand to
// pp-seq of param. traits (each pp-seq elem. to be inspected via PARAM_TRAITS).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_PARAMS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_TEMPLATE_PARAMS_INDEX, \
        traits \
    )()

#endif // #include guard

