
#ifndef BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_HPP_
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_HPP_

#include <boost/contract/ext_/preprocessor/traits/param/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/default.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PRIVATE */

// Precondition: decl = `default ...`.
// Implementation: NIL used as tuples cannot have EMTPY() elems (in MSVC).
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_(decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_REPLACE( \
            traits, \
            BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_AUX_DEFAULT_INDEX, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_DEFAULT_REMOVE_FRONT(decl) \
            BOOST_PP_EMPTY \
        ) \
    )

/* PUBLIC */

// Init. default argument to EMPTY without altering decl.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_PARSE_EMPTY(decl_traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_traits), \
            BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_PARSE_D_S( \
        d, s, decl_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_DEFAULT_FRONT( \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_traits)), \
        BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_ \
    , \
        decl_traits BOOST_PP_TUPLE_EAT(2) \
    ) decl_traits

// Replace previously init. default argument with what's parsed from decl.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_PARSE_D_S(1, 1, \
            decl_traits)

// Expand to `(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_AUX_DEFAULT_INDEX, traits)()

#endif // #include guard


