
#ifndef BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_HPP_
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/param_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/default.hpp>
#include <boost/contract/ext_/preprocessor/parenthesize.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PUBLIC */

// Expand to `(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_AUX_DEFAULT_INDEX, traits)()

// Initialize default argument to EMPTY without altering decl.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_EMPTY_DEFAULT_PARSE(decl_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(BOOST_PP_TUPLE_ELEM(2, 1, \
                decl_traits), BOOST_PP_EMPTY) \
    )

// Replace previously init. default argument with what's parsed from decl.
// Precondition: decl = `default ...`.
#define BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_REPLACE_DEFAULT_PARSE_D( \
        d, decl_traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_TRAITS_POP_BACK(BOOST_PP_TUPLE_ELEM(2, 1, \
                    decl_traits)), \
            BOOST_CONTRACT_EXT_PP_PARENTHESIZE( \
                BOOST_CONTRACT_EXT_PP_KEYWORD_DEFAULT_REMOVE_FRONT( \
                    BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) \
                ) \
            ) \
            BOOST_PP_EMPTY \
        ) \
    )

#endif // #include guard

