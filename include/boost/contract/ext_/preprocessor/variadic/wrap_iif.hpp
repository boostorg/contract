
#ifndef BOOST_CONTRACT_EXT_PP_VARIADIC_WRAP_IIF_HPP_
#define BOOST_CONTRACT_EXT_PP_VARIADIC_WRAP_IIF_HPP_

#include <boost/preprocessor/control/expr_iif.hpp>

/* PUBLIC */

// Expand to `prefix ,,, postfix` if bit is 1, or to `,,,` if bit is 0 (where
// `prefix`, `,,,`, and `postfix` can all be EMTPY()).
#define BOOST_CONTRACT_EXT_PP_VARIADIC_WRAP_IIF(bit, prefix, postfix, ...) \
    BOOST_PP_TUPLE_REM_CTOR(BOOST_PP_IIF(bit, \
            (prefix __VA_ARGS__ postfix), (__VA_ARGS__)))

#endif // #include guard

