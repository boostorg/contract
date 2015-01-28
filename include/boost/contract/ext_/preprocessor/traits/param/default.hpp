
#ifndef BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_HPP_
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_HPP_

#include <boost/contract/ext_/preprocessor/traits/param/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/default.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PRIVATE */

// Precondition: decl = `default ...`.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_( \
        default_, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(traits), \
            BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(default_), \
                default_ \
            , \
                (default_) \
            ) \
            BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_PARSE_ARGS_( \
        decl, traits) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_DEFAULT_REMOVE_FRONT(decl), traits)

/* PUBLIC */

// TODO: For consistency with all other PARSE macros, and REPLACE_PARSE below,
// this should be called EMPTY_DEFAULT_PARSE, and the one below
// REPLACE_DEFAULT_PARSE.

// Init. default argument to EMPTY without altering decl.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_PARSE_EMPTY(decl_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits), BOOST_PP_EMPTY) \
    )

// Replace previously init. default argument with what's parsed from decl.
// Precondition: decl = `default ...`.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_PARSE(decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_REPLACE_PARSE_ARGS_ \
        decl_traits \
    )

// Expand to `(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_AUX_DEFAULT_INDEX, traits)()

#endif // #include guard


