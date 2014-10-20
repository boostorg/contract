
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_EXPLICIT_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_EXPLICIT_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run the related generation script "generate.py".

#include <boost/contract/ext_/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

// PRIVATE //

// NOTE: These are not local macros, do NOT #undefine them ('x' used to avoid
// concatenating to reserved symbols).
// The following macro must expand to a unary token (e.g., `(1)`).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_EXPLICIT_ISxexplicit (1)
#define explicitxBOOST_CONTRACT_EXT_PP_KEYWORD_EXPLICIT_IS (1)
// The following macro must expand to nothing.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_EXPLICIT_REMOVExexplicit
#define explicitxBOOST_CONTRACT_EXT_PP_KEYWORD_EXPLICIT_REMOVE

// PUBLIC //

#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_EXPLICIT_FRONT(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_EXPLICIT_ISx)

#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_EXPLICIT_BACK(token) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_BACK(token, \
            xBOOST_CONTRACT_EXT_PP_KEYWORD_EXPLICIT_IS)

// Precondition: tokens start with keyword to remove (see `..._IS_EXPLICIT_FRONT`).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_EXPLICIT_REMOVE_FRONT(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_EXT_PP_KEYWORD_EXPLICIT_REMOVEx, tokens)

// Precondition: token ends with keyword to remove (see `..._IS_EXPLICIT_BACK`).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_EXPLICIT_REMOVE_BACK(token) \
    BOOST_PP_CAT(token, xBOOST_CONTRACT_EXT_PP_KEYWORD_EXPLICIT_REMOVE)

#endif // #include guard

