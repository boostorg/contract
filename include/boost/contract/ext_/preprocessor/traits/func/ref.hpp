
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/keyword.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/ref.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PRIVATE */

// Precondition: decl = `ref ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_REF_YES_(decl, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_REF_REMOVE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, ref ref BOOST_PP_EMPTY) \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_REF_NO_(decl, traits) \
    ( \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, ref BOOST_PP_EMPTY) \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_NO_(decl, traits) \
    ( \
        decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY) \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_REF_(decl, traits) \
    BOOST_PP_EXPAND(BOOST_PP_IIF( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_REF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_REF_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_REF_NO_ \
    )(decl, traits))
        
// Precondition: decl = `ref ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_YES_(decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_REF_( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_REF_REMOVE_FRONT(decl), traits)
        
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_PARSE_ARGS_(decl, traits) \
    BOOST_PP_EXPAND(BOOST_PP_IIF( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_REF_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_NO_ \
    )(decl, traits))

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_PARSE(decl_traits) \
    BOOST_PP_EXPAND(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_PARSE_ARGS_ \
            decl_traits)

// Expand to `ref | ref ref | EMPTY()` (ref for lvalue&, ref ref for rvalue&&).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_REF_INDEX, traits)()

#endif // #include guard

