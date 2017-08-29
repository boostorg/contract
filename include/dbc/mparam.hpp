/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_MPARAM_HPP_
#define DBC_MPARAM_HPP_

#include "detail/pp/defines.hpp" // Must be 1st include.

#if defined DBC_DOC

// Doxygen does not deal w/ Boost.Preprocessor well... using a simpler macro
// implementation that just selects the type (1st token). However, I am not 
// sure if this will work well in all contexes Doxygen will expand this macro.
#define DBC_MPARAM(count, tokens) DBC_MPARAM_GET_1ST_ tokens

#define DBC_MPARAM_GET_1ST_(first, rest) first

#elif !defined DBC

#undef DBC_MPARAM

#else // DBC

#include "detail/pp/mparam.hpp"

/** 
 * Concatenate specified tokens into a single macro parameter.
 * This is usefull to pass templates and code that contain "," to the 
 * preprocessor. If a token containing a "," is passed to the preprocessor, it
 * will be interpreted as two separate tokens unless wrapped by this macro.
 * If the macro parameter you are passing will be used by the called macro as a
 * value then just wrapping it with extra parenthesis () will work and this 
 * macro is not needed. However, the extra parenthersis will not work if the
 * parameter is used as a type in which case you need to use this macro. It is
 * safe to always use this macro for any sort of macro parameter (value, type, 
 * code, etc).
 * @code
 *  // Note the *required* extra parenthesis around map<>.
 *  class ii DBC_INHERIT_OBJECT(DBC_MPARAM(2, (std::map<int, int>))) { ... }
 * @endcode
 * @param[in] count Number of tokens {0, 1, ..., n}. If coutn is 0, this macro
 *  expans to nothing. If count is 1 this macro works but since you only have
 *  one token you can just pass it as macro parameter without using this macro.
 *  For count greater or equal than 1, this macro is necessary.
 * @param[in] tokens Tokens to concatenate into a simple macro parameter. 
 *  Tokens must be passed as a Boost.Preprocessor tuple of size equal to count
 *  "(token0, token1, ..., token_count-1)". This simply means that you have to 
 *  wrap your comma seperated token expression with an extra pair of 
 *  parenthesis () as shown in the example above.
 * @return Concatenated tokens (token0, token1, ..., token_count-1).
 */
#define DBC_MPARAM(count, tokens) DBC_PP_MPARAM_(count, tokens)

#endif // DBC

#endif // DBC_MPARAM_HPP_

