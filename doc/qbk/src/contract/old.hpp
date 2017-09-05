// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

/** @file
Facilities to support old values in postconditions.

Postconditions can access old variable values (before body executions) for types tagged @c contract::copyable.
*/

namespace contract {

/**
Macro used to access old value for the variable with the specified name in postconditions.

The library automatically declares variables to hold old values of types tagged @c contract::copyable and makes then accessible in the postconditions code block (and from the postconditions code block only).
This macro simply expands the specified name to the name of the old variable automatically declared by the library.

For example, in postconditions of a member function <c>void myvector<T>::push_back(const T& element)</c>, if both the class type @c myvector and the @c element argument type <c>const T&</c> have been tagged copyable (see the @c sequence parameter of @c CONTRACT_FUNCTION() and @c contract::copy) then the following old values are available:
@code
    CONTRACT_OLDOF(this)->...   // Object old value.
    CONTRACT_OLDOF(element)...  // Old value of function argument `element`.
@endcode

@Params
@Param{variable_name, Use @c this to access a pointer to the old object value. Use one of the function argument names to access the old value of that argument. The type of the variable with the specified name must be tagged @c contract::copyable in the signature sequence its old value to be available (otherwise the use of this macro will generate a compile-time error with @c noold in the error message).}
@EndParams

@Returns This macro expands to code equivalent to the following:
@code
    contract_old_ ## variable_name ## _
@endcode
(The preprocessor operator @c ## concatenates the specified tokens.)

@Note Shallow copies are performed for old values of pointer types (unless the pointed type defines a different copy constructor or @c contract::copy has been specialized for the pointed type to perform a different copy operation).
Therefore, if a pointer type is tagged @c contract::copyable, the old pointer value will be available in the postconditions and not the old pointed value -- this might not be what you intended.
The notable exception is the object which is passed by pointer (like @c this) but its old value is automatically deep copied by the library.

@Note The library supports old values for the object and all the function argument types.
This is a subset of the old values supported by Eiffel which are old values for any expression that can be evaluated in postconditions.
However, the old values supported by the library are usually enough to program the postconditions.

@See @c contract::copy, @c contract::copyable
*/
#define CONTRACT_OLDOF(variable_name)

/**
Tag the specified type @c T copyable.

In general, you should tag a type copyable @b only when the related variable old value (before body execution) is really needed in postconditions because:

-# The correspondent variable value will be copied before body execution adding run-time overhead.
The library performs the extra copy to support old values in postconditions only for variables of types tagged copyable and only when the @c CONTRACT_CHECK_POSTCONDITION macro is defined.
-# A type tagged copyable has the extra requirement that it must define an accessible constant-correct copy constructor (otherwise the library will generate a compile-time error).
The copy constructor is constant-correct when it accesses the copied value via a constant reference argument (this way the copied value cannot be mistakenly modified while it is being copied to check contracts):
@code
    T::T(const T& source) { ... } // Must be accessible and construct from a const&.
@endcode
See @c contract::copy to relax this requirement.

@Params
@Param{T, The type to be tagged. The @b entire type with eventual @c const\, <c>&</c>\, <c>*</c>\, etc qualifier should be tagged copyable. For example\, if the type is <c>const int&</c> then <c>contract::copyable<const int&></c> should be used (and not <c>const contract::copyable<int>&</c>).}
@EndParams

@Note When using the contract macros, <c>(copyable)(T)</c> is used instead of @c contract::copyable<T> to tag the type @c T copyable in the macro @c sequence parameter.

@See @c CONTRACT_OLDOF(), @c contract::copy
*/
template<typename T> class copyable {};

/**
Copy wrapper used by the library to make the actual copy of variables for which old values are needed in postconditions.

@Params
@Param{T, Type of the object being copied.}
@EndParams

@Note Under most circumstances programmers do @b not need to use this class which is usually just used internally by the library.

Specifically, if the copied type @c T already has a public constant-correct copy constructor then the @c contract::copy template will use such a constructor by default and programmers do not need to define any specialization of the @c contract::copy template.
@code
    class T {
    public:
        T(const T& source); // Public constant-correct copy constructor.

        ...
    };
@endcode
The constructor needs to be public for the library to access it and it needs to be contract-correct for the library to use it while still ensuring the contract-correctness of the contract checking code.

However, the @c contract::copy template can be specialized by programmers to expose a non-public constant-correct copy constructor to the library via friendship:
@code
    class x {
        ... // User class with no public copy constructor.

    private:
        // Only the library can access this copy constructor via friendship.
        friend class contract::copy<x>;
        x(const x* source); // Constant-correct (private) copy constructor.
    };
@endcode

Furthermore, programmers can specialize the @c contract::copy template for a user defined type in order to relax the library requirement of an accessible constant-correct copy constructor all together (it is recommended @b not to do this unless strictly necessary).
@code
    class y: boost::noncopyable { // User class with no copy constructor at all.
        // Self backup copy maintained by the class itself.
        y backup_copy; // Use this as the old value.

        ...
    };
    
    namespace contract {
    
    // Specialization to handle y old value without copying it.
    template<>
    class copy<y> {
    public:
        // It must declare a member variable named `value`.
        const y& value; // Maintains constant-correctness by using const member.
        
        // It must defined this copy constructor. It must maintains
        // constant-correctness taking a constant reference to `source`.
        copy(const y& source):
                // This does not copy `source` (`value` is a reference).
                // Instead it uses its `source` existing backup copy.
                value(source.backup_copy) {}
    };
    
    } // namespace
@endcode

The @c contract::copy template can also be specialized to alter the copy semantics for a type (it is recommended @b not to do this unless strictly necessary).
For example, by default a pointer to a double number <c>double*</c> is copied by copying the pointer value and not by copying the pointed number (this is the usual C++ copy semantic for pointers).
The following specialization of @c contract::copy copies the pointed number instead of the pointer value for postcondition old values of argument of type <c>double*</c>.
@code
    namespace contract {
    
    template<>
    class copy<double*> {
    private:
        double number_; // Copied pointed number value.
    public:
        const double* value; // Pointer to number_.
        
        copy(const double* number_ptr): number_(), value(&number_) {
            // Check pointer is valid.
            if (!number_ptr) throw std::logic_error("Invalid number pointer");
            number_ = *number_ptr; // Copy the *pointed* number.
        }
    };
    
    } // namespace
@endcode

See also the Examples section for a concrete example that specializes @c contract::copy to relax the accessible constant-correct constructor requirement.
*/
template<typename T>
class copy {
public:
    /**
    The copied value (used as the old value in postconditions).
    
    The variable type is defined as follows:
    @code
        typedef typename boost::add_const<typename 
                boost::remove_reference<T>::type>::type __ConstType__;
    @endcode
    */
    __ConstType__ value;
    
    /**
    Constructor which copies the specified object.

    The copy is done by constructing the member variable `value` using an accessible constant-correct copy constructor for @c T (which must be available otherwise the library will generate a compile-time error).
    
    @Note Source is a constant reference so to ensure contract checking
    constant-correctness (correctly, this constraint cannot be relaxed not
    even by specializing this class template).
    
    The constant reference type is defined as follows:
    @code
        typedef typename boost::add_reference<const_type>::type __ConstRef__;
    @endcode
    
    @Params
    @Param{source, The source object to be copied into the @c value member variable.}
    @EndParams
    */
    copy(__ConstRef__ source): value(source) {}
};

} // namespace

