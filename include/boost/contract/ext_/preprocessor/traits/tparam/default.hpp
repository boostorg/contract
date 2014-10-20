
#ifndef BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_DEFAULT_HPP_
#define BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_DEFAULT_HPP_

#include <boost/contract/ext_/preprocessor/traits/tparam/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/default.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

// PRIVATE //

// Precondition: sign is `default ...`.
#define BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_DEFAULT_REPLACE_(sign, traits) \
    ( \
        BOOST_PP_EMPTY(), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_REPLACE( \
            traits, \
            BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_AUX_DEFAULT_INDEX, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_DEFAULT_REMOVE_FRONT(sign) \
            BOOST_PP_EMPTY \
        ) \
    )

// PUBLIC //

#define BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_DEFAULT_PARSE_EMPTY(sign_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, sign_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK( \
            BOOST_PP_TUPLE_ELEM(2, 1, sign_traits), \
            BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_DEFAULT_PARSE_REPLACE_D_S( \
        d, s, sign_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_DEFAULT_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 0, sign_traits)), \
        BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_DEFAULT_REPLACE_ \
    , \
        sign_traits BOOST_PP_TUPLE_EAT(2) \
    ) sign_traits

#define BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_DEFAULT_PARSE_REPLACE(sign_traits) \
    BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_DEFAULT_PARSE_REPLACE_D_S(1, 1, \
            sign_traits)

// Expand to `(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_DEFAULT(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
        BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_AUX_DEFAULT_INDEX, \
        traits \
    )()

#endif // #include guard


