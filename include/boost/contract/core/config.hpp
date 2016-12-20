
#ifndef BOOST_CONTRACT_CONFIG_HPP_
#define BOOST_CONTRACT_CONFIG_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Facilities to configure this library compile-time and run-time behaviour.
*/

// IMPORTANT: This header MUST NOT #include any other header of this lib.
// That way users can #include this header and not #include any of this lib
// headers after that depending on the contract 0/1 macros below ensuring no
// compilation overhead.

#ifdef DOXYGEN
    #define BOOST_CONTRACT_STATIC_LINK
#elif   defined(BOOST_CONTRACT_STATIC_LINK) && ( \
        defined(BOOST_CONTRACT_HEADER_ONLY) || \
        defined(BOOST_ALL_DYN_LINK) )
    #error "STATIC_LINK defined with HEADER_ONLY and/or ALL_DYN_LINK"
#endif

#ifdef DOXYGEN
    /**
    Define this macro when compiling user code to avoid compiling this library
    (undefined by default).
    If this macro is defined, this library does not have to be compiled
    separately from user code. This library headers are simply included in the
    user program and this library implementation code is compiled as part of the
    user program. However, in general this library must be compiled as a shared
    library defining @RefMacro{BOOST_CONTRACT_DYN_LINK} when it is used by
    multiple programs (otherwise the contracts will not necessarily be checked
    correctly at run-time).
    
    @b Rationale: Named after @c BOOST_CHRONO_HEADER_ONLY.
    @see @RefSect{getting_started, Getting Started}
    */
    #define BOOST_CONTRACT_HEADER_ONLY
#elif   defined(BOOST_CONTRACT_HEADER_ONLY) && ( \
        defined(BOOST_CONTRACT_STATIC_LINK) || \
        defined(BOOST_ALL_DYN_LINK) )
    #error "HEADER_ONLY defined with STATIC_LINK and/or ALL_DYN_LINK"
#endif

#ifdef DOXYGEN
    /**
    Define this macro to not lock internal library data for thread safety
    (undefined by default).
    Defining this macro will make the library implementation code not thread
    safe so this macro should not be defined unless the library is being used
    strictly under single-threaded applications. However, when this macro is
    left undefined this library needs to use "global" locks (to ensure contract
    checking is globally disabled when other contracts are being checked and
    also to safely access the failure handler functors) and that could introduce
    a significant amount of synchronization in some multi-threaded applications.
    
    @b Rationale:   Named after @c BOOST_DISABLE_THREADS.
    @see @RefSect{contract_programming_overview, Contract Programming Overview}
    */
    #define BOOST_CONTRACT_DISABLE_THREADS
#endif

#ifndef BOOST_CONTRACT_MAX_ARGS
    /**
    Maximum number of function arguments when no variadic macros are supported
    (default to @c 10).
    On compilers that support variadic macros, this macro has no effect.
    On compilers that do not support variadic macros, this macro can be defined
    to support a maximum number of arguments different than @c 10 for
    overriding public functions (contracted via
    @RefFunc{boost::contract::public_function}).
    (Compilation times of this library were measured to be comparable between
    compilers that support variadic macros and compilers that do not.)
    @note   Regardless of the value of this macro and of compiler support for
            variadic macros, there is an intrinsic limit around 18 arguments
            for overriding public functions (because of similar limits for some
            Boost libraries like Boost.MPL and Boost.FunctionTypes internally
            used by this library).

    @b Rationale: Named after @c BOOST_FUNCTION_MAX_ARGS.
    @see @RefSect{tutorial, Tutorial}
    */
    #define BOOST_CONTRACT_MAX_ARGS 10
#endif

#ifndef BOOST_CONTRACT_BASE_TYPEDEF
    /**
    Define the name of the base type @c typedef (@c base_types by default).
    This macro can be defined if the @c typedef declared using
    @RefMacro{BOOST_CONTRACT_BASE_TYPES} must have a name different than
    @c base_types.
    
    @b Rationale:   This macro cannot be called @c BOOST_CONTRACT_BASE_TYPES
                    because that is already the name of the macro that extracts
                    public bases. Then @c BOOST_CONTRACT_BASE_TYPEDEF is a
                    reasonable name (but without changing this macro default
                    definition to @c base_typedef because @c base_types is
                    remains the preferred syntax for user code).
    @see @RefSect{tutorial, Tutorial}
    */
    #define BOOST_CONTRACT_BASE_TYPEDEF base_types
#endif

#ifndef BOOST_CONTRACT_INVARIANT
    /**
    Define the name of the invariant member functions (@c invariant by defult).
    This macro expands to the name of the @c const and <c>const volatile</c>
    member functions that check mutable and volatile class invariants
    respectively. This macro can be defined if the invariant functions need to
    be named differently from @c invariant.
    @see @RefSect{tutorial, Tutorial}
    */
    #define BOOST_CONTRACT_INVARIANT invariant
#endif

#ifndef BOOST_CONTRACT_STATIC_INVARIANT
    /**
    Define the name of the static invariant member function (@c static_invariant
    by defult).
    This macro expands to the name of the @c static member function that checks
    static class invariants. This macro can be defined if the static invariant
    function needs to be named differently from @c static_invariant.
    
    @b Rationale:   C++ does not allow to overload member functions based on the
                    @c static classifier, so a name different from the one
                    expanded by @RefMacro{BOOST_CONTRACT_INVARIANT} needed to be
                    used here.
    @see @RefSect{tutorial, Tutorial}
    */
    #define BOOST_CONTRACT_STATIC_INVARIANT static_invariant
#endif

#ifdef DOXYGEN
    /**
    Disable a number of static checks and related compile-time errors generated
    by this library (undefined by default).
    Among other compile-time errors, defining this macro disables compile-time
    error for the following checks:
    @li The static invariant member function must be @c static.
    @li Non-static invariant member functions must be either @c const,
        <c>const volatile</c>, or <c>volatile const</c>.
    @li A class that programs contracts for one or more overriding public
        functions via @RefFunc{boost::contract::public_function} must also
        define the @RefMacro{BOOST_CONTRACT_BASE_TYPES} @c typedef.
    */
    #define BOOST_CONTRACT_PERMISSIVE
#endif

#ifdef DOXYGEN
    /**
    Code block to execute if contracts are not assigned to a
    @RefClass{boost::contract::check} variable (undefined by default).
    In general, there is a logic error in the program when contracts are not
    assigned to a local variable of type @RefClass{boost::contract::check}.
    Therefore, by default (i.e., when this macro is not defined) this library
    calls @c assert with a @c false condition in such cases. If this macro is
    defined, this library will execute the code expanded by the macro instead of
    calling @c assert (if programmers prefer to throw an exception, etc.).
    */
    #define BOOST_CONTRACT_ON_MISSING_CHECK_DECL
#endif

#ifdef DOXYGEN
    /**
    Define this macro to not disable other any assertion checking while checking
    preconditions (undefined by default).
    The @RefSect{bibliography, [N1962]} proposal does not disable any assertion
    checking while checking preconditions (because unchecked arguments can be
    passed to function bodies if contract checking is disabled within
    precondition checking when function bodies are executed directly or
    indirectly to check the preconditions in question). However, not disabling
    assertion checking while checking preconditions can lead to infinite
    recursion in user code so by default this macro is not defined (but this
    macro can be defined to obtain the behaviour specified in
    @RefSect{bibliography, [1962]}).
    @see @RefSect{contract_programming_overview, Contract Programming Overview}
    */
    #define BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION
#endif

#ifdef DOXYGEN
    #define BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
#endif

#ifdef DOXYGEN
    /**
    If defined, this library does not check preconditions at run-time (undefined
    by default).
    If this macro is defined, this library implementation code is also optimized
    to reduce compile-time (not just run-time) overhead associated with checking
    preconditions. Users can also manually program @c \#ifdef statements in
    their code using this macro to completely disable compilation of
    preconditions (not recommended).
    @see @RefSect{advanced_topics, Advanced Topics}
    */
    #define BOOST_CONTRACT_NO_PRECONDITIONS
#endif

#ifdef DOXYGEN
    /**
    If defined, this library does not check postconditions and does not copy old
    values at run-time (undefined by default).
    If this macro is defined, this library implementation code is also optimized
    to reduce compile-time (not just run-time) overhead associated with checking
    postconditions and copying old values. Users can also manually program
    @c \#ifdef statements in their code using this macro to completely disable
    compilation of postconditions and old values (not recommended).
    @see @RefSect{advanced_topics, Advanced Topics}
    */
    #define BOOST_CONTRACT_NO_POSTCONDITIONS
#endif

#if defined(DOXYGEN) || (!defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_INVARIANTS))
    /**
    If defined, this library does not check entry invariants at run-time
    (undefined by default).
    If this macro is defined, this library implementation code is also optimized
    to reduce compile-time (not just run-time) overhead associated with
    checking class invariants at function entry.
    
    This macro can always be defined by itself but it is also automatically
    defined when @RefMacro{BOOST_CONTRACT_NO_INVARIANTS} is defined.
    @see @RefSect{advanced_topics, Advanced Topics}
    */
    #define BOOST_CONTRACT_NO_ENTRY_INVARIANTS
#endif

#if defined(DOXYGEN) || (!defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_INVARIANTS))
    /**
    If defined, this library does not check exit invariants at run-time
    (undefined by default).
    If this macro is defined, this library implementation code is also optimized
    to reduce compile-time (not just run-time) overhead associated with
    checking class invariants at function exit.
    
    This macro can always be defined by itself but it is also automatically
    defined when @RefMacro{BOOST_CONTRACT_NO_INVARIANTS} is defined.
    @see @RefSect{advanced_topics, Advanced Topics}
    */
    #define BOOST_CONTRACT_NO_EXIT_INVARIANTS
#endif

#if     !defined(BOOST_CONTRACT_NO_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS)
    /**
    If defined, this library does not check class invariants at run-time
    (undefined by default).
    If this macro is defined, this library implementation code is also optimized
    to reduce compile-time (not just run-time) overhead associated with
    checking class invariants (at both function entry and exit). Users can also
    manually program @c \#ifdef statements in their code using this macro to
    completely disable compilation of class invariants (not recommended).
    
    This macro can always be defined by itself but it is also automatically
    defined when @RefMacro{BOOST_CONTRACT_NO_ENTRY_INVARIANTS} and
    @RefMacro{BOOST_CONTRACT_NO_EXIT_INVARIANTS} are both defined.
    @see @RefSect{advanced_topics, Advanced Topics}
    */
    #define BOOST_CONTRACT_NO_INVARIANTS
#endif

// Following are NOT configuration macros.

// Ctor pre checked separately and outside RAII so not part of this #define.
#ifdef BOOST_CONTRACT_NO_CONSTRUCTORS
    #error "define NO_ENTRY_INVARIANTS, NO_EXIT_INVARIANTS, NO_POSTCONDITIONS, and NO_EXCEPTS instead"
#elif   defined(BOOST_CONTRACT_NO_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS)
    /**
    Defined by this library if constructor contracts are not being checked by
    @RefFunc{boost::contract::constructor}.
    Users can manually program @c \#ifdef statements in their code using this
    macro to completely disable compilation of constructor contracts (not
    recommended).

    This macro is automatically defined by this library, and it is not a
    configuration macro. This library will generate a compile-time error if
    programmers try to manually define this macro. Programmers can manually
    define @RefMacro{BOOST_CONTRACT_NO_ENTRY_INVARIANTS},
    @RefMacro{BOOST_CONTRACT_NO_EXIT_INVARIANTS}, and
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS} instead (constructor
    preconditions are checked separately by
    @RefClass{boost::contract::constructor_precondition} so they are disabled by
    @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS}).
    @see @RefSect{advanced_topics, Advanced Topics}
    */
    #define BOOST_CONTRACT_NO_CONSTRUCTORS
#endif

#ifdef BOOST_CONTRACT_NO_DESTRUCTORS
    #error "define NO_ENTRY_INVARIANTS, NO_EXIT_INVARIANTS, NO_POSTCONDITIONS, and NO_EXCEPTS instead"
#elif   defined(BOOST_CONTRACT_NO_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS)
    /**
    Defined by this library if destructor contracts are not being checked by
    @RefFunc{boost::contract::destructor}.
    Users can manually program @c \#ifdef statements in their code using this
    macro to completely disable compilation of destructor contracts (not
    recommended).

    This macro is automatically defined by this library, and it is not a
    configuration macro. This library will generate a compile-time error if
    programmers try to manually define this macro. Programmers can manually
    define @RefMacro{BOOST_CONTRACT_NO_ENTRY_INVARIANTS},
    @RefMacro{BOOST_CONTRACT_NO_EXIT_INVARIANTS}, and
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS} instead (destructors have no
    preconditions, see also @RefSect{contract_programming_overview, Contract
    Programming Overivew}).
    @see @RefSect{advanced_topics, Advanced Topics}
    */
    #define BOOST_CONTRACT_NO_DESTRUCTORS
#endif

#ifdef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
    #error "define NO_ENTRY_INVARIANTS, NO_PRECONDITIONS, NO_EXIT_INVARIANTS, NO_POSTCONDITIONS, and NO_EXCEPTS instead"
#elif   defined(BOOST_CONTRACT_NO_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_PRECONDITIONS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS)
    /**
    Defined by this library if public function contracts are not being checked
    by @RefFunc{boost::contract::public_function}.
    Users can manually program @c \#ifdef statements in their code using this
    macro to completely disable compilation of public function contracts (not
    recommended).

    This macro is automatically defined by this library, and it is not a
    configuration macro. This library will generate a compile-time error if
    programmers try to manually define this macro. Programmers can manually
    define @RefMacro{BOOST_CONTRACT_NO_ENTRY_INVARIANTS},
    @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS},
    @RefMacro{BOOST_CONTRACT_NO_EXIT_INVARIANTS}, and
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS} instead.
    @see @RefSect{advanced_topics, Advanced Topics}
    */
    #define BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
#endif
    
#ifdef BOOST_CONTRACT_NO_FUNCTIONS
    #error "define NO_PRECONDITIONS, NO_POSTCONDITIONS, and NO_EXCEPTS instead"
#elif   defined(BOOST_CONTRACT_NO_PRECONDITIONS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS)
    /**
    Defined by this library if non-member, private, and protected function
    contracts are not being checked by @RefFunc{boost::contract::function}.
    Users can manually program @c \#ifdef statements in their code using this
    macro to completely disable compilation of non-member, private, and
    protected function contracts (not recommended).

    This macro is automatically defined by this library, and it is not a
    configuration macro. This library will generate a compile-time error if
    programmers try to manually define this macro. Programmers can manually
    define @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS} and
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS} instead (private and protected
    functions do not check class invariants, see also
    @RefSect{contract_programming_overview, Contract Programming Overview}).
    @see @RefSect{advanced_topics, Advanced Topics}
    */
    #define BOOST_CONTRACT_NO_FUNCTIONS
#endif

#ifdef BOOST_CONTRACT_NO_ALL
    #error "define NO_ENTRY_INVARIANTS, NO_PRECONDITIONS, NO_EXIT_INVARIANTS, NO_POSTCONDITIONS, and NO_EXCEPTS instead"
#elif   defined(BOOST_CONTRACT_NO_CONSTRUCTORS) && \
        defined(BOOST_CONTRACT_NO_DESTRUCTORS) && \
        defined(BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS) && \
        defined(BOOST_CONTRACT_NO_FUNCTIONS)
    /**
    Defined by this library if no contracts (for any operation) are being
    checked.
    Users can manually program @c \#ifdef statements in their code using this
    macro to completely disable inclusion of this library headers, etc. (not
    recommended).

    This macro is automatically defined by this library, and it is not a
    configuration macro. This library will generate a compile-time error if
    programmers try to manually define this macro. Programmers can manually
    define @RefMacro{BOOST_CONTRACT_NO_ENTRY_INVARIANTS},
    @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS},
    @RefMacro{BOOST_CONTRACT_NO_EXIT_INVARIANTS}, and
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS} instead.
    @see @RefSect{advanced_topics, Advanced Topics}
    */
    #define BOOST_CONTRACT_NO_ALL
#endif

#ifdef BOOST_CONTRACT_DYN_LINK
    #error "define STATIC_LINK, HEADER_ONLY, or ALL_DYN_LINK instead"
#elif   defined(BOOST_ALL_DYN_LINK) || ( \
        !defined(BOOST_CONTRACT_STATIC_LINK) && \
        !defined(BOOST_CONTRACT_HEADER_ONLY) )
    /**
    Define this macro to compile this library as a shared library or DLL
    (undefined by default).
    In general, this library must be compiled as a shared library (a.k.a.,
    Dynamically Linked Library (DLL)) by defining this macro. That is necessary
    when the same library instance is used by multiple programs (otherwise the
    contracts will not necessarily be checked correctly at run-time).

    @b Rationale: Named after @c BOOST_ALL_DYN_LINK.
    @see @RefSect{getting_started, Getting Started}
    */
    #define BOOST_CONTRACT_DYN_LINK
#endif

#endif // #include guard

