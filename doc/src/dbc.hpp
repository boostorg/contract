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
 *
 * The @cref{DBC_NO}, @cref{DBC_CHECK_REQUIRE}, @cref{DBC_CHECK_ENSURE},
 * @cref{DBC_CHECK_INVARIANT}, and @cref{DBC_ALL} macro symbols any their
 * combinations can be used to selectively compile and check the relative
 * contract components.
 *
 * <small>
 * @note These macro symbols can be defined/undefined either from within the
 *  source code using the <c>\#define</c>/<c>\#undef</c> directives before the
 *  @e first <c>\#include <dbc.hpp></c> or, more conveniently, from the
 *  compiler command line options (use <c>-D</c>/<c>-U</c> for @c g++).
 *
 * </small>
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
 * Namespace containing the Design By Contract for C++ library symbols.
 * The library symbols ending with an underscore @c _ are implementation 
 * specific and must not be used directly.
 * The library macros are prefixed by @c DBC_.
 * The library symbols declared outside the @c dbc:: namespace are prefixed
 * by @c dbc_ and always postfixed by @c _ as they are all implementation
 * specific and should not be used directly.
*/
namespace dbc {

/**
 * If defined by the user, no contract will be compiled and checked
 * (defined by default).
 * If this is defined, overrides eventual user definition of
 * @cref{DBC_CHECK_REQUIRE}, @cref{DBC_CHECK_ENSURE},
 * @cref{DBC_CHECK_INVARIANT}, and @cref{DBC_ALL} cannot be defined at the same
 * time.
 */
#define DBC_NO

/**
 * If defined by the user, preconditions will be compiled and checked
 * (undefined by default).
 * If this is defined, @cref{DBC_NO} cannot be defined by the user.
 */
#define DBC_CHECK_REQUIRE

/**
 * If defined by the user, postconditions will be compiled and checked
 * (undefined by default).
 * If this is defined, @cref{DBC_NO} cannot be defined by the user.
 */
#define DBC_CHECK_ENSURE

/**
 * If defined by the user, invariants will be compiled and checked
 * (undefined by default).
 * If this is defined, @cref{DBC_NO} cannot be defined by the user.
 */
#define DBC_CHECK_INVARIANT

/**
 * If defined by the user, preconditions, postconditions, and invariants will
 * be compiled and checked (undefined by default).
 * If this is defined, overrides eventual user definition of
 * @cref{DBC_CHECK_REQUIRE}, @cref{DBC_CHECK_ENSURE},
 * @cref{DBC_CHECK_INVARIANT}, and @cref{DBC_NO} cannot be defined at the same
 * time.
 */
#define DBC_ALL

} // namespace dbc


