
#ifndef BOOST_CONTRACT_EXT_PP_EXPAND_HPP_
#define BOOST_CONTRACT_EXT_PP_EXPAND_HPP_

/* PUBLIC */

// Expand its argument once, `BOOST_PP_EXPAND` expands twice instead:
//  EXPAND1(x) --> x                   (x expanded once)
//  EXPAND(x)  --> EXPAND_(x) --> x    (x expanded twice)
// NOTE: This macro is sometimes useful to enforce proper macro expansion on
// MSVC (on better preprocessors like GCC, CLang, and Wave this macro is not
// necessary instead). For example, `EXPAND1(macro args) ...` where `args` is
// `(a, b EMPTY)` expands to `macro(a, b EMPTY) ...`, otherwise MSVc would
// sometimes confuse `...` as arguments for `EMPTY`.
#define BOOST_CONTRACT_EXT_PP_EXPAND1(tokens) tokens

#endif // #include gaurd

