// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// CONFIGURE DOXYGEN
// The following Doxygen user defined command must be added to the Doxyfile 
// ALIASES configuration parameter. This is done because Boost Doxygen disables
// some of the Doxygen native similar commands (template/macro parameters,
// @return, @see, @note, etc).
// For example, put following in Boost Jamfile:
//
// <doxygen:param>ALIASES=" Params=\"<b>Parameters:</b> <table border="0">\" Param{2}=\"<tr><td><b><tt>\\1</tt></b></td><td>\\2</td></tr>\" EndParams=\"</table>\" Returns=\"<b>Returns:</b>\" Note=\"<b>Note:</b>\" Warning=\"<b>Warning:</b>\" See=\"<b>See:</b>\" "

/**
@file
Include the entire library.

@code
    #include <contract.hpp>
@endcode

It is recommended to include the library this way instead of including the single header files from the <c>"contract/"</c> directory.

<b>Metaprogramming Symbols</b>

This documentation source code indicates some metaprogramming constructs using special mixed-case symbols prefixed and postfixed by double underscores "__".
These symbols are then expanded to actual code in the documentation text.
For example:
@code
    // Metaprogramming conventions for this documentation.
    __AMetaprogrammingConstruct__
    __AMetaprogrammingConstructWithParameters__< X, Y, Z >
@endcode
In this convention, these metaporgramming constructs are @b not templates.
They are internally implemented by the library using both preprocessor and template metaprogramming (in a way that is intentionally @e not documented here because it is library implementation specific).

@See Getting Started section.
*/

/**
Block invariants (and therefore also loop variants) are compiled and checked at run-time @b only when this macro is \#defined (\#undefined by default).

When this macro is \#undefined, block invariants (and loop variants) are not compiled in the object code and no block invariant (and loop variants) contract overhead is added.

@See Getting Started section for more information.
*/
#define CONTRACT_CHECK_BLOCK_INVARIANT

/**
Class invariants are compiled and checked at run-time @b only when this macro is \#defined (\#undefined by default).

When this macro is \#undefined, class invariants are not compiled in the object code and no class invariant contract overhead is added.

@See Getting Started section for more information.
*/
#define CONTRACT_CHECK_CLASS_INVARIANT

/**
Preconditions are compiled and checked at run-time @b only when this macro is \#defined (\#undefined by default).

When this macro is \#undefined, preconditions are not compiled in the object code and no precondition contract overhead is added.

@See Getting Started section for more information.
*/
#define CONTRACT_CHECK_PRECONDITION

/**
Postconditions are compiled and checked at run-time @b only when this macro is \#defined (\#undefined by default).

When this macro is \#undefined, postconditions are not compiled in the object code and no postcondition contract overhead is added.

@See Getting Started section for more information.
*/
#define CONTRACT_CHECK_POSTCONDITION

