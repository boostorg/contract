
#ifndef BOOST_CONTRACT_EXT_PP_PAREN_FIRST_HPP_
#define BOOST_CONTRACT_EXT_PP_PAREN_FIRST_HPP_

#include <boost/preprocessor/tuple/elem.hpp>

// PRIVATE //

#define BOOST_CONTRACT_EXT_PP_PAREN_FIRST_SPLIT_(...) (__VA_ARGS__) ,

// PUBLIC //

// Precondition: tokens == `(...[, ...]*) ...[, ...]*`.
// Expand to `(...[, ...]*)` in front above (discarding any trailing tokens).
#define BOOST_CONTRACT_EXT_PP_PAREN_FIRST(tokens) \
    BOOST_PP_TUPLE_ELEM(2, 0, \
            ( BOOST_CONTRACT_EXT_PP_PAREN_FIRST_SPLIT_ tokens ))

#endif // #include guard

