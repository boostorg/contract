
#ifndef BOOST_CONTRACT_CONFIG_HPP_
#define BOOST_CONTRACT_CONFIG_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file */

// IMPORTANT: This header MUST NOT #include any other header of this lib.
// That way users can #include this header and not #include any of this lib
// headers after that depending on the contract 0/1 macros below ensuring no
// compilation overhead.

// TODO: Document that when contracts are programmed in .cpp and all these lib headers are #include only from within .cpp, then a given lib can be compiled for example without inv/post, only with pre. The code that will link to that lib will not be able to enable inv/post, or disable the pre. However, if contracts are programmed in .hpp and this lib headers are #included in .hpp that are shipped to users with a given lib, users of that lib can turn on/off all contracts for the shipped lib as well.

// BOOST_CONTRACT_DYN_LINK
// BOOST_CONTRACT_HEADER_ONLY

// Rationale: Named after BOOST_DISABLE_THREADS, BOOST_ASIO_DISABLE_THREADS, etc.
// BOOST_CONTRACT_DISABLE_THREADS

// Rationale: Named after BOOST_FUNCTION_MAX_ARGS, etc.
#ifndef BOOST_CONTRACT_MAX_ARGS
#   define BOOST_CONTRACT_MAX_ARGS 10
#endif

// Rationale: This cannot be called BASE_TYPES because BASE_TYPES(...) is already used as the macro to extract the public bases... so BASE_TYPEDEF seemed a reasonable naming alternative, but don't change base_types default #define because `typedef BASE_TYPES(...) base_types` is usually the best syntax in user's code.
#ifndef BOOST_CONTRACT_BASE_TYPEDEF
    #define BOOST_CONTRACT_BASE_TYPEDEF base_types
#endif

#ifndef BOOST_CONTRACT_INVARIANT
    #define BOOST_CONTRACT_INVARIANT invariant
#endif

// C++ does not allow to overload member functions based on static classifier,
// so a name different from the non-static class invariant member must be used.
#ifndef BOOST_CONTRACT_STATIC_INVARIANT
    #define BOOST_CONTRACT_STATIC_INVARIANT static_invariant
#endif

// BOOST_CONTRACT_PERMISSIVE

// Type of exception to throw is `guard c = ...` is missing. This is a
// programming error so by default this library calls abort. If this macro is
// #defined however, this library will throw the exception specified by the
// macro value instead of calling abort. When #defined, this macro must be a
// default constructible type.
// Code instruction(s) to execute when contracts are missing `guard c = ...`.
// In general, this is #undefined and this library calls `assert(false)` when
// contract guards are missing. Missing a contract guard is a logic error in
// the program (similar to dereferencing a null pointer) so terminating the
// program via `abort` or `assert` as this library does by default is the only
// safe thing to do. Therefore, it is recommended to never #define this macro.
// However, this macro can be defined to throw an exception, call a function,
// a no-op, or any other user code in case users truly need to handle missing
// contract guard logic errors without terminating the program, for example:
//  #define BOOST_CONTRACT_ON_MISSING_GUARD { throw my_logic_error(); }
// (It can even be defined to expand to nothing.)
// BOOST_CONTRACT_ON_MISSING_GUARD

// Contract checking is not disable while checking preconditions.
// This is what N1962 does by default. N1962 authors indicated it can be shown
// that unchecked arguments are passed to function bodies if contract checking
// is disable within precondition checking).
// However, not disabling contract checking while checking preconditions can
// lead to infinite recursive call in user code so by default this macro is
// not defined.
// TODO: Rename this BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTIONS
// BOOST_CONTRACT_PRECONDITIONS_DISABLE_NOTHING

// BOOST_CONTRACT_NO_PRECONDITIONS
// BOOST_CONTRACT_NO_POSTCONDITIONS

#if !defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_INVARIANTS)
    #define BOOST_CONTRACT_NO_ENTRY_INVARIANTS
#endif

#if !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_INVARIANTS)
    #define BOOST_CONTRACT_NO_EXIT_INVARIANTS
#endif

#if !defined(BOOST_CONTRACT_NO_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS)
    #define BOOST_CONTRACT_NO_INVARIANTS
#endif

// Following are NOT configuration macros.

// Ctor pre checked separately and outside guard so not part of this #define.
#ifdef BOOST_CONTRACT_NO_CONSTRUCTORS
    #error "define NO_ENTRY_INVARIANTS, NO_EXIT_INVARIANTS, and NO_POSTCONDITIONS instead"
#elif defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_INVARIANTS)
    #define BOOST_CONTRACT_NO_CONSTRUCTORS
#endif

#ifdef BOOST_CONTRACT_NO_DESTRUCTORS
    #error "define NO_ENTRY_INVARIANTS, NO_EXIT_INVARIANTS, and NO_POSTCONDITIONS instead"
#elif defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_INVARIANTS)
    #define BOOST_CONTRACT_NO_DESTRUCTORS
#endif

#ifdef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
    #error "define NO_ENTRY_INVARIANTS, NO_PRECONDITIONS, NO_EXIT_INVARIANTS, and NO_POSTCONDITIONS instead"
#elif defined(BOOST_CONTRACT_NO_PRECONDITIONS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_INVARIANTS)
    #define BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
#endif
    
#ifdef BOOST_CONTRACT_NO_FUNCTIONS
    #error "define NO_PRECONDITIONS and NO_POSTCONDITIONS instead"
#elif defined(BOOST_CONTRACT_NO_PRECONDITIONS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
    #define BOOST_CONTRACT_NO_FUNCTIONS
#endif

#ifdef BOOST_CONTRACT_NO_ALL
    #error "define NO_ENTRY_INVARIANTS, NO_PRECONDITIONS, NO_EXIT_INVARIANTS, and NO_POSTCONDITIONS instead"
#elif defined(BOOST_CONTRACT_NO_CONSTRUCTORS) && \
        defined(BOOST_CONTRACT_NO_DESTRUCTORS) && \
        defined(BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS) && \
        defined(BOOST_CONTRACT_NO_FUNCTIONS)
    #define BOOST_CONTRACT_NO_ALL
#endif

#endif // #include guard

