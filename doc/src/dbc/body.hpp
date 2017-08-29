/**
 * @file
 * Header file to only include facilities to split body definition from
 * contract declaration.
 */

/**
 * This macro expands to the body function name, it is used to separate the
 * body implementation from its contract specification.
 * This library requires contracts to be listed together with the class
 * declaration as they are part of the code specification (as proposed in
 * [@ref Ott04]). Specifically, class invariants are listed with the class
 * declaration, preconditions and postconditions are listed with the
 * constructor, destructor, and member function declaration. The function body 
 * instead is part of the implementation and it can be defined either together
 * with the contract declaration or separately (this is to maintain the C++
 * ability to separate a function definition from its declaration).
 * 
 * If you want to separate declaration and definition, you can specify @c ; as
 * the function body in the contract declaration (as you would normally do in
 * C++) and then define the body separately wrapping the function name with
 * this macro.
 * 
 * For example, in @ref A_Complete_Example all bodies are defined together with 
 * their declarations. That example can be reworked as follow to separate body
 * definitions from their declarations:
 * @code
 *  #include <dbc.hpp>
 *  
 *  // Specification (could be in a header file .hpp).
 *  
 *  class str DBC_INHERIT_OBJECT(str) { // Class declaration.
 *  public:
 *      // Member function declaration (signature and contract specification).
 *      size_t size() const
 *      DBC_MEM_FUN( (public) (size_t) (str) (size)() (const), {
 *          ... // Preconditions here (keep it simple).
 *      }, {
 *          ... // Postconditions here (keep it simple).
 *      }, ;) // ';' indicates body not defined here. 
 *  
 *  private:
 *      size_t size_;
 *      ...
 *  };
 *  
 *  ...
 *  
 *  // Implementation (could be in a separate code file .cpp).
 *  
 *  // Member function definition (body implementation).    
 *  size_t std::DBC_BODY(size)() const {
 *      // Body definition here.
 *      return size_;
 *  }
 * @endcode
 * <small>
 *
 * @note In C++ a function is @e declared when its signature is specified, and
 *  it is @e defined when its implementation is given (see [@ref Str97]). A
 *  common reason for separating a function definition from its declaration is
 *  to avoid recompiling the function implementation every time. That is
 *  usually achieved by listing the declaration in an header file 
 *  (<c>.hpp</c>) and the definition in a separate code file (<c>.cpp</c>),
 *  then the code file is compiled only if the function implementation
 *  changes. For example, the header file @c "add.hpp" would contain the 
 *  specification:
 *  @code
 *      // File: "add.hpp".
 *      
 *      int add(const int& a, const int& b); // Declaration (specification).
 *  @endcode
 *  While the code file @c "add.cpp" would contain the implementation:
 *  @code
 *      // File: "add.cpp".
 * 
 *      #include "add.hpp"
 * 
 *      int add(const int& a, const int& b) { // Definition (implementation).
 *          return a + b;
 *      }
 *  @endcode
 *  Programs would include the header file and be linked with the object file
 *  separately compiled from the code file.
 *
 * </small>
 * @param[in] function_name The function name.
 * @return If preconditions, postconditions, or invariants are checked
 *  (@c DBC_CHECK_REQUIRE_, @c DBC_CHECK_ENSURE, or @c DBC_CHECK_INVARIANT
 *  symbols are defined at compile-time), this macro expands to a special
 *  name for the body function (the actual name is implementation specific).
 *  Otherwise, this macro simply expands to the specified function name.
 * @see Operators and destructors require the special macros
 *  @c DBC_OPERATOR_BODY() and @c DBC_DESTRUCTOR_BODY() because their names
 *  contain special symbols.
 * @see Constructor require the use of the special @c init() function because
 *  of member initializers as discussed in @c DBC_CONSTRUCTOR().
 */
#define DBC_BODY(function_name)

/**
 * This macro expands to the operator body function name, it is used to
 * separate the body implementation from its contract specification for
 * operators.
 * Functionally this macro is equivalent to @c DBC_BODY() (see related 
 * documentation) but it handles the special operator symbols (@c ==,
 * @c <, etc) which cannot be treated as the regular function names that only
 * contain letters and numbers.
 * 
 * For example, reworking the @ref A_Complete_Example to separate body
 * definitions from their implementations:
 * @code
 *  #include <dbc.hpp>
 *  
 *  class str DBC_INHERIT_OBJECT(str) {
 *  public:
 *      char& operator[](const size_t& index) // Declaration.
 *      DBC_MEM_FUN( (public) (char&) DBC_COPYABLE(str)
 *              (operator_at)( (const size_t&)(index) ), {
 *          ... // Member function preconditions.
 *      }, {
 *          ... // Member function postconditions.
 *      }, ;) // ';' indicates body not defined here.
 *  
 *  private:
 *      char* chars_;
 *      ...
 *  };
 *  
 *  // Definition (must use same 'operator_at' name as in contract declaration).
 *  char& str::DBC_OPERATOR_BODY(operator[], operator_at)(const size_t& index) {
 *      // Body definition here.
 *      return chars_[index];
 *  }
 * @endcode
 * @param[in] operator_symbol The operator name with symbols
 *  (e.g., @c operator == , @c operator<, etc).
 * @param[in] operator_name The operator name without symbols. This name is
 *  arbitrary but it must match the one specified in the contract declaration
 *  and it is recommended to still use the @c operator word as prefix (e.g., 
 *  @c operator_equal, @c operator_less, etc).
 * @return If preconditions, postconditions, or invariants are checked
 *  (@c DBC_CHECK_REQUIRE_, @c DBC_CHECK_ENSURE, or @c DBC_CHECK_INVARIANT
 *  symbols are defined at compile-time), this macro expands to a special name
 *  for the specified operator body function @a operator_name (the actual name
 *  is implementation specific). Otherwise, this macro expands to the specified
 *  @a operator_symbol.
 * @see @c DBC_BODY() for more information.
 */
#define DBC_OPERATOR_BODY(operator_symbol, operator_name)

/**
 * This macro expands to the destructor body function name, it is used to
 * separate the body implementation from its contract specification for
 * destructors.
 * Functionally this macro is equivalent to @c DBC_BODY() (see related 
 * documentation) but it handles the special destructor name that is inferred
 * from the class name.
 * 
 * For example, reworking the @ref A_Complete_Example to separate body
 * definitions from their implementations:
 * @code
 *  #include <dbc.hpp>
 *  
 *  class str DBC_INHERIT_OBJECT(str) {
 *  public:
 *      virtual ~str() // Declaration.
 *      DBC_DESTRUCTOR( (public) (virtual) (str)(), ;)  // ';' for body defined
 *                                                      // later.
 *  
 *  private:
 *      char* chars_;
 *      ...
 *  };
 *  
 *  char& str::DBC_DESTRUCTOR_BODY(str)() { // Definition.
 *      // Body definition here.
 *      delete[] chars_;
 *  }
 * @endcode
 * @param[in] class_name The class name (the plain type name, no namespace
 *  prefix, no template parameters, etc).
 * @return If preconditions, postconditions, or invariants are checked
 *  (@c DBC_CHECK_REQUIRE_, @c DBC_CHECK_ENSURE, or @c DBC_CHECK_INVARIANT
 *  symbols are defined at compile-time), this macro expands to a special name
 *  for the destructor body function (the actual name is implementation 
 *  specific). Otherwise, this macro expands to the destructor name
 *  <c>~class_name</c>.
 * @see @c DBC_BODY() for more information.
 */
#define DBC_DESTRUCTOR_BODY(class_name)

