
#ifndef BOOST_CONTRACT_EXPT_PP_TRAITS_PARSE_HPP_
#define BOOST_CONTRACT_EXPT_PP_TRAITS_PARSE_HPP_

#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// This API is typically not used by users. It is provided here in case users
// want to implement their own signature parsing using the ..._PARSE macros
// directly, instead of using the already provided function and class parsing.

// PUBLIC //

// Initialize a parsing data structure `sign_traits` from specified signature.
#define BOOST_CONTRACT_EXT_PP_TRAITS_PARSE_INIT(sign) \
    ( sign, BOOST_PP_EMPTY() )

// Expand to signature tokens remaining to be parsed.
#define BOOST_CONTRACT_EXT_PP_TRAITS_PARSE_REST(sign_traits) \
    BOOST_PP_TUPLE_ELEM(2, 0, sign_traits)

// Expand to traits parsed so far from signature.
#define BOOST_CONTRACT_EXT_PP_TRAITS_PARSE_DONE(sign_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, sign_traits)

#endif // #include guard

