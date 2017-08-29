/**
 * @file
 * Header file to include only the base object.
 */

namespace dbc {

/**
 * This macro must follow the class type name and it privately derives the
 * class from @c dbc::object.
 * Any class with a contract specified by this library must inherit from @c 
 * dbc::object. The inheritance should be private so not to alter the public
 * inheritance tree (part of the requirement for this library not to alter the
 * class public API).
 * 
 * @note This macro is simply used for convenience so the programmer does not 
 *  have to manually write the private inheritance from @c dbc::object with the
 *  <c>\#ifdef DBC</c> guard.
 * 
 * For example (from @ref A_Complete_Example):
 * @code
 *  #include <dbc.hpp>
 *  
 *  class str DBC_INHERIT_OBJECT(str) { // Recommended form.
 *      ...
 *  };
 *  @endcode
 *  which is essentially equivalent to:
 * @code
 *  #include <dbc.hpp>
 *  
 *  class str // Equivalent code form (not recommended).
 *  #ifdef DBC // When one or more DBC_CHECK_... defined.
 *          : private dbc::object<str> // Privately inherit from dbc::object.
 *  #endif // DBC
 *          {
 *      ...
 *  };
 * @endcode
 * The equivalent code form is less readable and requires the programmer to 
 * write more code increasing the opportunity for error. Therefore, it is 
 * recommended to use @c DBC_INHERIT_OBJECT() instead.
 * @param[in] class_type The class type. For templates, the template parameters
 *  need to be specified.
 * @return If preconditions, postconditions, or invariants are checked
 *  (@c DBC_CHECK_REQUIRE_, @c DBC_CHECK_ENSURE, or @c DBC_CHECK_INVARIANT
 *  symbols are defined at compile-time), this macro expands to code that 
 *  privately derives the specified class type from @c dbc::object.
 *  Otherwise,
 *  this macro expands to nothing.
 * @see Use @c DBC_MULTI_INHERIT_OBJECT() if the class inherits also from other
 *  classes.
 * @see Use @c DBC_MPARAM() if @a class_type is a template with more than one
 *  parameter.
 */
#define DBC_INHERIT_OBJECT(class_type)

/**
 * This macro must follow the last base class type name and if privately
 * derives the class from @c dbc::object when multiple inheritance is used.
 * 
 * This macro is similar to @c DBC_INHERIT_OBJECT() (see related documentation).
 * It is used when the class type also inherits from other classes
 * (<em>multiple inheritance</em>).
 * 
 * @note This macro is simply used for convenience so the programmer does not
 *  have to manually write the private inheritance from @c dbc::object with the
 *  <c>\#ifdef DBC</c> guard.
 * 
 * For example:
 * @code
 *  #include <dbc.hpp>
 *  
 *  class B { ... };
 *  
 *  // Inherits from both B (publically) and dbc::object<C> (privately).
 *  class C: public B DBC_MULTI_INHERIT_OBJECT(C) { // Recommended form.
 *      ...
 *  };
 * @endcode
 * which is essentially equivalent to:
 * @code
 *  #include <dbc.hpp>
 *  
 *  class B { ... };
 *  
 *  class C: public B // Equivalent code form (not recommended).
 *  #ifdef DBC // When one or more DBC_CHECK_... defined.
 *          // Note the use of ',' instead of ':' used by DBC_INHERIT_OBJECT().
 *          , private dbc::objec<C> // Privately inherit from dbc::object.
 *  #endif // DBC
 *          {
 *      ...
 *  };
 * @endcode
 * The equivalent code form is less readable and requires the programmer to
 * write more code increasing the opportunity for error. Therefore, it is
 * recommended to use @c DBC_MULTI_INHERIT_OBJECT() instead.
 * @param[in] class_type The class type. For templates, the template parameters
 *  need to be specified.
 * @return If preconditions, postconditions, or invariants are checked
 *  (@c DBC_CHECK_REQUIRE_, @c DBC_CHECK_ENSURE, or @c DBC_CHECK_INVARIANT
 *  symbols are defined at compile-time), this macro expands to code that 
 *  privately derives the specified class type from @c dbc::object. Otherwise,
 *  this macro expands to nothing.
 * @see Use @c DBC_INHERIT_OBJECT() if the class does not inherit from other 
 *  classes.
 * @see Use @c DBC_MPARAM() if @a class_type is a template with more than one
 *  parameter.
 */
#define DBC_MULTI_INHERIT_OBJECT(class_type)

/**
 * Any class with a contract must privately inherit from this base object
 * class.
 * This class should not be used directly, the @c DBC_INHERIT_OBJECT() and
 * @c DBC_MULTI_INHERIT_OBJECT() should be used instead.
 *
 * Because the inheritance is private, it does not alter the contracted class
 * public API.
 * Because this class class is a template on taking as parameter the contracted
 * class type, there is a different base object for every specified contracted
 * class type so this does not alter the inheritance tree by introducing a
 * common ancestor to all classes.
 * @code
 *  #include <dbc.hpp>
 *
 *  class C
 *  #ifdef DBC
 *          : dbc::object<C>
 *  #endif // DBC
 *          {
 *      ... // Class and its contract here.
 *  };
 * @endcode
 * @tparam C The contracted class that is inheriting from this object.
 * @note This base object is used by the library implementation to store
 *  internal state, etc.
 */
template<class C>
class object {};

} // namespace dbc

