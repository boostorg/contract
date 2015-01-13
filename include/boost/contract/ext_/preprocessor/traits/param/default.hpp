
#ifndef BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_HPP_
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_HPP_

#include <boost/contract/ext_/preprocessor/traits/param/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/default.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PRIVATE */

// Precondition: sign is `default ...`.
// Implementation: NIL used as tuples cannot have EMTPY() elems (on MSVC).
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_(sign, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_REPLACE( \
            traits, \
            BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_AUX_DEFAULT_INDEX, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_DEFAULT_REMOVE_FRONT(sign) \
            BOOST_PP_EMPTY \
        ) \
    )

/* PUBLIC */

// Init. default argument to EMPTY without altering sign.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_PARSE_EMPTY(sign_traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_FIRST(sign_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_SECOND(sign_traits), \
            BOOST_PP_EMPTY \
        ) \
    )

// Replace previously init. default argument with what parsed from sign.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_PARSE_D_S( \
        d, s, sign_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_DEFAULT_FRONT( \
            BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_FIRST(sign_traits)), \
        BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_ \
    , \
        sign_traits BOOST_PP_TUPLE_EAT(2) \
    ) sign_traits

#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_PARSE(sign_traits) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_PARSE_D_S(1, 1, \
            sign_traits)

// Expand to `(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_AUX_DEFAULT_INDEX, \
        traits \
    )()

#endif // #include guard


