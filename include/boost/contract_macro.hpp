
#ifndef BOOST_CONTRACT_MACRO_HPP_
#define BOOST_CONTRACT_MACRO_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Completely disable run-time and compile-time overheads of contract code.

This header also includes all headers file <c>boost/contract/\*.hpp</c> are
necessary to use this macro (including the ones that define ASSERT, virtual_,
access, OVERRIDE, BASE_TYPES, CHECK, constructor_precondition, etc.)

Almost all the macros defined in this header file are variadic macros. On
compilers that do not support variadic macros, programmers can manually code
<c>#ifndef BOOST_CONTRACT_NO_...</c> statements instead (see
@RefSect{extra_topics.disable_contract_compilation__macro_interface_,
Disable Contract Compilation}).
*/

// IMPORTANT: Following headers can always be #included (without any #if-guard)
// because they expand to trivial code that does not affect compile-time. 
// IMPORTANT: Following header must always be #included here (without any
// #if-guard) because they define types and macros that are typically left in
// user code even when contracts are disables (these types and macros never
// affect run-time and their definitions are trivial when contracts are disabled
// so their impact on compile-time is negligible).
#include <boost/contract/core/constructor_precondition.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/core/access.hpp>
#include <boost/contract/core/check_macro.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/override.hpp>

#if     !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <boost/contract/assert.hpp>
#endif

#ifndef BOOST_CONTRACT_NO_PRECONDITIONS
    #define BOOST_CONTRACT_PRECONDITION(...) .precondition(__VA_ARGS__)
#else
    /**
    Program preconditions that can be completely disabled at compile-time.

    @c BOOST_CONTRACT_PRECONDITION(f) expands to code equivalent to:
    
    @code
    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
        .precondition(f)
    #endif
    @endcode
    
    Where:
    
    @arg    <c><b>f</b></c> is the nullay functor called by this library to
            check preconditions @c f().
            Assertions within this functor are usually programmed using
            @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a call
            to this functor indicates a contract assertion failure (and will
            result in this library calling
            @RefFunc{boost::contract::precondition_failure}).
            This functor should capture variables by (constant) value, or better
            by (constant) reference (to avoid extra copies).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)

    @see    @RefSect{tutorial.preconditions, Preconditions},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_PRECONDITION(...) /* nothing */
#endif

#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
    #define BOOST_CONTRACT_POSTCONDITION(...) .postcondition(__VA_ARGS__)
#else
    /**
    Program postconditions that can be completely disabled at compile-time.

    @c BOOST_CONTRACT_POSTCONDITION(f) expands to code equivalent to:
    
    @code
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        .postcondition(f)
    #endif
    @endcode
    
    Where:

    @arg    <c><b>f</b></c> is the functor called by this library to check
            postconditions @c f(...).
            Assertions within this functor are usually programmed using
            @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a call
            to this functor indicates a contract assertion failure (and will
            result in this library calling
            @RefFunc{boost::contract::postcondition_failure}).
            This functor should capture variables by (constant) references (to
            access the values they will have at function exit).
            This functor takes the return value as its one single parameter but
            only for virtual public functions and public functions overrides,
            otherwise it takes no parameter.
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)

    @see    @RefSect{tutorial.postconditions, Postconditions},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_POSTCONDITION(...) /* nothing */
#endif

#ifndef BOOST_CONTRACT_NO_EXCEPTS
    #define BOOST_CONTRACT_EXCEPT(...) .except(__VA_ARGS__)
#else
    /**
    Program exception guarantees that can be completely disabled at
    compile-time.
    
    @c BOOST_CONTRACT_EXCEPT(f) expands to code equivalent to:
    
    @code
    #ifndef BOOST_CONTRACT_NO_EXCEPTS
        .except(f)
    #endif
    @endcode
    
    Where:
    
    @arg    <c><b>f</b></c> is the nullary functor called by this library to
            check exception guarantees @c f().
            Assertions within this functor are usually programmed using
            @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a call
            to this functor indicates a contract assertion failure (and will
            result in this library calling
            @RefFunc{boost::contract::except_failure}).
            This functor should capture variables by (constant) references (to
            access the values they will have at function exit).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)

    @see    @RefSect{tutorial.exception_guarantees, Exception Guarantees},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_EXCEPT(...) /* nothing */
#endif

#ifndef BOOST_CONTRACT_NO_OLDS
    #include <boost/contract/old.hpp>
    #include <boost/preprocessor/facilities/overload.hpp>
    #include <boost/preprocessor/facilities/empty.hpp>
    #include <boost/preprocessor/cat.hpp>

    /* PRIVATE */
    
    #define BOOST_CONTRACT_OLD_VAR_1(ptr) \
        ptr
    #define BOOST_CONTRACT_OLD_VAR_2(ptr, expr) \
        ptr = BOOST_CONTRACT_OLDOF(expr)
    #define BOOST_CONTRACT_OLD_VAR_3(v, ptr, expr) \
        ptr = BOOST_CONTRACT_OLDOF(v, expr)

    #define BOOST_CONTRACT_OLD_VAR_(...) \
        BOOST_PP_CAT(BOOST_PP_OVERLOAD(BOOST_CONTRACT_OLD_VAR_, __VA_ARGS__) \
                (__VA_ARGS__), BOOST_PP_EMPTY())

    /* PUBLIC */
    
    #define BOOST_CONTRACT_OLD(...) .old(__VA_ARGS__)

    #define BOOST_CONTRACT_OLD_PTR(...) \
        boost::contract::old_ptr< __VA_ARGS__ > \
        BOOST_CONTRACT_OLD_VAR_

    #define BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(...) \
        boost::contract::old_ptr_if_copyable< __VA_ARGS__ > \
        BOOST_CONTRACT_OLD_VAR_
#else
    #include <boost/preprocessor/tuple/eat.hpp>
   
    /**
    Program old copies at body that can be completely disabled at compile-time.

    @c BOOST_CONTRACT_OLD(f) expands to code equivalent to:
    
    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        .old(f)
    #endif
    @endcode
    
    Where:

    @arg    <c><b>f</b></c> is the nullary functor called by this library
            @c f() to assign old value copies just before the body is execute
            but after entry invariants (when they apply) and preconditions are
            checked.
            Old value pointers within this functor call are usually assigned
            using @RefMacro{BOOST_CONTRACT_OLDOF}.
            Any exception thrown by a call to this functor will result in
            this library calling @RefFunc{boost::contract::old_failure} (because
            old values could not be copied to check postconditions and exception
            guarantees).
            This functor should capture old value pointers by references so they
            can be assigned (all other variables needed to evaluate old value
            expressions can be captured by (constant) value, or better by
            (constant) reference to avoid extra copies).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)

    @see    @RefSect{advanced_topics.old_values_at_body, Old Values at Body},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_OLD(...) /* nothing */

    /**
    Program old values that can be completely disabled at compile-time (this
    requires the old value type to be copyable).

    This is an overloaded variadic macro and it can be used in the following
    different ways.

    1\. <c>BOOST_CONTRACT_OLD_PTR(T)(ptr)</c> expands to code equivalent
        to the following (this leaves the old value pointer null):

    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::contract::old_ptr<T> ptr // This never uses `v`.
    #endif
    @endcode
    
    2\. <c>BOOST_CONTRACT_OLD_PTR(T)(ptr, expr)</c> expands to code equivalent
        to the following (this initializes the pointer to the old value copy,
        but not to be used for virtual public functions and public function
        overrides):
    
    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::contract::old_ptr<T> ptr = BOOST_CONTRACT_OLDOF(expr)
    #endif
    @endcode
    
    3\. <c>BOOST_CONTRACT_OLD_PTR(T)(v, ptr, expr)</c> expands to code
        equivalent to the following (this initializes the pointer to the old
        value copy for virtual public functions and public function overrides):
    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::contract::old_ptr<T> ptr = BOOST_CONTRACT_OLDOF(v, expr)
    #endif
    @endcode
    
    Where:
    
    @arg    <c><b>T</b></c> is the type of the pointed old value.
            This type must be copyable (i.e.,
            <c>boost::contract::is_old_value_copyable<T>::value</c> is @c true),
            otherwise this pointer will always be null and this library will
            generate a compile-time error when the pointer is dereferenced
            (but see also @c BOOST_CONTRACT_OLD_PTR_IF_COPYABLE).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)
    @arg    <c><b>v</b></c> is the extra parameter of type
            @RefClass{boost::contract::virtual_}<c>*</c> and default value @c 0
            from the enclosing virtual public function or public function
            overrides declaring the contract.
            (This is not a variadic macro parameter so any comma it might
            contain must be protected by round parenthesis, but
            <c>BOOST_CONTRACT_OLD_PTR(T)((v), ptr, expr)</c> will always work.)
    @arg    <c><b>ptr</b></c> is the name of the old value pointer variable.
            (This is not a variadic macro parameter but it will never contain
            any comma because it is an identifier.)
    @arg    <c><b>expr</b></c> is the expression to be evaluated and copied in
            the old value pointer.
            (This is not a variadic macro parameter so any comma it might
            contain must be protected by round parenthesis, but
            <c>BOOST_CONTRACT_OLD_PTR(T)(v, ptr, (expr))</c> will always work.)

    @see    @RefSect{tutorial.old_values, Old Values},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_OLD_PTR(...) BOOST_PP_TUPLE_EAT(0)

    /**
    Program old values that can be completely disabled at compile-time (this
    does not require the old value type to be copyable).

    This is an overloaded variadic macro and it can be used in the following
    different ways.

    1\. <c>BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(T)(ptr)</c> expands to code
        equivalent to the following (this leaves the old value pointer null):

    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::contract::old_ptr_if_copyable<T> ptr // This never uses `v`.
    #endif
    @endcode
    
    2\. <c>BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(T)(ptr, expr)</c> expands to code
        equivalent to the following (this initializes the pointer to the old
        value copy, but not to be used for virtual public functions and public
        function overrides):
    
    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::contract::old_ptr_if_copyable<T> ptr = BOOST_CONTRACT_OLDOF(expr)
    #endif
    @endcode
    
    3\. <c>BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(T)(v, ptr, expr)</c> expands to
        code equivalent to the following (this initializes the pointer to the
        old value copy for virtual public functions and public function
        overrides):
    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::contract::old_ptr_if_copyable<T> ptr =
                BOOST_CONTRACT_OLDOF(v, expr)
    #endif
    @endcode
    
    Where:
    
    @arg    <c><b>T</b></c> is the type of the pointed old value.
            If this type is not copyable (i.e.,
            <c>boost::contract::is_old_value_copyable<T>::value</c> is
            @c false), this pointer will always be null, but this library will
            not generate a compile-time error when this pointer is dereferenced
            (see also @c BOOST_CONTRACT_OLD_PTR).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)
    @arg    <c><b>v</b></c> is the extra parameter of type
            @RefClass{boost::contract::virtual_}<c>*</c> and default value @c 0
            from the enclosing virtual public function or public function
            overrides declaring the contract.
            (This is not a variadic macro parameter so any comma it might
            contain must be protected by round parenthesis, but
            <c>BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(T)((v), ptr, expr)</c> will
            always work.)
    @arg    <c><b>ptr</b></c> is the name of the old value pointer variable.
            (This is not a variadic macro parameter but it will never contain
            any commas because it is an identifier.)
    @arg    <c><b>expr</b></c> is the expression to be evaluated and copied in
            the old value pointer.
            (This is not a variadic macro parameter so any comma it might
            contain must be protected by round parenthesis, but
            <c>BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(T)(v, ptr, (expr))</c> will
            always work.)

    @see    @RefSect{extra_topics.old_value_requirements__templates_,
            Old Value Requirements},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(...) BOOST_PP_TUPLE_EAT(0)
#endif

#ifndef BOOST_CONTRACT_NO_INVARIANTS
    #include <boost/contract/core/config.hpp>

    #define BOOST_CONTRACT_INVARIANT(...) \
        void BOOST_CONTRACT_INVARIANT_FUNC() const __VA_ARGS__

    #define BOOST_CONTRACT_INVARIANT_VOLATILE(...) \
        void BOOST_CONTRACT_INVARIANT_FUNC() const volatile __VA_ARGS__
    
    #define BOOST_CONTRACT_STATIC_INVARIANT(...) \
        static void BOOST_CONTRACT_STATIC_INVARIANT_FUNC() __VA_ARGS__
#else
    /**
    Program (constant) class invariants that can be completely disabled at
    compile-time.

    @c BOOST_CONTRACT_INVARIANT({ ... }) expands to code equivalent to:

    @code
        #ifndef BOOST_CONTRACT_NO_INVARIANTS
            void BOOST_CONTRACT_INVARIANT_FUNC() const {
                ...
            }
        #endif
    @endcode
    
    Where:
    
    @arg    <b>{ ... }</b> is the definition of the function that checks class
            invariants for public functions that are not static and not volatile
            (but see also @c BOOST_CONTRACT_STATIC_INVARIANT and
            @c BOOST_CONTRACT_INVARIANT_VOLATILE).
            Assertions within this function are usually programmed using
            @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a call
            to this function indicates a contract assertion failure (and will
            result in this library calling either
            @RefFunc{boost::contract::entry_invariant_failure} or
            @RefFunc{boost::contract::exit_invariant_failure}).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)

    @see    @RefSect{tutorial.class_invariants, Class Invariants},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_INVARIANT(...) /* nothing */

    /**
    Program volatile class invariants that can be completely disabled at
    compile-time.

    @c BOOST_CONTRACT_INVARIANT_VOLATILE({ ... }) expands to code equivalent to:

    @code
        #ifndef BOOST_CONTRACT_NO_INVARIANTS
            void BOOST_CONTRACT_INVARIANT_FUNC() const volatile {
                ...
            }
        #endif
    @endcode
    
    Where:
    
    @arg    <b>{ ... }</b> is the definition of the function that checks class
            invariants for volatile public functions
            (but see also @c BOOST_CONTRACT_INVARIANT and
            @c BOOST_CONTRACT_STATIC_INVARIANT).
            Assertions within this function are usually programmed using
            @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a call
            to this function indicates a contract assertion failure (and will
            result in this library calling either
            @RefFunc{boost::contract::entry_invariant_failure} or
            @RefFunc{boost::contract::exit_invariant_failure}).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)

    @see    @RefSect{extra_topics.volatile_public_functions,
            Volatile Public Functions},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_INVARIANT_VOLATILE(...) /* nothing */
    
    /**
    Program static class invariants that can be completely disabled at
    compile-time.

    @c BOOST_CONTRACT_STATIC_INVARIANT({ ... }) expands to code equivalent to:

    @code
        #ifndef BOOST_CONTRACT_NO_INVARIANTS
            static void BOOST_CONTRACT_STATIC_INVARIANT_FUNC() {
                ...
            }
        #endif
    @endcode
    
    Where:
    
    @arg    <b>{ ... }</b> is the definition of the function that checks class
            invariants for static public functions
            (but see also @c BOOST_CONTRACT_INVARIANT and
            @c BOOST_CONTRACT_INVARIANT_VOLATILE).
            Assertions within this function are usually programmed using
            @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a call
            to this function indicates a contract assertion failure (and will
            result in this library calling either
            @RefFunc{boost::contract::entry_invariant_failure} or
            @RefFunc{boost::contract::exit_invariant_failure}).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)

    @see    @RefSect{tutorial.class_invariants, Class Invariants},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_STATIC_INVARIANT(...) /* nothing */
#endif

#ifndef BOOST_CONTRACT_NO_CONSTRUCTORS
    #include <boost/contract/constructor.hpp>
    #include <boost/contract/check.hpp>
    #include <boost/contract/detail/name.hpp>

    #define BOOST_CONTRACT_CONSTRUCTOR(...) \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::constructor(__VA_ARGS__)
#else
    /**
    Program contracts that can be completely disabled at compile-time for
    constructors.
            
    @c BOOST_CONTRACT_CONSTRUCTOR(obj) expands to code equivalent to:

    @code
        #ifndef BOOST_CONTRACT_NO_CONSTRUCTORS
            boost::contract::check internal_var = boost::contract::
                    constructor(obj)
        #endif
    @endcode

    Where:
    
    @arg    <c><b>obj</b></c> is the object @c this from the scope of the
            enclosing constructor declaring the contract.
            Constructors check all class invariants, including static and
            volatile invariants (see also @RefSect{tutorial.class_invariants,
            Class Invariants} and
            @RefSect{advanced_topics.volatile_public_functions,
            Volatile Public Functions}).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)
    @arg    <c><b>internal_var</b></c> is a variable name internally generated
            by this library (this name is unique but only on different lines so
            this macro cannot be expanded multiple times on the same line
            number).

    @see    @RefSect{tutorial.constructors, Constructors},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefMacro{BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION}
    */
    #define BOOST_CONTRACT_CONSTRUCTOR(...) /* nothing */
#endif
#if     !defined(BOOST_CONTRACT_NO_CONSTRUCTORS) && \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
    // constructor_precondition.hpp already #included at top.

    #define BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION(...) \
        boost::contract::constructor_precondition< __VA_ARGS__ >
#else
    #include <boost/preprocessor/tuple/eat.hpp>
    // constructor_precondition.hpp always #included at top of this file.

    /**
    Program preconditions that can be completely disabled at compile-time for
    constructors.

    <c>BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION(Class)(f)</c> expands
    to code equivalent to:

    @code
    #if     !defined(BOOST_CONTRACT_NO_CONSTRUCTORS) && \
            !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
        boost::contract::constructor_precondition<Class>(f)
    #else
        // No-op call (likely optimized away, minimal to no overhead).
        boost::contract::constructor_precondition<Class>()
    #endif
    
    @endcode
    
    Where:

    @arg    <c><b>Class</b></c> is the class type of the constructor for which
            preconditions are being programmed.
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)
    @arg    <c><b>f</b></c> is the nullary functor called by this library to
            check constructor preconditions @c f().
            Assertions within this functor call are usually programmed using
            @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a call
            to this functor indicates a contract failure (and will result in
            this library calling
            @RefFunc{boost::contract::precondition_failure}).
            This functor should capture variables by (constant) value, or better
            by (constant) reference to avoid extra copies.
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)

    @see    @RefSect{tutorial.constructors, Constructors},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation},
            @RefMacro{BOOST_CONTRACT_CONSTRUCTOR}
    */
    #define BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION(...) \
        /* always use default ctor (i.e., do nothing) */ \
        boost::contract::constructor_precondition< __VA_ARGS__ >() \
        BOOST_PP_TUPLE_EAT(0)
#endif

#ifndef BOOST_CONTRACT_NO_DESTRUCTORS
    #include <boost/contract/destructor.hpp>
    #include <boost/contract/check.hpp>
    #include <boost/contract/detail/name.hpp>

    #define BOOST_CONTRACT_DESTRUCTOR(...) \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::destructor(__VA_ARGS__)
#else
    /**
    Program contracts that can be completely disabled at compile-time for
    destructors.
    
    @c BOOST_CONTRACT_DESTRUCTOR(obj) expands to code equivalent to:
    
    @code
        #ifndef BOOST_CONTRACT_NO_DESTRUCTORS
            boost::contract::check internal_var = boost::contract::
                    destructor(obj)
        #endif
    @endcode

    Where:
    
    @arg    <c><b>obj</b></c> is the object @c this from the scope of the
            enclosing destructor declaring the contract.
            Destructors check all class invariants, including static and
            volatile invariants (see also @RefSect{tutorial.class_invariants,
            Class Invariants} and
            @RefSect{advanced_topics.volatile_public_functions,
            Volatile Public Functions}).
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)
    @arg    <c><b>internal_var</b></c> is a variable name internally generated
            by this library (this name is unique but only on different lines so
            this macro cannot be expanded multiple times on the same line
            number).

    @see    @RefSect{tutorial.destructors, Destructors},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_DESTRUCTOR(...) /* nothing */
#endif

#ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
    #include <boost/contract/public_function.hpp>
    #include <boost/contract/check.hpp>
    #include <boost/contract/detail/name.hpp>

    #define BOOST_CONTRACT_PUBLIC_FUNCTION(...) \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::public_function(__VA_ARGS__)

    #define BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(...) \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::public_function<__VA_ARGS__>
    
    #define BOOST_CONTRACT_STATIC_PUBLIC_FUNCTION(...) \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::public_function< __VA_ARGS__ >()
#else
    #include <boost/preprocessor/tuple/eat.hpp>

    /**
    Program contracts that can be completely disabled at compile-time for
    non-static public functions (virtual or not) that do not override.
    
    This is an overloaded variadic macro and it can be used in the following
    different ways.

    1\. <c>BOOST_CONTRACT_PUBLIC_FUNCTION(obj)</c> expands to code
        equivalent to the following (for non-virtual public functions that are
        not static and do not override, returning void or not):

    @code
        #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
            boost::contract::check internal_var = boost::contract::
                    public_function(obj)
        #endif
    @endcode
    
    2\. <c>BOOST_CONTRACT_PUBLIC_FUNCTION(v, obj)</c> expands to code
        equivalent to the following (for virtual public functions that are
        not static and do not override, returning void):

    @code
        #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
            boost::contract::check internal_var = boost::contract::
                    public_function(v, obj)
        #endif
    @endcode
    
    3\. <c>BOOST_CONTRACT_PUBLIC_FUNCTION(v, r, obj)</c> expands to code
        equivalent to the following (for virtual public functions that are
        not static and do not override, not returning void):

    @code
        #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
            boost::contract::check internal_var = boost::contract::
                    public_function(v, r, obj)
        #endif
    @endcode

    Where (these are all variadic macro parameters so they can contain commas
    not protected by round parenthesis):

    @arg    <c><b>v</b></c> is the extra parameter of type
            @RefClass{boost::contract::virtual_}<c>*</c> and default value @c 0
            from the enclosing virtual public function declaring the contract.
    @arg    <c><b>r</b></c> is a reference to the return value of the enclosing
            virtual public function declaring the contract.
            This is usually a local variable declared by the enclosing virtual
            public function just before the contract, but programmers must set
            it to the actual value being returned by the function at each
            @c return statement.
    @arg    <c><b>obj</b></c> is the object @c this from the scope of the
            enclosing public function declaring the contract.
            This object might be mutable, @c const, @c volatile, or
            <c>const volatile</c> depending on the cv-qualifier of the enclosing
            function (volatile public functions will check volatile class
            invariants, see @RefSect{extra_topics.volatile_public_functions,
            Volatile Public Functions}).
    @arg    <c><b>internal_var</b></c> is a variable name internally generated
            by this library (this name is unique but only on different lines so
            this macro cannot be expanded multiple times on the same line
            number).
    
    @see    @RefSect{tutorial.public_functions, Public Functions},
            @RefSect{tutorial.virtual_public_functions,
            Virtual Public Functions},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_PUBLIC_FUNCTION(...) /* nothing */
    
    /**
    Program contracts that can be completely disabled at compile-time for
    public function overrides (virtual or not).
    
    This is an overloaded variadic macro and it can be used in the following
    different ways.

    1\. <c>BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(Override)(v, f, obj, ...)</c>
        expands to code equivalent to the following (for public function
        overrides that return void):

    @code
        #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
            boost::contract::check internal_var = boost::contract::
                    public_function<Override>(v, f, obj, ...)
        #endif
    @endcode
    
    2\. <c>BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(Override)(v, r, f, obj, ...)
        </c> expands to code equivalent to the following (for public function
        overrides that do not return void):

    @code
        #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
            boost::contract::check internal_var = boost::contract::
                    public_function<Override>(v, r, f, obj, ...)
        #endif
    @endcode

    Where (these are all variadic macro parameters so they can contain commas
    not protected by round parenthesis):

    @arg    <c><b>Override</b></c> is the type
            <c>override_<i>function-name</i></c> declared using the
            @RefMacro{BOOST_CONTRACT_OVERRIDE} (or equivalent) macro from the
            enclosing function name.
    @arg    <c><b>v</b></c> is the extra parameter of type
            @RefClass{boost::contract::virtual_}<c>*</c> and default value @c 0
            from the enclosing virtual public function declaring the contract.
    @arg    <c><b>r</b></c> is a reference to the return value of the enclosing
            virtual public function declaring the contract.
            This is usually a local variable declared by the enclosing virtual
            public function just before the contract, but programmers must set
            it to the actual value being returned by the function at each
            @c return statement.
    @arg    <c><b>f</b></c> is a pointer to the enclosing public function
            override declaring the contract.
    @arg    <c><b>obj</b></c> is the object @c this from the scope of the
            enclosing public function declaring the contract.
            This object might be mutable, @c const, @c volatile, or
            <c>const volatile</c> depending on the cv-qualifier of the enclosing
            function (volatile public functions will check volatile class
            invariants, see @RefSect{extra_topics.volatile_public_functions,
            Volatile Public Functions}).
    @arg    <c><b>...</b></c> is a variadic macro parameter listing all the
            arguments passed to the enclosing public function override declaring
            the contract (by reference and in order they appear in the enclosing
            function declaration), but excluding the trailing argument @c v.
    @arg    <c><b>internal_var</b></c> is a variable name internally generated
            by this library (this name is unique but only on different lines so
            this macro cannot be expanded multiple times on the same line
            number).
    
    @see    @RefSect{tutorial.public_function_overrides,
            Public Function Overrides},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(...) \
        BOOST_PP_TUPLE_EAT(0)
    
    /**
    Program contracts that can be completely disabled at compile-time for static
    public functions.
    
    @c BOOST_CONTRACT_STATIC_PUBLIC_FUNCTION(Class) expands to code equivalent
    to:
    
    @code
        #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
            boost::contract::check internal_var = boost::contract::
                    public_function<Class>()
        #endif
    @endcode
    
    Where:
    
    @arg    <c><b>Class</b></c> is the class type of the enclosing static
            public function declaring the contract.
            (This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.)
    @arg    <c><b>internal_var</b></c> is a variable name internally generated
            by this library (this name is unique but only on different lines so
            this macro cannot be expanded multiple times on the same line
            number).
    
    @see    @RefSect{tutorial.static_public_functions, Static Public Functions},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_STATIC_PUBLIC_FUNCTION(...) /* nothing */
#endif

#ifndef BOOST_CONTRACT_NO_FUNCTIONS
    #include <boost/contract/function.hpp>
    #include <boost/contract/check.hpp>
    #include <boost/contract/detail/name.hpp>

    #define BOOST_CONTRACT_FUNCTION() \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::function()
#else
    #include <boost/preprocessor/facilities/empty.hpp>

    /**
    Program contracts that can be completely disabled at compile-time for
    (non-public) functions.
    
    This can be used to program contracts for non-member functions but also for
    private and protected functions, lambda functions, loops, arbitrary blocks
    of code, etc.

    @c BOOST_CONTRACT_FUNCTION() expands to code equivalent to:
    
    @code
        #ifndef BOOST_CONTRACT_NO_FUNCTIONS
            boost::contract::check internal_var = boost::contract::
                    function()
        #endif
    @endcode
    
    Where:
    
    @arg    <c><b>internal_far</b></c> is a variable name internally generated
            by this library (this name is unique but only on different lines so
            this macro cannot be expanded multiple times on the same line
            number).
    
    @see    @RefSect{tutorial.non_member_functions, Non-Member Functions},
            @RefSect{advanced_topics.private_and_protected_functions,
            Private and Protected Functions},
            @RefSect{advanced_topics.lambdas__loops__code_blocks__etc_,
            Lambdas\, Loops\, Code Blocks\, Etc.},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_FUNCTION() /* nothing */
#endif

#endif // #include guard

