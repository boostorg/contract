
#ifndef BOOST_CONTRACT_AUX_CONFIG_HPP_
#define BOOST_CONTRACT_AUX_CONFIG_HPP_

// Disable lib's implementation assertions to check against internal errors.
// #define BOOST_CONTRACT_AUX_CONFIG_NDEBUG

// IMPORTANT: Cannot use '_' infix to prevent forming reserved C++ names
// (containing "__" if user `name` starts/ends with '_' already) so using 'X'.
#ifndef BOOST_CONTRACT_AUX_CONFIG_NAME_PREFIX
#   define BOOST_CONTRACT_AUX_CONFIG_NAME_PREFIX boost_contract_auxX
#endif

#endif // #include guard

