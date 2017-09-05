
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_CONFIG_HPP_
#define CONTRACT_CONFIG_HPP_

/** @file
@brief Macros used to configure the library behaviour at compile-time (this
header is automatically included by <c>contract.hpp</c>).

These configuration macros have appropriate default values if left undefined.
Programmers can define these macros before including any of the library headers
(using compiler options like <c>-D</c> for GCC, <c>/D</c> for MSVC, etc) in
order to change the library behaviour.

The macros @RefMacro{CONTRACT_CONFIG_NO_PRECONDITIONS},
@RefMacro{CONTRACT_CONFIG_NO_POSTCONDITIONS}, etc can be defined to selectively
disable compilation and run-time checking of all preconditions, postconditions,
etc.
This is a common practice in Contract Programming to generate debug and release
builds with less correctness checks but faster run-times.
Note that all contracts are compiled and checked at run-time by default unless
specified otherwise using these configuration macros.

@SeeAlso @RefSect{getting_started, Getting Started} section,
@RefSect{contract_programming_overview, Contract Programming Overview} section.
*/

#include <contract/limits.hpp>

// All these macros are undefined by default (unless generating Doxygen docs).
// Virtual specifiers (final, override, and new) are enabled iff contracts
// (pre, post, or inv) are enabled.
#ifdef DOXYGEN

/**
@brief Disable compilation and run-time checking of all preconditions.

Preconditions are not checked at run-time and not even compiled when
programmers define this macro.
This can be used to speed up execution and compilation of debug and release
builds at different stages of development and testing as it is common practise
in Contract Programming.

@Note Assertion requirements can be used to selectively disable single
assertions (see the @RefSect{advanced_topics, Advanced Topics} section).

@SeeAlso @RefSect{getting_started, Getting Started} section.
*/
#define CONTRACT_CONFIG_NO_PRECONDITIONS

/**
@brief Disable compilation and run-time checking of all postconditions.

Postconditions are not checked at run-time and not even compiled when
programmers define this macro.
This can be used to speed up execution and compilation of debug and release
builds at different stages of development and testing as it is common practise
in Contract Programming.

@Note Assertion requirements can be used to selectively disable single
assertions (see the @RefSect{advanced_topics, Advanced Topics} section).

@SeeAlso @RefSect{getting_started, Getting Started} section.
*/
#define CONTRACT_CONFIG_NO_POSTCONDITIONS

/**
@brief Disable compilation and run-time checking of all class invariants.

Class invariants are not checked at run-time and not even compiled when
programmers define this macro.
This can be used to speed up execution and compilation of debug and release
builds at different stages of development and testing as it is common practise
in Contract Programming.

@Note Assertion requirements can be used to selectively disable single
assertions (see the @RefSect{advanced_topics, Advanced Topics} section).

@SeeAlso @RefSect{getting_started, Getting Started} section.
*/
#define CONTRACT_CONFIG_NO_CLASS_INVARIANTS

/**
@brief Disable compilation and run-time checking of all block invariants.

Block invariants are not checked at run-time and not even compiled when
programmers define this macro.
This can be used to speed up execution and compilation of debug and release
builds at different stages of development and testing as it is common practise
in Contract Programming.

@Note Assertion requirements can be used to selectively disable single
assertions (see the @RefSect{advanced_topics, Advanced Topics} section).

@SeeAlso @RefSect{getting_started, Getting Started} section.
*/
#define CONTRACT_CONFIG_NO_BLOCK_INVARIANTS

/**
@brief Disable compilation and run-time checking of all loop variants.

Loop variants are not checked at run-time and not even compiled when
programmers define this macro.
This can be used to speed up execution and compilation of debug and release
builds at different stages of development and testing as it is common practise
in Contract Programming.

@Note Assertion requirements can be used to selectively disable single
assertions (see the @RefSect{advanced_topics, Advanced Topics} section).

@SeeAlso @RefSect{getting_started, Getting Started} section.
*/
#define CONTRACT_CONFIG_NO_LOOP_VARIANTS

#endif // DOXYGEN

/**
@brief Specify the maximum number of supported function parameters.

This macro automatically defaults to <c>5</c> if left undefined by programmers.
This macro must be a non-negative integral number.
Increasing the value specified by this macro might increase compilation time.

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#ifndef CONTRACT_CONFIG_FUNCTION_ARITY_MAX
#   define CONTRACT_CONFIG_FUNCTION_ARITY_MAX 5
#endif

/**
@brief Specify the maximum number of base classes supported for
multiple-inheritance.

This macro automatically defaults to <c>4</c> if left undefined by programmers.
This macro must be a non-negative integral number.
Increasing the value specified by this macro might increase compilation time.

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#ifndef CONTRACT_CONFIG_INHERITANCE_MAX
#   define CONTRACT_CONFIG_INHERITANCE_MAX 4
#endif

/**
@brief Specify the maximum number of supported old value declarations in
postconditions.

This macro automatically defaults to <c>5</c> if left undefined by programmers.
This macro must be a non-negative integral number smaller or equal to
@RefMacro{CONTRACT_LIMIT_OLDOFS}.
Increasing the value specified by this macro might increase compilation time.

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#ifndef CONTRACT_CONFIG_OLDOF_MAX
#   define CONTRACT_CONFIG_OLDOF_MAX 5
#endif
#if CONTRACT_CONFIG_OLDOF_MAX > CONTRACT_LIMIT_OLDOFS
#   error "CONTRACT_CONFIG_OLDOF_MAX cannot exceed CONTRACT_LIMIT_OLDOFS"
#endif

/**
@brief Specify the maximum supported array dimension for multi-dimensional
arrays.

This macro automatically defaults to <c>3</c> if left undefined by programmers
(therefore, by default up to 3-dimensional arrays <c>x[]</c>, <c>x[][]</c>, and
<c>x[][][]</c> can be passed to functions declared using this library, but
always using an extra <c>typedef</c> as specified by the
@RefSect{tutorial, Tutorial} section).
This macro must be a non-negative integral number.
Increasing the value specified by this macro might increase compilation time.

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#ifndef CONTRACT_CONFIG_ARRAY_DIMENSION_MAX
#   define CONTRACT_CONFIG_ARRAY_DIMENSION_MAX 3
#endif

#ifdef DOXYGEN

/**
@brief Do not allow overriding functions to specify preconditions.

If programmers define this macro, the library will generate a compile-time
error if overriding functions specify preconditions.
Therefore, preconditions can only be specified by functions at the very root of
the inheritance tree and they cannot be subcontracted (this is as specified by
@RefSect{bibliography, [N1962]}, however note that in case of
multiple-inheritance the preconditions of all base functions will still be
checked in logic-or with each other effectively still allowing a base class to
weaken the preconditions from another base class).

By default, this library allows to subcontract preconditions.

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
#define CONTRACT_CONFIG_DO_NOT_SUBCONTRACT_PRECONDITIONS

/**
@brief Specify that no assertion should be disabled while checking
preconditions.

Assertion checking is disabled within assertions in order to avoid infinite
recursion and that is a standard requirement of Contract Programming.
However, if programmers define this macro then no assertion checking is
disabled within preconditions (this is as specified by
@RefSect{bibliography, [N1962]}).
Assertion checking within assertion checking will still be disabled for
postconditions, class invariants, etc.

By default, this library disables assertion checking within assertions for all
contracts, including preconditions.

@SeeAlso @RefSect{contract_programming_overview, Contract Programming Overview}
section.
*/
#define CONTRACT_CONFIG_PRECONDITIONS_DISABLE_NO_ASSERTION

/**
@brief Report precondition that failed in the overridden function (instead of
the precondition failed in the overriding function).

Subcontracted preconditions fail only when the preconditions of the overriding
function fail together with the overridden preconditions from all the base
classes.
By default the assertion that failed in the overriding function is reported.
If programmes define this macro then the library will instead the report the
assertion that failed in the overridden function from within one of the base
classes.

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
#define CONTRACT_CONFIG_REPORT_BASE_PRECONDITION_FAILURE

/**
@brief Make the implementation of this library thread-safe.

In order to globally disable assertion checking within assertions, this library
internally has to use a global variable.
If programmers defined this macro, such a variable will be automatically locked
to avoid race conditions (this effectively introduces a global lock in the
program).

@SeeAlso @RefSect{contract_programming_overview, Contract Programming Overview}
section.
*/
#define CONTRACT_CONFIG_THREAD_SAFE

#endif // DOXYGEN

#endif // #include guard

