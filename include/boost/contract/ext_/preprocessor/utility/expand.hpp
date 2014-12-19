
#ifndef BOOST_CONTRACT_EXT_PP_EXPAND_HPP_
#define BOOST_CONTRACT_EXT_PP_EXPAND_HPP_

/* PUBLIC */

// Expand its argument once, `BOOST_PP_EXPAND` expands it twice instead:
//  EXPAND_ONCE(x)  --> x                   (x expanded once)
//  EXPAND(x)       --> EXPAND_(x) --> x    (x expanded twice)
// This macro is sometimes useful to enforce proper macro expansion at least on
// MSVC (on better preprocessors like GCC, CLang, and Wave this macro is not
// necessary instead). For example, `EXPAND_ONCE(macro args) ...` where `args`
// is `(a, b EMPTY)` expands to `macro(a, b EMPTY) ...`. Otherwise, MSVC would
// sometimes confuse `...` as arguments for `EMPTY`, etc.
// NOTE:
//  *   In theory this macro is equivalent to `IDEM(tokens)` but these are
//      logically different, plus not using both macros confuses MSVC sometimes.
//  *   In theory this macro is also equivalent to `BOOST_PP_REM(1) (tokens)`
//      but again that confuses MSVC sometimes.
#define BOOST_CONTRACT_EXT_PP_EXPAND_ONCE(tokens) tokens

#endif // #include gaurd

