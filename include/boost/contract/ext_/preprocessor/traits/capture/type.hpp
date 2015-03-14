
#ifndef BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_HPP_
#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/index/capture.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PUBLIC */

// Expand to `(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CAPTURE_TYPE, traits)()


// Precondition: decl = `[wrapped-type] ...`.
// Implementation: Trailing EMPTY already added by AUX_TYPE_PARSE.
#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_PARSE_D(d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE_D(d, \
                BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#endif // #include guard

