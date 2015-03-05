
#ifndef BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_HPP_
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/assertion_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/template.hpp>
#include <boost/contract/ext_/preprocessor/keyword/using.hpp>
#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

/* PUBLIC */

// Expand to `(c++-template-parameters,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_AUX_TEMPLATE_PARAMS_INDEX,\
        traits \
    )()

// Precondition: decl = `[template(,,,)] using ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_PARSE( \
        decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_ARGS_ \
        decl_traits \
    )

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_ARGS_( \
        decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_NO_ \
    )(decl, traits)

// Precondition: decl = `template( c++-template-parameter, ... ) using ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_YES_( \
        decl, traits) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl), traits)
        
// Precondition: decl = `using ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_NO_( \
        decl, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_USING_REMOVE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY) \
    )

// Precondition: decl = `( c++-template-parameter, ... ) using ...`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS_( \
        decl, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_USING_REMOVE_FRONT( \
                BOOST_PP_TUPLE_EAT(0) decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl) BOOST_PP_EMPTY) \
    )

#endif // #include guard

