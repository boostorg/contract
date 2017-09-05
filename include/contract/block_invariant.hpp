
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_BLOCK_INVARIANT_HPP_
#define CONTRACT_BLOCK_INVARIANT_HPP_

/** @file
@brief Macros used to specify block invariants (this header is automatically
included by <c>contract.hpp</c>).
*/

#include <contract/aux_/macro/block_invariant.hpp>
#include <contract/detail/preprocessor/variadic/to_seq.hpp>
#include <boost/local_function/detail/preprocessor/line_counter.hpp>
#include <boost/config.hpp>

#ifndef DOXYGEN

#ifndef BOOST_NO_VARIADIC_MACROS

#define CONTRACT_BLOCK_INVARIANT(...) \
    CONTRACT_AUX_BLOCK_INVARIANT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            0, /* outside template */ \
            CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ( \
                    (ERROR_block_invariants_cannot_be_empty), __VA_ARGS__))

#define CONTRACT_BLOCK_INVARIANT_TPL(...) \
    CONTRACT_AUX_BLOCK_INVARIANT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            1, /* inside template */ \
            CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ( \
                    (ERROR_block_invariants_cannot_be_empty), __VA_ARGS__))

#else

#define CONTRACT_BLOCK_INVARIANT(seq) \
    CONTRACT_AUX_BLOCK_INVARIANT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            0, /* outside template */ \
            seq)

#define CONTRACT_BLOCK_INVARIANT_TPL(seq) \
    CONTRACT_AUX_BLOCK_INVARIANT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            1, /* inside template */ \
            seq)

#endif

#else

/**
@brief Macro used to specify block invariants.

This macro can appear at any point in a code block within a function definition
and it is used to assert correctness condition of the implementation (similarly
to C++ <c>assert</c>).

@Params
@Param{assertions,
The syntax for the assertions is explained in the @RefSect{grammar\, Grammar}
section.
Static assertions\, constant assertions\, and select assertions can be used.
}
@EndParams

Within a type-dependent scope (e.g., within templates),
@RefMacro{CONTRACT_BLOCK_INVARIANT_TPL} must be used instead of this macro.

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
#define CONTRACT_BLOCK_INVARIANT(assertions)

/**
@brief Macro used to specify block invariants within a type-dependent scope
(e.g., within templates).

This macro is the exact same as @RefMacro{CONTRACT_BLOCK_INVARIANT} but is must
be used when specifying block invariants within a type-dependent scope.

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
#define CONTRACT_BLOCK_INVARIANT_TPL(assertions)

#endif

#endif // #include guard

