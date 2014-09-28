
#ifndef BOOST_CONTRACT_EXT_PP_PAREN_EAT_HPP_
#define BOOST_CONTRACT_EXT_PP_PAREN_EAT_HPP_

// PRIVATE //

// IMPLEMENTATION: Must expand to nothing (so to "eat" the first paren).
#define BOOST_CONTRACT_EXT_PP_PAREN_EAT_(...)

// PUBLIC //

// Precondition: tokens == `(...[, ...]*) ...[, ...]*`.
// Expand to trailing ...[, ...]* above, "eating" parenthesized tokens in front.
#define BOOST_CONTRACT_EXT_PP_PAREN_EAT(tokens) \
    BOOST_CONTRACT_EXT_PP_PAREN_EAT_ tokens

#endif // #include guard

