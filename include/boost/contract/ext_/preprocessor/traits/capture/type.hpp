
#ifndef BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_HPP_
#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/capture_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PUBLIC */

// Expand to `(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_AUX_TYPE_INDEX, traits)()


// Precondition: decl = `[wrapped-type] ...`.
#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_PARSE_D(d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE_D(d, \
                BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

/* PRIVATE */

// EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_(decl_type, traits) \
    BOOST_PP_IIF(BOOST_PP_EXPAND(BOOST_CONTRACT_EXT_PP_IS_EMPTY \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
        BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_NO_ \
    , \
        BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_YES_ \
    )(decl_type, traits)

#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_YES_(decl_type, traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_type), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type) BOOST_PP_EMPTY) \
    )

#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_NO_(decl_type, traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_type), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY) \
    )

#endif // #include guard

