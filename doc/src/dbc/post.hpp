/**
 * @file
 * Header file to only include facilities to support "old" postfix in
 * postconditions.
 */

namespace dbc {

/**
 * This macro marks the specified type copyable so its value before the body
 * execution is available in postconditions via the @c .old postfix.
 * This macro should only be used with the @a signature argument of the
 * @c DBC_CONSTRUCTOR(), @c DBC_DESTRUCTOR(), and @c DBC_MEM_FUN() contract
 * macro API. When the contract code API @c fun::constr, @c fun::destr, and
 * @c fun::mem are used, @c dbc::copyable is used instead of this macro.
 * 
 * For example (from @ref A_Complete_Example):
 * @code
 *  #include <dbc.hpp>
 *  
 *  class str DBC_INHERIT_OBJECT(str) {
 *  public:
 *      // Must have copy constructor.
 *  
 *      char& operator[](const size_t& index)
 *      DBC_MEM_FUN( (public) (char&) DBC_COPYABLE(str) // Copyable class type.
 *              (operator_at)( (const size_t&)(index) ), {
 *          DBC_ASSERT(index >= 0 && index < self.size(), "index in range");
 *      }, {
 *          // Not a const mem fun, use 'self.old' for object before body.
 *          DBC_ASSERT(result == self.old.chars_[index.now],
 *                  "returning char at index");
 *      }, {
 *          return chars_[index];
 *      })
 *  
 *  private:
 *      char* chars_;
 *  };
 * @endcode
 * 
 * @warning A type should be declared copyable only and only if the value of the
 *  related variable before the body execution is <b>strictly needed</b> to
 *  assert postconditions. This is because of the followings:
 *  -#  A copyable type @e must have a copy constructor otherwise the code
 *      will not compile. If you are writing a template and declare one of the
 *      template parameters copyable, be aware that you are adding the extra
 *      requirement that the template parameter must have a copy constructor
 *      (and you might be doing so just to specify the contract while your 
 *      template implementation would not require the copy constructor for that
 *      type).
 *  -#  This library internally uses the type's copy constructor to copy the 
 *      type's value before the body is executed. This obviously has an impact 
 *      on performance.
 *  -#  The copied value provided by the library via the <c>.old</c> in 
 *      postconditions is only as good as the copy performed by the user 
 *      defined copy constructor for the type. For example, if the copy 
 *      constructor has a bug or it performs a shallow copy where a deep copy
 *      is semantically needed, the value returned by <c>.old</c>
 *      might violate one or more assertions in the postconditions not because
 *      of an issue in the function body but because of a problem in the copy 
 *      constructor.
 *  
 *  For example, there is no need to declare copyable the type of a constant
 *  argument (the argument cannot be modified by the body because it is 
 *  declared constant). Similarly, there is no need to declare copyable the 
 *  class type for a constant member function (the object cannot be modified by
 *  the body because the function is declared constant).
 *  @code
 *      template<typename T>
 *      class C {
 *      public:
 *          // No need to declare C or "const T&" copyable as const fun and arg.
 *          T f(const T& x) const
 *          DBC_MEM_FUN( (public) (T) (template)(C) (f)( (const T&)(x) ) 
 *                  (const), {
 *              ... // Preconditions.
 *          }, {
 *              // self.old is same as self.now because this is a const member
 *              // function. Then use self.now and don't declare C copyable.
 *              // x.old is same as x.now because the argument is a const&.
 *              // Then use self.now and don't declare "const T&" copyable.
 *              ... // Postconditions.
 *          }, {
 *              ... // Body.
 *          })
 *          
 *          // Declaring the types copyable as done below is not needed, has a 
 *          // performance impact, and requires C and T to have copy
 *          // constructors.
 *          //  T f(const T& x) const
 *          //  DBC_MEM_FUN( (public) (T) (template)DBC_COPYABLE(C)
 *          //          (f)( DBC_COPYABLE(const T&)(x) ) (const), ...)
 *      };
 *  @endcode
 * @param[in] type The type that must be specified copyable. This type must have
 *  a copy costructor, otherwise the library will generate compile-time errors.
 * @return Mark the specified type copyable within the @a signature argument of
 *  contract macro API @c DBC_CONSTRUCTOR(), @c DBC_DESTRUCTOR(), 
 *  and @c DBC_MEM_FUN().
 * @see @c dbc::copyable for same functionality for contract code API.
 */
#define DBC_COPYABLE(type)

/**
 * Indicate the specified type is copyable to support the "old" postfix in
 * postconditions.
 * This should only be used with the library code-based API. Use
 * @c DBC_COPYABLE() with the macro-based API instead.
 * @tparam T Type specified as copyable. The library compilation will require
 *  this type to have copy constructor. Specify a type copyable only if its 
 *  value before body execution is needed in postcondition to avoid the extra
 *  requirement of the existence of the copy constructor and the performance
 *  impact of the copy operation to support the "old" postfix in
 *  postconditions.
 */
template<typename T> class copyable {};

/**
 * Postcondition argument types to support the "old" postfix.
 * This should only be used with the library code-based API.
 * @tparam T Postcondition argument type.
 *  For non-copyable types, this class does not provide the @a old member
 *  variable, no copy is performed, and the "old" postfix is not available in
 *  postconditions.
 */
template<typename T> class post {
public:
    /** Current argument value. */
    const remove_const_ref_<T>& now;
};

/**
 * Postcondition argument pointer types to support the "old" postfix.
 * This should only be used with the library code-based API.
 * @tparam T Postcondition argument pointer type.
 *  For non-copyable types, this class does not provide the @a old member
 *  variable, no copy is performed, and the "old" postfix is not available in
 *  postconditions.
 */
template<typename T> class post<T*> {
public:
    /** Current argument value. */
    const remove_const_ref_<T>* now;
};

/**
 * Postcondition argument types to support the "old" postfix.
 * This should only be used with the library code-based API.
 * @tparam T Postcondition argument type.
 *  For copyable types, this class provides the @a old member variable, a copy 
 *  is performed before body execution, and the "old" postfix is available in
 *  postconditions.
 */
template<typename T> class post<copyable<T> > {
public:
    /** Current argument value. */
    const remove_const_ref_<T>& now;
    
    /** Argument value copied before body execution. */
    const remove_const_ref_<T> old;
};

/**
 * Postcondition argument pointer types to support the "old" postfix.
 * This should only be used with the library code-based API.
 * @tparam T Postcondition argument pointer type.
 *  For copyable types, this class provides the @a old member variable, a copy 
 *  is performed before body execution, and the "old" postfix is available in
 *  postconditions.
 */
template<typename T> class post<copyable<T*> > {
public:
    /** Current argument value. */
    const remove_const_ref_<T>* now;

    /** Argument value copied before body execution. */
    const remove_const_ref_<T>* old;
};

} // namespace dbc

