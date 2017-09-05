
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_OLDOF_HPP_
#define CONTRACT_OLDOF_HPP_

/** @file
@brief Constructs to declare postcondition old values (this header is
automatically included by <c>contract.hpp</c>).
*/

#include <boost/mpl/bool.hpp>

/**
@brief Macro used to refer to the old value of an expression.

This macro refers the old value of the expression that follows the macro
(i.e., the value the expression had after function entry but before body
execution).
This macro must be used to initialize old value declarations within
postconditions (see also the @RefSect{grammar, Grammar} section):

@code
auto old_variable = CONTRACT_OLDOF odlof_expression
@endcode

The specified expression that follows the macro might or not be wrapped within parenthesis.

The old-of expression type can be explicitly specified instead of <c>auto</c>
but it must be wrapped within parenthesis unless it is a fundamental type
containing no symbol.
If not explicitly specified, the library will automatically deduce the type
using Boost.Typeof (as always, types must be properly registered with
Boost.Typeof for type-of emulation mode on compilers that do not support native
type-of).

@SeeAlso @RefSect{tutorial, Tutorial} section,
@RefSect{advanced_topics, Advanced Topics} section.
*/
// Used to mark start of oldof expression within an oldof assignment
// (unbalanced parenthesis `) ... (` will balance within user code).
#define CONTRACT_OLDOF ) postcondition(CONTRACT_DETAIL_PP_TRAITS_OLDOF

namespace contract {

/**
@brief Trait used to determine if a type can be copied for an old value or not.

A type can be used for a postcondition old value if and only if it can be
copied using the @RefClass{contract::copy} template.
By default, all types that have a constant-correct copy constructor (i.e., that are <c>ConstantCopyConstructible</c>) can be copied by
@RefClass{contract::copy}.

If a type cannot be copied, an old value declaration using such a type will not
fail but it will generate an old value that will cause a compile-time error as
soon as it is used in a contract assertion.
Therefore, this trait can be used to program assertion requirements for those
assertions that use old values on generic types that are not always known to be
copyable.
This way, the assertions will be disabled by the requirement instead of
generating a compile-time error when the old values they use cannot be copied.

@Params
@Param{OldofExpressionType,
The type of the expression specified to the @RefMacro{CONTRACT_OLDOF} macro for
a given postcondition old value declaration.
}
@EndParams

Unfortunately, in C++ it is not possible to portably implement a template
meta-function that checks if a generic type has a constant-correct copy
constructor (or even just a copy constructor).
Therefore, the default implementation of this trait is <c>boost::mpl::true_</c>
for any type <c>OdlofExpressionType</c>.
This will cause compile-time errors for old value types that cannot be copied
in which case users can specialize this unary boolean meta-function to inherit
from <c>boost::mpl::false_</c> for such types.

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
template< typename OldofExpressionType >
struct has_oldof : boost::mpl::true_ {};

} // namespace contract

#endif // #include guard

