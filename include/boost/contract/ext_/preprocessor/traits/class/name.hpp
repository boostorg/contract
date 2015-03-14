
#ifndef BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_NAME_HPP_
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_NAME_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/index/class.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PUBLIC */

// Expand to `name`.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_NAME, traits)

// Precondition: decl = `(name) ...`.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_NAME_PARSE(decl_traits) \
    BOOST_PP_EXPAND(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_NAME_PARSE_ARGS_ \
            decl_traits)

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_NAME_PARSE_ARGS_(decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(1) decl, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK( \
            traits, \
            BOOST_PP_TUPLE_REM_CTOR(1, \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
        ) \
    )

#endif // #include guard

