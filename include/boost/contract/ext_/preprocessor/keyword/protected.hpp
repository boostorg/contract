
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run the related generation script "generate.py".

#include <boost/contract/ext_/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

// PRIVATE //

// NOTE: These are not local macros, do NOT #undefine them ('x' used to avoid
// concatenating to reserved symbols).
// The following macro must expand to a unary token (e.g., `(1)`).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_ISxprotected (1)
#define protectedxBOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_IS (1)
// The following macro must expand to nothing.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_REMOVExprotected
#define protectedxBOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_REMOVE

// PUBLIC //

#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PROTECTED_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_ISx)

#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PROTECTED_BACK(token) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_BACK(token, \
            xBOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_IS)

// Precondition: tokens start with keyword to remove (see `..._IS_PROTECTED_FRONT`).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_REMOVE_FRONT(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_REMOVEx, tokens)

// Precondition: token ends with keyword to remove (see `..._IS_PROTECTED_BACK`).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_REMOVE_BACK(token) \
    BOOST_PP_CAT(token, xBOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_REMOVE)

#endif // #include guard

