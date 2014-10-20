
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run the related generation script "generate.py".

#include <boost/contract/ext_/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

// PRIVATE //

// NOTE: These are not local macros, do NOT #undefine them ('x' used to avoid
// concatenating to reserved symbols).
// The following macro must expand to a unary token (e.g., `(1)`).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_ISxswitch (1)
#define switchxBOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_IS (1)
// The following macro must expand to nothing.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_REMOVExswitch
#define switchxBOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_REMOVE

// PUBLIC //

#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_SWITCH_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_ISx)

#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_SWITCH_BACK(token) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_BACK(token, \
            xBOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_IS)

// Precondition: tokens start with keyword to remove (see `..._IS_SWITCH_FRONT`).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_REMOVE_FRONT(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_REMOVEx, tokens)

// Precondition: token ends with keyword to remove (see `..._IS_SWITCH_BACK`).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_REMOVE_BACK(token) \
    BOOST_PP_CAT(token, xBOOST_CONTRACT_EXT_PP_KEYWORD_SWITCH_REMOVE)

#endif // #include guard

