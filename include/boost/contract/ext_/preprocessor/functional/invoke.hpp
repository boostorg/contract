
#ifndef BOOST_CONTRACT_EXT_PP_INVOKE_HPP_
#define BOOST_CONTRACT_EXT_PP_INVOKE_HPP_

// This is sometimes useful first associate a macro with its arguments (in a
// tuple `(macro, arg1, arg2, ...)`) but then lazily invoke the macro onto its
// arguments only at some later point.

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_INVOKE1(macro, _1) macro(_1)

#define BOOST_CONTRACT_EXT_PP_INVOKE2(macro, _1, _2) macro(_1, _2)

#define BOOST_CONTRACT_EXT_PP_INVOKE3(macro, _1, _2, _3) macro(_1, _2, _3)

#define BOOST_CONTRACT_EXT_PP_INVOKE4(macro, _1, _2, _3, _4) macro(_1, _2, _3, _4)

#define BOOST_CONTRACT_EXT_PP_INVOKE5(macro, _1, _2, _3, _4, _5) macro(_1, _2, _3, _4, _5)

// Add more arity here as needed.

#endif // #include guard

