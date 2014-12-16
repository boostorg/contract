
#ifndef BOOST_CONTRACT_EXT_PP_PAREN_FRONT_HPP_
#define BOOST_CONTRACT_EXT_PP_PAREN_FRONT_HPP_

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_PAREN_FRONT_SPLIT_(...) (__VA_ARGS__) ,

#define BOOST_CONTRACT_EXT_PP_PAREN_FRONT_PAIR_FIRST_(first, second) first

// NOTE: Using `BOOST_PP_TUPLE_ELEM(2, 0, pair)` confuses MSVC here. 
#define BOOST_CONTRACT_EXT_PP_PAREN_FRONT_OO_(pair) \
    BOOST_CONTRACT_EXT_PP_PAREN_FRONT_PAIR_FIRST_ pair

/* PUBLIC */

// Precondition: tokens == `(...[, ...]*) ...[, ...]*`.
// Expand to `(...[, ...]*)` in front above (discarding any trailing tokens).
// NOTE: To get the trailing `...[, ...]*` use `BOOST_PP_TUPLE_EAT(0) tokens`.
#define BOOST_CONTRACT_EXT_PP_PAREN_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_PAREN_FRONT_OO_(( \
            BOOST_CONTRACT_EXT_PP_PAREN_FRONT_SPLIT_ tokens))

#endif // #include guard

