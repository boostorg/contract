
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_LIMITS_HPP_
#define CONTRACT_LIMITS_HPP_

/** @file
@brief Macros reporting bounds of some library constructs (this header is
automatically included by <c>contract.hpp</c>).

These are <em>not</em> configuration macros so programmers cannot change these
values.
These macros are used to inform programmers of bounds on some of this library
constructs.
*/

/**
@brief Upper bound on possible maximum number of postcondition old variables.

The maximum possible number of postcondition old variables is <c>15</c> (the
actual maximum value is controlled by @RefMacro{CONTRACT_CONFIG_OLDOF_MAX}).

For compilers that do not support variadic macros, this is the maximum possible
total number of postcondition statements (total of old variable declarations,
plus return value declaration, plus assertions, etc).

@Note This is not a configuration macro.
The value of this macro is fixed and programmers cannot change it.

@SeeAlso @RefSect{tutorial, Tutorial} section,
@RefSect{no_variadic_macros, No Variadic Macros} section.
*/
#define CONTRACT_LIMIT_OLDOFS 15

/**
@brief Maximum number of select assertions that can be nested into one another.

The maximum number of select assertions that can be nested into one another is
<c>5</c>.

@Note This is not a configuration macro.
The value of this macro is fixed and programmers cannot change it.

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
#define CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS 5

/**
@brief Maximum number of catch statements for a constructor-try block with
member initializers.

The maximum number of catch statements for a constructor-try block with member
initializers is <c>10</c>.
(Constructor-try blocks are specified outside the
@RefMacro{CONTRACT_CONSTRUCTOR} macro when the is no member initializers so
this limit does not apply to that case.)

@Note This is not a configuration macro.
The value of this macro is fixed and programmers cannot change it.

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
#define CONTRACT_LIMIT_CONSTRUCTOR_TRY_BLOCK_CATCHES 10

#endif // #include guard

