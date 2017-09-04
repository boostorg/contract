/**
 * @file
 * Header file to only include facilities to write contracts using the
 * code-based API.
 * The types defined in this file use some template metaprgramming constructs.
 * Metaprogramming constructs are indicated in this documentation with names
 * ending with an underscore @c _. Following this library naming
 * @ref Conventions "conventions", these names are implementation specific,
 * they should not be used directly, and they are not documented here. For
 * example, @c remove_const_ref_<const T&> indicates a metagramming expression
 * that is internally evaluated by this library to @c T (removing both the
 * constant @c const and reference @c & type qualifiers). However,
 * @c remove_const_ref_ is implementation specific (it might not even exist in
 * the actual library implementation), should not be used directly, and it is
 * not documented here.
 */

namespace dbc {

/**
 * This macro expands to the contract class name for code-based API.
 * When using the code-based API, this macro should always be used to name the 
 * class inheriting from @c dbc::fun::constr, @c dbc::fun::destr, or
 * @c dbc::fun::mem used to specify the contract. If a different name is used,
 * the contract specified using the code-based API cannot be subcontracted
 * from the macro-based API.
 * @param[in] function_name The name of the member function for which the
 *  contract is being specified. Use @c init, @c del, and @c operator_... for
 *  constructors, destructor, and operators.
 * @param[in] argument_names A preprocessor sequence specifying the member
 *  function argument names @c (argument_name0)(argument_name1)... .
 * @see @ref Code_Based_API for an example.
 */
#define DBC_CONTRACT(function_name, argument_names)

/**
 * Template used by the code-based API to specify contracts for functions with
 * given return type and (optional) argument types.
 * @tparam R The function return type. Use @c void for void functions.
 * @tparam A0, A1, ... The function argument types (neither one of which can
 *  be @c void). These template parameters are all optional (indicated by their
 *  default @c none_ value), specify:
 *  -   No argument type @c dbc::fun<R> for a function with no argument.
 *  -   Only @a A0 @c dbc::fun<R, A0> for a function with only one argument.
 *  -   @a A0 and @a A1 @c dbc::fun<R, A0, A1> for a function with two 
 *      arguments.
 *  -   And so on. The maximum number of supported arguments is defined by
 *      @cref{DBC_CONFIG_MAX_ARGC}.
 */
template<typename R, typename A0 = none_, typename A1 = none_, ...>
class fun {
public:
    /**
     * Return type without @c const and @c & qualifiers.
     * For example, if @a R is <c>const std::string&</c> then
     * @c basic_result_type is evaluated to @c std::string.
     */
    typedef remove_const_ref_<R> basic_result_type;

    /**
     * Argument type without @c const, @c &, and @c dbc::copyable qualifiers.
     * For example, if @a A0 is <c>dbc::copyable<const std::string&></c> then
     * @c basic_arg0_type is evaluated to @c std::string.
     *
     * These types @c basic_arg0_type, @c basic_arg1_type, ... are defined for
     * each argument number in <c>[0, DBC_CONFIG_MAX_ARGC - 1]</c>.
     */    
    typedef remove_copyable_const_ref_<A0> basic_arg0_type;

    /**
     * Argument type without @c const and @c & qualifiers (but keeps 
     * @c dbc::copyable qualifier if specified).
     * For example, if @a A0 is <c>dbc::copyable<const std::string&></c> then
     * @c copyable_arg0_type is evaluated to @c dbc::copyable<std::string>.
     * 
     * These types @c copyable_arg0_type, @c copyable_arg1_type, ... are
     * defined for every argument number in <c>[0, DBC_CONFIG_MAX_ARGC - 1]</c>.
     */    
    typedef remove_const_ref_<A0> copyable_arg0_type;
    
    /**
     * Argument type without @c dbc::copyable qualifier (but keeps @c const and
     * @c & qualifiers if specified).
     * For example, if @a A0 is <c>dbc::copyable<const std::string>&</c> then
     * @c uncopyable_arg0_type is evaluated to <c>const std::string&</c>.
     * 
     * These types @c uncopyable_arg0_type, @c uncopyable_arg1_type, ... are
     * defined for every argument number in <c>[0, DBC_CONFIG_MAX_ARGC - 1]</c>.
    */    
    typedef remove_copyable_<A0> uncopyable_arg0_type;

    /**
     * Template used by the code-based API to specify contracts for functions
     * members of the given class and eventually subcontracting from the given
     * base contract class.
     * The contracted function must be a member of the class @a C, with return
     * type @a R, argument types @a A0, @a A1, ..., and optionally 
     * subcontracting from the base contract class @a B.
     * @tparam C Class of which the contracted function is member of.
     *  This class type @a C must privately inherit from @c dbc::object<C>
     *  (see @c DBC_INHERIT_OBJECT()) and it must specify invariants
     *  (see @c DBC_INVARIANT()).
     * @tparam B Base contract class from which the contract function is
     *  subcontracting. This must be of a type derived from @c dbc::fun::mem so
     *  to be a valid contract. If the contracted member function is not
     *  subcontracting, this parameter can be left unspecified).
     * @see @ref Code_Based_API for an example.
     */
    template<class C, class B = no_base_>
    class mem {
    public:
        /**
         * Type resulting from this template instantiation.
         * This is needed when writing contracts for functions member of a
         * @e template class type @a C.
         * @code
         *  #include <dbc.hpp>
         *
         *  teamplate<typename T>
         *  class C DBC_MULTI_INHERIT_OBJECT(C<T>) {
         *  public:
         *      T f(const T& x) const
         *  #ifdef DBC
         *      { return DBC_CONTRACT(f, (x))().call(*this, &C::DBC_BODY(f),
         *          x, "f"); }
         *  protected:
         *      class DBC_CONTRACT(f, (x)): public dbc::fun<T, const T&>::
         *              template // Need to explicitly indicate template.
         *              mem<const C>::this_type { // Need instantiated type.
         *          void require(const C& self, const T& x) {
         *              // Preconditions.
         *          }
         *          void ensure(const dbc::post<C>& self,
         *                  const dbc::post<T>& x) {
         *              // Postconditions.
         *          }
         *      };
         *      T DBC_BODY(f)(const T& x) const
         *  #endif // DBC
         *      ; // Body definition split from contract declaration.
         *  public:
         *      
         *      ...
         *  };
         * @endcode
         */
        typedef mem<C, B> this_type;
        
        /**
         * Class type without @c const, @c &, and @c dbc::copyable qualifiers.
         */
        typedef remove_copyable_const_ref_<C> basic_class_type;

        /**
         * Class type without @c const and @c & qualifiers (but keeps eventual
         * @c dbc::copyable qualifier).
         */
        typedef remove_const_ref_<C> copyable_class_type;
        
        /**
         * Class type without @c & and @c dbc::copyable qualifiers (but keeps
         * eventual @c const qualifier).
         */
        typedef remove_copyable_ref_<C> uncopyable_class_type;

        /**
         * Member function pointer type.
         * Note that the eventual @c dbc::copyable qualifier is removed from
         * the function argument and class types as it does not appear in the 
         * actual member function signature. 
         */
        typedef R (uncopyable_class_type::* mem_fun_type)(
                uncopyable_arg1_type, uncopyable_arg1_type, ...);

        /**
         * Check this contract and execute the specified body accordingly to
         * the @ref Member_Function_Call_Semantics
         * "DBC Member Function Call Semantics".
         * @param self A reference to the object (use @c *this from the
         *  contracted member function). The eventual @c const qualifier is 
         *  kept for the class type to properly handle constant member 
         *  functions.
         * @param[in] body A pointer to function implementing the body.
         * @param arg0, arg1, ... The function arguments. The eventual @c const
         *  qualifiers are kept to properly handle constant arguments.
         * @param[in] name The function name (optional, used for log messages).
         * @return The value returned by the body (could be @c void).
         */
        inline virtual R call(uncopyable_class_type& self, mem_fun_type body,
                uncopyable_arg0_type arg0,
                uncopyable_arg0_type arg1,
                ...,
                const std::string& name = "");

    protected:
        /**
         * The user must implement this function specifying the
         * @e preconditions required by the member function contract.
         * If the contract does not require any precondition, simply implement
         * this pure virtual function as @c {}.
         * All these arguments are constant references so the contract cannot 
         * modify the object and argument values by mistake.
         * @param[in] self Constant reference to the object.
         * @param[in] arg0, arg1, ... Constant references to the argument
         *  values (present only if @a A0, @a A1, ... have been specified).
         */
        inline virtual void require(const basic_class_type& self,
                const basic_arg0_type& arg0,
                const basic_arg1_type& arg1, ...) = 0;
                
        /**
         * The user must implement this function specifying the
         * @e postconditions ensured by the member function contract.
         * If the contract does not ensure any postcondition, simply implement
         * this pure virtual function as @c {}.
         * All these arguments are constant references so the contract cannot 
         * modify the object, argument, and returned values by mistake.
         * @param[in] self Constant reference to the object @e post-value.
         *  The post-value allows to access the current object value (after the
         *  body execution) via @c self.now. Furthermore, if the object type
         *  @c C was specified copyable using @c dbc::copyable then also the
         *  old object value (@e before the body execution) can be accessed via
         *  @c self.old (this requires the type to have a copy constructor and 
         *  will impact performances with an extra copy of the object, use it
         *  only when the old value is really needed in postconditions,
         *  see @c DBC_COPYABLE()).
         * @param[in] arg0, arg1, ... Constant references to the argument
         *  post-values (present only if @a A0, @a A1, ... have been
         *  specified). As for @a self, @c arg0.now is used to access the
         *  argument value after body execution and @c arg0.old is used to 
         *  assess the value before body execution if the argument type was
         *  specified @c dbc::copyable (and similarly for the other argument 
         *  numbers).
         * @param[in] result Constant reference to the value being returned
         *  (present only if @a R is not @c void).
         */
        inline virtual void ensure(const post<copyable_class_type>& self,
                const post<copyable_arg0_type>& arg0,
                const post<copyable_arg1_type>& arg1,
                ..., 
                const basic_result_type& result) = 0;
    };

    /**
     * Template used by the code-based API to specify contracts for
     * constructors of the given class.
     * The contracted constructor must be for the class @a C, and argument
     * types @a A0, @a A1, ... .
     *
     * This template is present only if @a R is @c void because constructors
     * do not return a value.
     *
     * There is no base contract parameter @a B as constructor do not
     * subcontract directly (the base class constructor contract is implicitly
     * checked by C++ construction mechanism).
     * @tparam C Class of which the contracted constructor is member of.
     *  This type cannot be specified copyable via @c dbc::copyable because
     *  there is no object before constructor body execution so the "old"
     *  postfix is never available in constructor postconditions.
     *  This class type @a C must privately inherit from @c dbc::object<C>
     *  (see @c DBC_INHERIT_OBJECT()) and it must specify invariants
     *  (see @c DBC_INVARIANT()).
     * @see See dbc::fun::mem for more detailed documentation for member
     *  function contracts.
     * @see @ref Code_Based_API for an example.
     */
    template<class C>
    class constr {
    public:
        /** Type resulting from this template instantiation. */
        typedef constr<C> this_type;
        
        /** Class ype without @c const, @c &, and @c dbc::copyable. */
        typedef remove_copyable_const_ref_<C> basic_class_type;

        /** Class type without @c const and @c & qualifiers. */
        typedef remove_const_ref_<C> copyable_class_type;
        
        /** Class type without @c & and @c dbc::copyable qualifiers. */
        typedef remove_copyable_ref_<C> uncopyable_class_type;

        /** Member function pointer type. */
        typedef void (uncopyable_class_type::* mem_fun_type)(
                uncopyable_arg1_type, uncopyable_arg1_type, ...);

        /**
         * Check this contract and execute the specified body accordingly to
         * the @ref Constructor_Call_Semantics
         * "DBC Constructor Call Semantics".
         * @param self A reference to the object (use @c *this from the
         *  contracted constructor).
         * @param[in] body A pointer to function implementing the body.
         * @param arg0, arg1, ... The function arguments.
         * @param[in] name The function name (optional, used for log messages).
         * @note This call returns @c void because constructors return no
         *  value.
         */
        inline void call(uncopyable_class_type& self, mem_fun_type body,
                uncopyable_arg0_type arg0,
                uncopyable_arg0_type arg1,
                ...,
                const std::string& name = "");
        
    protected:
        /**
         * The user must implement this function specifying the
         * @e preconditions required by the constructor contract.
         * If the contract does not require any precondition, simply implement
         * this pure virtual function as @c {}.
         * All these arguments are constant references so the contract cannot 
         * modify the argument values by mistake.
         * @param[in] arg0, arg1, ... Constant references to the argument
         *  values (present only if @a A0, @a A1, ... have been specified).
         * @note There is no @c self argument as there is no object before
         *  constructor body execution so the preconditions cannot access any
         *  object value.
         */
        inline virtual void require(
                const basic_arg0_type& arg0,
                const basic_arg1_type& arg1, ...) = 0;
                
        /**
         * The user must implement this function specifying the
         * @e postconditions ensured by the constructor contract.
         * If the contract does not ensure any postcondition, simply implement
         * this pure virtual function as @c {}.
         * All these arguments are constant references so the contract cannot 
         * modify the object, and argument values by mistake.
         * @param[in] self Constant reference to the object @e post-value.
         *  This post-value only allows to access the current object value
         *  (after the body execution) via @c self.now because @a C cannot be
         *  specified @c dbc::copyable for constructors.
         * @param[in] arg0, arg1, ... Constant references to the argument
         *  post-values (present only if @a A0, @a A1, ... have been
         *  specified). As for @a self, @c arg0.now is used to access the
         *  argument value after body execution and @c arg0.old is used to 
         *  assess the value before body execution if the argument type was
         *  specified @c dbc::copyable (and similarly for the other argument 
         *  numbers).
         * @note There is no @a result argument because constructors return no
         *  value.
         */
        inline virtual void ensure(const post<copyable_class_type>& self,
                const post<copyable_arg0_type>& arg0,
                const post<copyable_arg1_type>& arg1,
                ...) = 0; 
    };

    /**
     * Template used by the code-based API to specify contracts for
     * the destructor of the given class.
     *
     * This template is present only if @a R is @c void and no argument type
     * @a A0, @a A1, ... is specified because destructors have no return 
     * value and no argument.
     *
     * Destructor contracts have no preconditions or postconditions so this
     * class does not declares the @c require() and @c ensure() pure virtual
     * functions.
     *
     * There is no base contract parameter @a B as destructor do not
     * subcontract directly (the base class destructor contract is implicitly
     * checked by C++ destruction mechanism).
     * @tparam C Class of which the contracted destructor is member of.
     *  This type cannot be specified copyable via @c dbc::copyable because
     *  destructors do not check postconditions.
     *  This class type @a C must privately inherit from @c dbc::object<C>
     *  (see @c DBC_INHERIT_OBJECT()) and it must specify invariants
     *  (see @c DBC_INVARIANT()).
     * @see See dbc::fun::mem for more detailed documentation for member
     *  function contracts.
     * @see @ref Code_Based_API for an example.
     */
    template<class C>
    class destr {
    public:
        /** Type resulting from this template instantiation. */
        typedef destr<C> this_type;
        
        /** Class ype without @c const, @c &, and @c dbc::copyable. */
        typedef remove_copyable_const_ref_<C> basic_class_type;

        /** Class type without @c const and @c & qualifiers. */
        typedef remove_const_ref_<C> copyable_class_type;
        
        /** Class type without @c & and @c dbc::copyable qualifiers. */
        typedef remove_copyable_ref_<C> uncopyable_class_type;

        /** Member function pointer type. */
        typedef void (uncopyable_class_type::* mem_fun_type)();

        /**
         * Check this contract and execute the specified body accordingly to
         * the @ref Destructor_Call_Semantics
         * "DBC Destructor Call Semantics".
         * This call will only throw if the body throws. The body is specified
         * by the user and to comply with C++ STL it should not throw (but it
         * is up to the user to full fill the STL requirement or not).
         * However, if the contract fails during this call, no exception will
         * be thrown and @c dbc::broken_destructor_invariant() will be called
         * instead (or the user's defined handler for this condition, see
         * @c dbc::set_broken_destructor_invariant()). Therefore, this libray
         * comply with C++ STL exception safety requirements.
         *
         * In addition, if this function is called when calling the destructor
         * during stack unwinding while there is an unhandled exception, this
         * call will simply log a message in case of contract failure. (This is
         * necessary because the class contract does not need to hold if the
         * system is already in a failure status because of an unhandled
         * exception.)
         * @param self A reference to the object (use @c *this from the
         *  contracted destructor).
         * @param[in] body A pointer to function implementing the body.
         * @param[in] name The function name (optional, used for log messages).
         * @note There is no function argument type because destructors take no
         *  argument.
         * @note This call returns @c void because destructors return no
         *  value.
         */
        inline void call(uncopyable_class_type& self, mem_fun_type body,
                const std::string& name = "");
    };

}; // class fun

} // namespace dbc

