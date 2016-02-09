
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

// TODO: Document in rationale following config macro do not have CONFIG infix to be consistent with convention from other Boost libs (e.g., Boost.Chrono). also following all require re-building this library (THREAD_DISABLE included), while other CONFIG only require re-building user's code.
// BOOST_CONTRACT_DYN_LINK
// BOOST_CONTRACT_HEADER_ONLY
// BOOST_CONTRACT_THREAD_DISABLED

#ifndef BOOST_CONTRACT_CONFIG_MAX_ARGS
#   define BOOST_CONTRACT_CONFIG_MAX_ARGS 10
#endif

#ifndef BOOST_CONTRACT_CONFIG_BASE_TYPES
    #define BOOST_CONTRACT_CONFIG_BASE_TYPES base_types
#endif

#ifndef BOOST_CONTRACT_CONFIG_INVARIANT
    #define BOOST_CONTRACT_CONFIG_INVARIANT invariant
#endif

// C++ does not allow to overload member functions based on static classifier,
// so a name different from the non-static class invariant member must be used.
#ifndef BOOST_CONTRACT_CONFIG_STATIC_INVARIANT
    #define BOOST_CONTRACT_CONFIG_STATIC_INVARIANT static_invariant
#endif

// BOOST_CONTRACT_CONFIG_PERMISSIVE (#undef by default).

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
//  #define BOOST_CONTRACT_CONFIG_ON_MISSING_GUARD { throw my_logic_error(); }
// BOOST_CONTRACT_CONFIG_ON_MISSING_GUARD

// Contract checking is not disable while checking preconditions.
// This is what N1962 does by default. N1962 authors indicated it can be shown
// that unchecked arguments are passed to function bodies if contract checking
// is disable within precondition checking).
// However, not disabling contract checking while checking preconditions can
// lead to infinite recursive call in user code so by default this macro is
// not defined.
// BOOST_CONTRACT_CONFIG_PRECONDITIONS_DISABLE_NOTHING

// BOOST_CONTRACT_CONFIG_NO_PRECONDITIONS
// BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
// BOOST_CONTRACT_CONFIG_NO_ENTRY_INVARIANTS
// BOOST_CONTRACT_CONFIG_NO_EXIT_INVARIANTS
// BOOST_CONTRACT_CONFIG_NO_INVARIANTS

// Following are NOT configuration macros.

#if defined(BOOST_CONTRACT_PRECONDITIONS)
    #error "define/undef ..._CONFIG_NO_PRECONDITIONS instead"
#elif defined(BOOST_CONTRACT_CONFIG_NO_PRECONDITIONS)
    #define BOOST_CONTRACT_PRECONDITIONS 0
#else
    #define BOOST_CONTRACT_PRECONDITIONS 1
#endif

#if defined(BOOST_CONTRACT_POSTCONDITIONS)
    #error "define/undef ..._CONFIG_NO_POSTCONDITIONS instead"
#elif defined(BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS)
    #define BOOST_CONTRACT_POSTCONDITIONS 0
#else
    #define BOOST_CONTRACT_POSTCONDITIONS 1
#endif

#if defined(BOOST_CONTRACT_ENTRY_INVARIANTS)
    #error "define/undef ..._CONFIG_NO[_ENTRY]_INVARIANTS instead"
#elif defined(BOOST_CONTRACT_CONFIG_NO_ENTRY_INVARIANTS) || \
        defined (BOOST_CONTRACT_CONFIG_NO_INVARIANTS)
    #define BOOST_CONTRACT_ENTRY_INVARIANTS 0
#else
    #define BOOST_CONTRACT_ENTRY_INVARIANTS 1
#endif

#if defined(BOOST_CONTRACT_EXIT_INVARIANTS)
    #error "define/undef ..._CONFIG_NO[_EXIT]_INVARIANTS instead"
#elif defined(BOOST_CONTRACT_CONFIG_NO_EXIT_INVARIANTS) || \
        defined (BOOST_CONTRACT_CONFIG_NO_INVARIANTS)
    #define BOOST_CONTRACT_EXIT_INVARIANTS 0
#else
    #define BOOST_CONTRACT_EXIT_INVARIANTS 1
#endif

#if defined(BOOST_CONTRACT_INVARIANTS)
    #error "define/undef ..._CONFIG_NO[_ENTRY|_EXIT]_INVARIANTS instead"
#elif BOOST_CONTRACT_NO_ENTRY_INVARIANTS && BOOST_CONTRACT_NO_EXIT_INVARIANTS
    #define BOOST_CONTRACT_INVARIANTS 0
#else
    #define BOOST_CONTRACT_INVARIANTS 1
#endif

#if defined(BOOST_CONTRACT_FUNCTIONS)
    #error "define/undef ..._CONFIG_NO_... instead"
#elif !BOOST_CONTRACT_PRECONDITIONS && !BOOST_CONTRACT_POSTCONDITIONS
    #define BOOST_CONTRACT_FUNCTIONS 0
#else
    #define BOOST_CONTRACT_FUNCTIONS 1
#endif

#if defined(BOOST_CONTRACT_CONSTRUCTORS)
    #error "define/undef ..._CONFIG_NO_... instead"
// Ctor pre checked separately and outside guard so not part of this if cond.
#elif !BOOST_CONTRACT_POSTCONDITIONS && !BOOST_CONTRACT_INVARIANTS
    #define BOOST_CONTRACT_CONSTRUCTORS 0
#else
    #define BOOST_CONTRACT_CONSTRUCTORS 1
#endif

#if defined(BOOST_CONTRACT_DESTRUCTORS)
    #error "define/undef ..._CONFIG_NO_... instead"
#elif !BOOST_CONTRACT_POSTCONDITIONS && !BOOST_CONTRACT_INVARIANTS
    #define BOOST_CONTRACT_DESTRUCTORS 0
#else
    #define BOOST_CONTRACT_DESTRUCTORS 1
#endif

#if defined(BOOST_CONTRACT_PUBLIC_FUNCTIONS)
    #error "define/undef ..._CONFIG_NO_... instead"
#elif !BOOST_CONTRACT_PRECONDITONS && !BOOST_CONTRACT_POSTCONDITIONS && \
        !BOOST_CONTRACT_INVARIANTS
    #define BOOST_CONTRACT_PUBLIC_FUNCTIONS 0
#else
    #define BOOST_CONTRACT_PUBLIC_FUNCTIONS 1
#endif

#if defined(BOOST_CONTRACT_CLASSES)
    #error "define/undef ..._CONFIG_NO_... instead"
#elif !BOOST_CONTRACT_CONSTRUCTORS && !BOOST_CONTRACT_DESTRUCTORS && \
        !BOOST_CONTRACT_PUBLIC_FUNCTIONS
    #define BOOST_CONTRACT_CLASSES 0
#else
    #define BOOST_CONTRACT_CLASSES 1
#endif

#endif // #include guard

