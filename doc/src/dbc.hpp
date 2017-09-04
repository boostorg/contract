/**
 * @file
 * Header file to include the entire Design By Contract for C++ library.
 * This is the only file you need to include to use this library. It is
 * recommended to simply include this file instead of the separate header files
 * under the @c "dbc/" directory. (All files under the @c "dbc/detail/"
 * directory are implementation specific and must never be included directly.)
 * @code
 *  #include <dbc.hpp> // Simply include this one file.
 * 
 *  ... // Use the library.
 * @endcode
 */

#include "dbc/config.hpp"
#include "dbc/exception.hpp"
#include "dbc/assertion.hpp"
#include "dbc/body.hpp"
#include "dbc/post.hpp"
#include "dbc/mparam.hpp"
#include "dbc/object.hpp"
#include "dbc/invariant.hpp"
#include "dbc/fun.hpp"
#include "dbc/mfun.hpp"

/**
 * Namespace containing the library symbols.
 * This library symbols ending with an underscore @c _ are implementation 
 * specific and must not be used directly.
 * This library macros are prefixed by @c DBC_.
 * This library symbols declared outside the @c dbc:: namespace are prefixed
 * by @c dbc_ and postfixed by @c _ as they are all implementation specific.
*/
namespace dbc {}

