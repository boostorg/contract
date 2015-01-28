
#ifndef BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_HPP_
#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_HPP_

// TODO: Fix all #include for all files.
#include <boost/contract/ext_/preprocessor/traits/capture/aux_/index.hpp>

/* PRIVATE */

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

#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_(decl_type, traits) \
    BOOST_PP_IIF(BOOST_PP_EXPAND(BOOST_CONTRACT_EXT_PP_IS_EMPTY \
            BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \
        BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_NO_ \
    , \
        BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_YES_ \
    )(decl_type, traits)

// Precondition: decl = `[wrapped-type] ...`.
#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_PARSE_ARGS_(d, decl, traits) \
    BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_( \
            BOOST_CONTRACT_EXT_PP_TRAITS_TYPE_PARSE_D(d, decl), traits)
    
/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_PARSE_D(d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_PARSE_ARGS_(d, \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Expand to `(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_AUX_TYPE_INDEX, traits)()

#endif // #include guard

