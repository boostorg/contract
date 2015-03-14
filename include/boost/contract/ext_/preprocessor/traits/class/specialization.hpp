
#ifndef BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_SPECIALIZATION_HPP_
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_SPECIALIZATION_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/index/class.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PUBLIC */

// Expand to `(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_SPECIALIZATION(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_SPECIALIZATION, \
        traits \
    )()

#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_SPECIALIZATION_PARSE(decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_SPECIALIZATION_PARSE_ARGS_ \
        decl_traits \
    )

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_SPECIALIZATION_PARSE_ARGS_( \
        decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_SPECIALIZATION_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_SPECIALIZATION_NO_ \
    )(decl, traits)

#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_SPECIALIZATION_NO_(decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK(traits, BOOST_PP_EMPTY))

#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_SPECIALIZATION_YES_(decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK(traits, \
                BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl) BOOST_PP_EMPTY) \
    )

#endif // #include guard

