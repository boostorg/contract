
#ifndef BOOST_CONTRACT_EXT_PP_IDEM_HPP_
#define BOOST_CONTRACT_EXT_PP_IDEM_HPP_

/* PUBLIC */

// NOTE:
//  *   In theory this macro is equivalent to `EXPAND_ONCE(tokens)` but these
//      are logically different plus not using both macros confuses MSVC
//      sometimes.
//  *   In theory this macro is also equivalent to `BOOST_PP_REM(1) (tokens)`
//      but again that confuses MSVC sometimes.
#define BOOST_CONTRACT_EXT_PP_IDEM(tokens) tokens

#endif // #include guard

