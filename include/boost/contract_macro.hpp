
#ifndef BOOST_CONTRACT_MACRO_HPP_
#define BOOST_CONTRACT_MACRO_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Completely disable run-time and compile-time overheads of contract code.

Almost all the macros defined in this header file are variadic macros. On
compilers that do not support variadic macros, programmers can manually code
<c>#ifndef BOOST_CONTRACT_NO_...</c> statements instead (see
@RefSect{extra_topics, Extra Topics}).
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

// TODO: Document these macros will cause all pre, post, inv assertions to have the same line number (but different code text) in the error message. And that is bad for compiler errors while programming contracts as well (all on same line... and more cryptic).

// TODO: Add tests for all variadic macros defined here (with unwrapped commas in code, types, etc.).

// TODO: Make sure there are test for /all/ these macros (OLD_PTR_IF_COPYABLE, EXPECT, INVARIANT_VOLATILE, etc.).

#ifndef BOOST_CONTRACT_NO_PRECONDITIONS
    #define BOOST_CONTRACT_PRECONDITION(...) .precondition(__VA_ARGS__)
#else
    /**
    Macro to program preconditions that can be completely disabled at
    compile-time.
    @c BOOST_CONTRACT_PRECONDITION(f) expands to code equivalent to:
    @code
    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
        .precondition(f)
    #endif
    @endcode
    Where:
    @arg    @b f is a nullary functor that checks preconditions. This is a
            variadic macro parameter so it can contain commas not protected by
            round parenthesis.

    @see @RefSect{tutorial, Tutorial}, @RefSect{extra_topics, Extra Topics}
    */
    #define BOOST_CONTRACT_PRECONDITION(...) /* nothing */
#endif

#ifndef BOOST_CONTRACT_NO_OLDS
    #include <boost/contract/old.hpp>
    #include <boost/preprocessor/facilities/overload.hpp>
    #include <boost/preprocessor/facilities/empty.hpp>
    #include <boost/preprocessor/cat.hpp>
    
    #define BOOST_CONTRACT_OLD_VAR_1(ptr) \
        ptr
    #define BOOST_CONTRACT_OLD_VAR_2(ptr, expr) \
        ptr = BOOST_CONTRACT_OLDOF(expr)
    #define BOOST_CONTRACT_OLD_VAR_3(v, ptr, expr) \
        ptr = BOOST_CONTRACT_OLDOF(v, expr)

    #define BOOST_CONTRACT_OLD_VAR_(...) \
        BOOST_PP_CAT(BOOST_PP_OVERLOAD(BOOST_CONTRACT_OLD_VAR_, __VA_ARGS__) \
                (__VA_ARGS__), BOOST_PP_EMPTY())

    #define BOOST_CONTRACT_OLD_PTR(...) \
        boost::contract::old_ptr< __VA_ARGS__ > \
        BOOST_CONTRACT_OLD_VAR_
    #define BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(...) \
        boost::contract::old_ptr_if_copyable< __VA_ARGS__ > \
        BOOST_CONTRACT_OLD_VAR_
    
    #define BOOST_CONTRACT_OLD(...) .old(__VA_ARGS__)
#else
    #include <boost/preprocessor/tuple/eat.hpp>

    /**
    Macro to program old values that can be completely disabled at compile-time.
    This is an overloaded variadic macro and it can be used in a number of
    different ways:

    1\. <c>BOOST_CONTRACT_OLD_PTR(T)(ptr)</c> expands to code equivalent
        to:
    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::contract::old_ptr<T> ptr // Never requires `v`.
    #endif
    @endcode
    2\. <c>BOOST_CONTRACT_OLD_PTR(T)(ptr, expr)</c> expands to code
        equivalent to:
    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::contract::old_ptr<T> ptr = BOOST_CONTRACT_OLDOF(expr)
    #endif
    @endcode
    3\. <c>BOOST_CONTRACT_OLD_PTR(T)(v, ptr, expr)</c> expands to code
        equivalent to:
    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::contract::old_ptr<T> ptr = BOOST_CONTRACT_OLDOF(v, expr)
    #endif
    @endcode
    Where:
    @arg    @b T is the old value type. This type must be copy constructible
            (i.e., @c boost::contract::is_old_value_copyable<T>::value must be
            @c true), otherwise this library will generate a compile-time error
            if the old value pointer is dereferenced. This is a variadic macro
            parameter so it can contain commas not protected by round
            parenthesis.
    @arg    @b v is the extra parameter of type
            <c>boost::contract::virtual_*</c> passed to the enclosing virtual
            public function.
    @arg    @b ptr is the name of the old value pointer variable.
    @arg    @b expr is the expression to be evaluated and copied in the old
            value. This is not a variadic macro parameter so any comma it might
            contain must be protected by round parenthesis (i.e.,
            <c>BOOST_CONTRACT_OLD_PTR(T)(v, ptr, (expr))<c/> will always work).
    
    @see @RefSect{tutorial, Tutorial}, @RefSect{extra_topics, Extra Topics}
    */
    #define BOOST_CONTRACT_OLD_PTR(...) BOOST_PP_TUPLE_EAT(0)

    /**
    Macro to program old values that can be completely disabled at compile-time
    (for old value types that might be non-copyable).
    This is an overloaded variadic macro and it can be used in a number of
    different ways:

    1\. <c>BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(T)(ptr)</c> expands to code
        equivalent to:
    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::contract::old_ptr_if_copyable<T> ptr // Never requires `v`.
    #endif
    @endcode
    2\. <c>OOST_CONTRACT_OLD_PTR_IF_COPYABLE(T)(ptr, expr)</c> expands to
        code equivalent to:
    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::contract::old_ptr_if_copyable<T> ptr = BOOST_CONTRACT_OLDOF(expr)
    #endif
    @endcode
    3\. <c>BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(T)(v, ptr, expr)</c> expands
        to code equivalent to:
    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::contract::old_ptr_if_copyable<T> ptr =
                BOOST_CONTRACT_OLDOF(v, expr)
    #endif
    @endcode
    Where:
    @arg    @b T is the old value type. If this type is not copy constructible
            (i.e., @c boost::contract::is_old_value_copyable<T>::value is
            @c false), the old value pointer will be set to null. This is a
            variadic macro parameter so it can contain commas not protected by
            round parenthesis.
    @arg    @b v is the extra parameter of type
            <c>boost::contract::virtual_*</c> passed to the enclosing virtual
            public function.
    @arg    @b ptr is the name of the old value pointer variable.
    @arg    @b expr is the expression to be evaluated and copied in the old
            value. This is not a variadic macro parameter so any comma it might
            contain must be protected by round parenthesis (i.e.,
            <c>BOOST_CONTRACT_OLD_PTR(T)(v, ptr, (expr));<c/> will always
            work).
    
    @see @RefSect{extra_topics, Extra Topics}
    */
    #define BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(...) BOOST_PP_TUPLE_EAT(0)
    
    /**
    Macro to program old value copies at body that can be completely disabled at
    compile-time.
    @c BOOST_CONTRACT_OLD(f) expands to code equivalent to:
    @code
    #ifndef BOOST_CONTRACT_NO_OLDS
        .old(f)
    #endif
    @endcode
    Where:
    @arg    @b f is a nullary functor that assigns old pointers to old value
            copies. This is a variadic macro parameter so it can contain commas
            not protected by round parenthesis.

    @see    @RefSect{advanced_topics, Advanced Topics},
            @RefSect{extra_topics, Extra Topics}
    */
    #define BOOST_CONTRACT_OLD(...) /* nothing */
#endif
    
#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
    #define BOOST_CONTRACT_POSTCONDITION(...) .postcondition(__VA_ARGS__)
#else
    /**
    Macro to program postconditions that can be completely disabled at
    compile-time.
    @c BOOST_CONTRACT_POSTCONDITION(f) expands to code equivalent to:
    @code
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        .postcondition(f)
    #endif
    @endcode
    Where:
    @arg    @b f is a functor that checks postconditions. This function takes
            the return value as its one single parameter but only for virtual
            public functions and public functions overrides, otherwise it takes
            no parameter. This is a variadic macro parameter so it can contain
            commas not protected by round parenthesis.

    @see @RefSect{tutorial, Tutorial}, @RefSect{extra_topics, Extra Topics}
    */
    #define BOOST_CONTRACT_POSTCONDITION(...) /* nothing */
#endif

#ifndef BOOST_CONTRACT_NO_EXCEPTS
    #define BOOST_CONTRACT_EXCEPT(...) .except(__VA_ARGS__)
#else
    /**
    Macro to program exception guarantees that can be completely disabled at
    compile-time.
    @c BOOST_CONTRACT_EXCEPT(f) expands to code equivalent to:
    @code
    #ifndef BOOST_CONTRACT_NO_EXCEPTS
        .except(f)
    #endif
    @endcode
    Where:
    @arg    @b f is a nullary functor that checks exception guarantees.
            This is a variadic macro parameter so it can contain commas not
            protected by round parenthesis.

    @see @RefSect{tutorial, Tutorial}, @RefSect{extra_topics, Extra Topics}
    */
    #define BOOST_CONTRACT_EXCEPT(...) /* nothing */
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
    Macro to program (constant) class invariants that can be completely disabled
    at compile-time.
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
            invariants (this can be a semicolon @c ; to separate this function
            definition from its declaration as usual in C++). This is a variadic
            macro parameter so it can contain commas not protected by round
            parenthesis.

    @see @RefSect{tutorial, Tutorial}, @RefSect{extra_topics, Extra Topics}
    */
    #define BOOST_CONTRACT_INVARIANT(...) /* nothing */

    /**
    Macro to program volatile class invariants that can be completely disabled
    at compile-time.
    @c BOOST_CONTRACT_INVARIANT_VOLATILE({ ... }) expands to code equivalent
    to:
    @code
        #ifndef BOOST_CONTRACT_NO_INVARIANTS
            void BOOST_CONTRACT_INVARIANT_FUNC() const volatile {
                ...
            }
        #endif
    @endcode
    Where:
    @arg    <b>{ ... }</b> is the definition of the function that checks
            volatile class invariants (this can be a semicolon @c ; to separate
            this function definition from its declaration as usual in C++). This
            is a variadic macro parameter so it can contain commas not protected
            by round parenthesis.

    @see @RefSect{extra_topics, Extra Topics}
    */
    #define BOOST_CONTRACT_INVARIANT_VOLATILE(...) /* nothing */
    
    /**
    Macro to program static class invariants that can be completely disabled
    at compile-time.
    @c BOOST_CONTRACT_STATIC_INVARIANT({ ... }) expands to code equivalent
    to:
    @code
        #ifndef BOOST_CONTRACT_NO_INVARIANTS
            static void BOOST_CONTRACT_STATIC_INVARIANT_FUNC() {
                ...
            }
        #endif
    @endcode
    Where:
    @arg    <b>{ ... }</b> is the definition of the function that checks static
            class invariants (this can be a semicolon @c ; to separate this
            function definition from its declaration as usual in C++). This is a
            variadic macro parameter so it can contain commas not protected by
            round parenthesis.

    @see @RefSect{tutorial, Tutorial}, @RefSect{extra_topics, Extra Topics}
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
    Macro to program contracts that can be completely disabled at compile-time
    for constructors.
    @c BOOST_CONTRACT_CONSTRUCTOR(obj) expands to code equivalent to:
    @code
        #ifndef BOOST_CONTRACT_NO_CONSTRUCTORS
            boost::contract::check internal_identifier =
                    boost::contract::constructor(obj)
        #endif
    @endcode
    Where:
    @arg    @b obj is a pointer to the object of from the enclosing constructor
            scope (typically @c this).
    @arg    @b internal_identifier is a variable name internally generated by
            this library (this is unique but only on different line numbers so
            this macro cannot be used multiple times on the same line).
    
    @see @RefSect{tutorial, Tutorial}, @RefSect{extra_topics, Extra Topics}
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
    Macro to program preconditions that can be completely disabled at
    compile-time for constructors.
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
    @arg    @b Class is the type of the enclosing constructor class. This is a
            variadic macro parameter so it can contain commas not protected by
            round parenthesis.
    @arg    @b f is a nullary functor that checks preconditions. This is handled
            as a variadic macro parameter so it can contain commas not protected
            by round parenthesis.

    @see @RefSect{tutorial, Tutorial}, @RefSect{extra_topics, Extra Topics}
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
    Macro to program contracts that can be completely disabled at compile-time
    for destructors.
    @c BOOST_CONTRACT_DESTRUCTOR(obj) expands to code equivalent to:
    @code
        #ifndef BOOST_CONTRACT_NO_DESTRUCTORS
            boost::contract::check internal_identifier =
                    boost::contract::destructor(obj)
        #endif
    @endcode
    Where:
    @arg    @b obj is a pointer to the object of from the enclosing destructor
            scope (typically @c this).
    @arg    @b internal_identifier is a variable name internally generated by
            this library (this is unique but only on different line numbers so
            this macro cannot be used multiple times on the same line).
    
    @see @RefSect{tutorial, Tutorial}, @RefSect{extra_topics, Extra Topics}
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
    Macro to program contracts that can be completely disabled at compile-time
    for (non-static and not overriding) public functions.
    @c BOOST_CONTRACT_PUBLIC_FUNCTION(param_list) expands to
    code equivalent to:
    @code
        #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
            boost::contract::check internal_identifier =
                    boost::contract::public_function(param_list)
        #endif
    @endcode
    Where:
    @arg    @b param_list is the (overloaded) list of parameters normally passed
            to @c boost::contract::public_function for non-static public
            functions that do not override any virtual function. This is handled
            as a variadic macro parameter so it can contain commas not protected
            by round parenthesis.
    @arg    @b internal_identifier is a variable name internally generated by
            this library (this is unique but only on different line numbers so
            this macro cannot be used multiple times on the same line).
    
    @see @RefSect{tutorial, Tutorial}, @RefSect{extra_topics, Extra Topics}
    */
    #define BOOST_CONTRACT_PUBLIC_FUNCTION(...) /* nothing */
    
    /**
    Macro to program contracts that can be completely disabled at compile-time
    for public functions that override virtual functions.
    <c>BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(Override)(param_list)</c>
    expands to code equivalent to:
    @code
        #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
            boost::contract::check internal_identifier =
                    boost::contract::public_function<Override>(param_list)
        #endif
    @endcode
    Where:
    @arg    @b Override is the introspection type trait generated using
            @c BOOST_CONTRACT_OVERRIDE, @c BOOST_CONTRACT_OVERRIDES, or
            @c BOOST_CONTRACT_NAMED_OVERRIDE. This is a variadic macro parameter
            so it can contain commas not protected by round parenthesis.
    @arg    @b param_list is the (overloaded) list of parameters normally passed
            to @c boost::contract::public_function for public functions that
            override virtual functions. This is handled as a variadic macro
            parameter so it can contain commas not protected by round
            parenthesis.
    @arg    @b internal_identifier is a variable name internally generated by
            this library (this is unique but only on different line numbers so
            this macro cannot be used multiple times on the same line).
    
    @see @RefSect{tutorial, Tutorial}, @RefSect{extra_topics, Extra Topics}
    */
    #define BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(...) \
        BOOST_PP_TUPLE_EAT(0)
    
    /**
    Macro to program contracts that can be completely disabled at compile-time
    for static public functions.
    @c BOOST_CONTRACT_STATIC_PUBLIC_FUNCTION(Class) expands to
    code equivalent to:
    @code
        #ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
            boost::contract::check internal_identifier =
                    boost::contract::public_function<Class>()
        #endif
    @endcode
    Where:
    @arg    @b Class is the type of the class of the enclosing static public
            function. This is a variadic macro parameter so it can contain
            commas not protected by round parenthesis.
    @arg    @b internal_identifier is a variable name internally generated by
            this library (this is unique but only on different line numbers so
            this macro cannot be used multiple times on the same line).
    
    @see @RefSect{tutorial, Tutorial}, @RefSect{extra_topics, Extra Topics}
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
    Macro to program contracts that can be completely disabled at compile-time
    for (non-public) functions.
    @c BOOST_CONTRACT_FUNCTION() expands to code equivalent to:
    @code
        #ifndef BOOST_CONTRACT_NO_FUNCTIONS
            boost::contract::check internal_identifier =
                    boost::contract::function()
        #endif
    @endcode
    Where:
    @arg    @b internal_identifier is a variable name internally generated by
            this library (this is unique but only on different line numbers so
            this macro cannot be used multiple times on the same line).
    
    @see @RefSect{tutorial, Tutorial}, @RefSect{extra_topics, Extra Topics}
    */
    #define BOOST_CONTRACT_FUNCTION() /* nothing */
#endif

#endif // #include guard

