
#ifndef BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/capture/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/capture/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>

/* PUBLIC */

// Precondition: decl = `[wrapped-type] name`.
#define BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_PARSE_D_L(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE_PARSE_D(d, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    ))))

#endif // #include guard

