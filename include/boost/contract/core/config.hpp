
#ifndef BOOST_CONTRACT_CONFIG_HPP_
#define BOOST_CONTRACT_CONFIG_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Configuration macros.
*/

// IMPORTANT: This header MUST NOT #include any other header of this lib.
// That way users can #include this header and not #include any of this lib
// headers after that depending on the contract 0/1 macros below ensuring no
// compilation overhead.

// TODO: Document that when contracts are programmed in .cpp and all these lib headers are #include only from within .cpp, then a given lib can be compiled for example without inv/post, only with pre. The code that will link to that lib will not be able to enable inv/post, or disable the pre. However, if contracts are programmed in .hpp and this lib headers are #included in .hpp that are shipped to users with a given lib, users of that lib can turn on/off all contracts for the shipped lib as well.

#ifdef DOXYGEN
    /**
    Define this macro to compile this library as a shared library or DLL
    (undefined by default).
    In general, this library must be compiled as a shared library defining this
    macro when used by multiple programs otherwise the contracts will not
    necessarily be checked correctly at run-time.
    <b>Rationale:</b> Named after @c BOOST_ALL_DYN_LINK.
    @see @RefSect{getting_started, Getting Started}.
    */
    #define BOOST_CONTRACT_DYN_LINK
#endif

#ifdef DOXYGEN
    /**
    Define this macro to compile user code with this library composed of headers
    only (undefined by default).
    If this macro is defined, this library does not have to be compiled
    separately. This library headers can simply be included in the user program
    and this library code will be compiled directly as part of the user program.
    However, in general this library must be compiled as a shared library
    defining @RefMacro{BOOST_CONTRACT_DYN_LINK} when used by multiple programs
    otherwise the contracts will not necessarily be checked correctly at
    run-time.
    <b>Rationale:</b> Named after @c BOOST_CHRONO_HEADER_ONLY.
    @see @RefSect{getting_started, Getting Started}.
    */
    #define BOOST_CONTRACT_HEADER_ONLY
#endif

#ifdef DOXYGEN
    /**
    Define this macro to not lock internal library data for thread safety
    (undefined by default).
    Defining this macro will make the library implementation code not thread
    safe so this macro should not be defined unless the library is being used
    strictly under single-threaded applications. However, when this macro is
    left undefined this library needs to use "global" locks to ensure contract
    checking is globally disabled when other contracts are being checked and
    also to safely access the failure handler functors (this could introduce a
    significant amount of synchronization in multi-threaded applications).
    <b>Rationale:</b>   Named after @c BOOST_DISABLE_THREADS,
                        @c BOOST_ASIO_DISABLE_THREADS, etc.
    @see @RefSect{contract_programming_overview, Contract Programming Overview}.
    */
    #define BOOST_CONTRACT_DISABLE_THREADS
#endif

#ifndef BOOST_CONTRACT_MAX_ARGS
    /**
    Maximum number of function arguments when no variadic macros are supported
    (default to @c 10).
    This defines the maximum number of arguments of the overriding public
    function pointer passed to @RefFunc{boost::contract::public_function} on
    compilers that do not support variadic macros. This macro has no effect on
    compilers that support variadic macros.
    @note   Regardless of the value of this macro and of compiler support for
            variadic macros, there is an intrinsic limit around 19 arguments
            for overriding public functions (because of a similar limit of some
            Boost libraries like Boost.MPL and Boost.FunctionTypes internally
            used by this library).

    <b>Rationale:</b> Named after @c BOOST_FUNCTION_MAX_ARGS, etc.
    */
    #define BOOST_CONTRACT_MAX_ARGS 10
#endif

#ifndef BOOST_CONTRACT_BASE_TYPEDEF
    /**
    Define the name of the base type @c typedef (@c base_types by default).
    <b>Rationale:</b>   This cannot be called @c BOOST_CONTRACT_BASE_TYPES
                        because that is already used as the name of macro to
                        extract the public bases. Then
                        @c BOOST_CONTRACT_BASE_TYPEDEF is a reasonable naming
                        alternative (but without changing this macro default to
                        @c base_typedef because
                        <c>typedef BOOST_CONTRACT_BASE_TYPES(...) base_types</c>
                        is the preferred syntax in user code).
    */
    #define BOOST_CONTRACT_BASE_TYPEDEF base_types
#endif

#ifndef BOOST_CONTRACT_INVARIANT
    /**
    Define the name of the @c const and <c>const volatile</c> member functions
    that checks mutable and volatile class invariants respectively (@c invariant
    by default).
    */
    #define BOOST_CONTRACT_INVARIANT invariant
#endif

#ifndef BOOST_CONTRACT_STATIC_INVARIANT
    /**
    Define the name of the @c static member function that checks static class
    invariants (@c static_invariant by default).
    @note   C++ does not allow to overload member functions based on static
            classifier, so a name different from the non-static class invariant
            name expanded by @RefMacro{BOOST_CONTRACT_INVARIANT} must be used
            here.
    */
    #define BOOST_CONTRACT_STATIC_INVARIANT static_invariant
#endif

#ifdef DOXYGEN
    /**
    Disable a number of static checks and compiler warnings generated by this
    library (undefined by default).
    Among other things, this macro checks:
    @li Static invariant member function is @c static.
    @li Non-static invariant member function is either @c const,
        <c>const volatile</c>, or <c>volatile const</c>.
    @li A class that has contracts for one or more overriding public functions
        must also define the @RefMacro{BOOST_CONTRACT_BASE_TYPES} @c typedef.
    */
    #define BOOST_CONTRACT_PERMISSIVE
#endif

#ifdef DOXYGEN
    /**
    Code block to execute if <c>boost::contract::guard c = ...</c> assignment is
    missing (undefined by default).
    In general, if programmer omit this assignment, it is a logic error in the
    program. Therefore, when this macro is not defined, by default this library
    calls calls @c assert with a @c false condition. If this macro is defined,
    this library will execute the code expanded by this macro instead of calling
    @c assert.
    */
    #define OOST_CONTRACT_ON_MISSING_GUARD
#endif

#ifdef DOXYGEN
    /**
    If defined, checking preconditions does not disable checking of other
    assertions (undefined by default).
    This is what [N1962] does by default because unchecked arguments are passed
    to function bodies if contract checking is disable within precondition
    checking (function bodies need to be executed directly or indirectly while
    checking the preconditions in question). However, not disabling assertion
    checking while checking preconditions can lead to infinite recursive calls
    in user code so by default this macro is not defined.
    */
    #define OOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION
#endif

#ifdef DOXYGEN
    /**
    If defined, this library does not check preconditions at run-time (undefined
    by default).
    This library implementation code is also optimized to avoid overhead in
    associated with precondition checking when possible also at compile-time.
    Users can manually program @c #ifdef statements using this macro to disable
    precondition compilation (not just run-time checking).
    @see @RefSect{advanced_topics, Advanced Topics}.
    */
    #define BOOST_CONTRACT_NO_PRECONDITIONS
#endif

#ifdef DOXYGEN
    /**
    If defined, this library does not check postconditions at run-time
    (undefined by default).
    This library implementation code is also optimized to avoid overhead in
    associated with postcondition checking when possible also at compile-time.
    Users can manually program @c #ifdef statements using this macro to disable
    postcondition compilation (not just run-time checking).
    @see @RefSect{advanced_topics, Advanced Topics}.
    */
    #define BOOST_CONTRACT_NO_POSTCONDITIONS
#endif

#if defined(DOXYGEN) || (!defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_INVARIANTS))
    /**
    If defined, this library does not check entry invariants at run-time
    (undefined by default).
    This library implementation code is also optimized to avoid overhead in
    associated with entry invariant checking when possible also at compile-time.
    Users can manually program @c #ifdef statements using this macro to disable
    class invariant compilation (not just run-time checking).

    This macro can always be defined by itself but it is also automatically
    defined when @RefMacro{BOOST_CONTRACT_NO_INVARIANTS} is defined.

    @see @RefSect{advanced_topics, Advanced Topics}.
    */
    #define BOOST_CONTRACT_NO_ENTRY_INVARIANTS
#endif

#if defined(DOXYGEN) || (!defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_INVARIANTS))
    /**
    If defined, this library does not check exit invariant at run-time
    (undefined by default).
    This library implementation code is also optimized to avoid overhead in
    associated with exit invariant checking when possible also at compile-time.
    Users can manually program @c #ifdef statements using this macro to disable
    class invariant compilation (not just run-time checking).

    This macro can always be defined by itself but it is also automatically
    defined when @RefMacro{BOOST_CONTRACT_NO_INVARIANTS} is defined.

    @see @RefSect{advanced_topics, Advanced Topics}.
    */
    #define BOOST_CONTRACT_NO_EXIT_INVARIANTS
#endif

#if !defined(BOOST_CONTRACT_NO_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS)
    /**
    If defined, this library does not check class invariants at run-time
    (undefined by default).
    This library implementation code is also optimized to avoid overhead in
    associated with class invariant checking when possible also at compile-time.
    Users can manually program @c #ifdef statements using this macro to disable
    class invariant compilation (not just run-time checking).

    This macro can always be defined by itself but it is also automatically
    defined when @RefMacro{BOOST_CONTRACT_NO_ENTRY_INVARIANTS} and
    @RefMacro{BOOST_CONTRACT_NO_EXIT_INVARIANTS} are both defined.

    @see @RefSect{advanced_topics, Advanced Topics}.
    */
    #define BOOST_CONTRACT_NO_INVARIANTS
#endif

// Following are NOT configuration macros.

// Ctor pre checked separately and outside guard so not part of this #define.
#ifdef BOOST_CONTRACT_NO_CONSTRUCTORS
    #error "define NO_ENTRY_INVARIANTS, NO_EXIT_INVARIANTS, and NO_POSTCONDITIONS instead"
#elif defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_INVARIANTS)
    /**
    This library defines this macro if constructor contracts are not being
    checked by @RefFunc{boost::contract::constructor}.
    This macro is automatically defined or not by this library, and it is not a
    configuration macro. This library will generate a compile-time error if
    users manually define this macro.
    Users can manually define @RefMacro{BOOST_CONTRACT_NO_ENTRY_INVARIANTS},
    @RefMacro{BOOST_CONTRACT_NO_EXIT_INVARIANTS}, and
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS} instead.
    
    Note that constructor preconditions are checked separately by
    @RefClass{boost::contract::constructor_precondition} so their run-time check
    ing is disabled by @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS} directly.
    @see @RefSect{advanced_topics, Advanced Topics}.
    */
    #define BOOST_CONTRACT_NO_CONSTRUCTORS
#endif

#ifdef BOOST_CONTRACT_NO_DESTRUCTORS
    #error "define NO_ENTRY_INVARIANTS, NO_EXIT_INVARIANTS, and NO_POSTCONDITIONS instead"
#elif defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_INVARIANTS)
    /**
    This library defines this macro if destructor contracts are not being
    checked by @RefFunc{boost::contract::destructor}.
    This macro is automatically defined or not by this library, and it is not a
    configuration macro. This library will generate a compile-time error if
    users manually define this macro.
    Users can manually define @RefMacro{BOOST_CONTRACT_NO_ENTRY_INVARIANTS},
    @RefMacro{BOOST_CONTRACT_NO_EXIT_INVARIANTS}, and
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS} instead.
    (Note that destructors have no preconditions.)
    @see @RefSect{advanced_topics, Advanced Topics}.
    */
    #define BOOST_CONTRACT_NO_DESTRUCTORS
#endif

#ifdef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
    #error "define NO_ENTRY_INVARIANTS, NO_PRECONDITIONS, NO_EXIT_INVARIANTS, and NO_POSTCONDITIONS instead"
#elif defined(BOOST_CONTRACT_NO_PRECONDITIONS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_INVARIANTS)
    /**
    This library defines this macro if public function contracts are not being
    checked by @RefFunc{boost::contract::public_function}.
    This macro is automatically defined or not by this library, and it is not a
    configuration macro. This library will generate a compile-time error if
    users manually define this macro.
    Users can manually define @RefMacro{BOOST_CONTRACT_NO_ENTRY_INVARIANTS},
    @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS},
    @RefMacro{BOOST_CONTRACT_NO_EXIT_INVARIANTS}, and
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS} instead.
    @see @RefSect{advanced_topics, Advanced Topics}.
    */
    #define BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
#endif
    
#ifdef BOOST_CONTRACT_NO_FUNCTIONS
    #error "define NO_PRECONDITIONS and NO_POSTCONDITIONS instead"
#elif defined(BOOST_CONTRACT_NO_PRECONDITIONS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
    /**
    This library defines this macro if non-member, private, or protected
    function contracts are not being checked by
    @RefFunc{boost::contract::function}.
    This macro is automatically defined or not by this library, and it is not a
    configuration macro. This library will generate a compile-time error if
    users manually define this macro.
    Users can manually define @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS} and
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS} instead.
    @see @RefSect{advanced_topics, Advanced Topics}.
    */
    #define BOOST_CONTRACT_NO_FUNCTIONS
#endif

#ifdef BOOST_CONTRACT_NO_ALL
    #error "define NO_ENTRY_INVARIANTS, NO_PRECONDITIONS, NO_EXIT_INVARIANTS, and NO_POSTCONDITIONS instead"
#elif defined(BOOST_CONTRACT_NO_CONSTRUCTORS) && \
        defined(BOOST_CONTRACT_NO_DESTRUCTORS) && \
        defined(BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS) && \
        defined(BOOST_CONTRACT_NO_FUNCTIONS)
    /**
    This library defines this macro if no contracts (for any operation) are
    being checked.
    This macro is automatically defined or not by this library, and it is not a
    configuration macro. This library will generate a compile-time error if
    users manually define this macro.
    Users can manually define @RefMacro{BOOST_CONTRACT_NO_ENTRY_INVARIANTS},
    @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS},
    @RefMacro{BOOST_CONTRACT_NO_EXIT_INVARIANTS}, and
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS} instead.
    @see @RefSect{advanced_topics, Advanced Topics}.
    */
    #define BOOST_CONTRACT_NO_ALL
#endif

#endif // #include guard

