// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

/** @file
Utilities to pass commas within macro parameters.
*/

/**
Macro used to pass type expressions with unwrapped commas as macro parameters.

The C++ ISO standard preprocessor only recognizes the parenthesis @c () and it does not recognize any other parenthesis like @c <>, @c {}, @c [], etc.

As a consequence, any comma within a macro parameter which is not wrapped by the @c () parenthesis will be interpreted by the preprocessor as a separation token (the end of the current macro parameter and the start of the next macro parameter).
See also the Tutorial section for more explanation and examples.

<b>Value Expressions</b>

Value expressions passed as macro parameters and containing unwrapped commas can be wrapped by and extra set of parenthesis @c ().

For example, this is OK because the comma `<c>,</c>` is already wrapped by the parenthesis @c () of the @c add() function call:
@code
    CONTRACT_ASSERT( add(1, 2) == 3 ); // OK.
@endcode
This is incorrect instead because the comma `<c>,</c>` is not wrapped.
It is interpreted as a call to @c CONTRACT_ASSERT() passing @b two distinct macro parameters `<c>std::map<double</c>` and `<c>int>().empty()</c>` separated by the comma `<c>,</c>`:
@code
    CONTRACT_ASSERT( std::map<double, int>().empty() ); // Error.
@endcode
However, it can be fixed by using and extra set of parenthesis to wrap the value expression:
@code
    CONTRACT_ASSERT( (std::map<double, int>().empty()) ); // OK.
@endcode

<b>Type Expressions</b>

A similar issue arises when type expressions with unwrapped commas are passed as macro parameters (including when they are passed as preprocessor sequence elements):
@code
    std::map<dobule, int> m(void)
    CONTRACT_FUNCTION( (std::map<double, int>) (m)( (void) ) // Error.
        ...
    )
@endcode
This is interpreted as a preprocessor 2-tuple with two elements `<c>std::map<double</c>` and `<c>int></c>` separated by the comma `<c>,</c>` instead that one single element of the preprocessor sequence.

@Note Unfortunately, the approach followed for value expressions cannot be used for macro parameters that represent type expressions.
That is because types wrapped by an extra set of parenthesis @c () can introduce syntax or semantics errors depending on the context where they are used.
For example, with respect to <c>std::map<double, int></c>, the wrapped type expression <c>(std::map<double, int>)</c> could be compiled a C-style type cast potentically introducing a semantic error, or it could generate a syntax error if it were used to declare a variable.

The macro @c CONTRACT_WRAP_TYPE() (or equivalently the @c contract::wrap class template) is be used to overcome this limitation:
@code
    std::map<dobule, int> m(void)
    CONTRACT_FUNCTION( (CONTRACT_WRAP_TYPE( (std::map<double, int>) )) //OK.
            (m)( (void) )
        ...
    )
@endcode
Note that the extra pair of parenthesis @c () used in invoking the macro are mandatory as they wrap the comma(s) so one parameter (not many) is passed to the macro.

@Params
@Param{parenthesized_type, The type expression wrapped within an extra set of mandatory parenthesis @c ().}
@EndParams

@Returns The macro in the example above expands to code equivalent to the following:
@code
    std::map<dobule, int> m(void)
    CONTRACT_FUNCTION( (contract::wrap<void(std::map<double, int>)>::type)
            (m)( (void) )
        ...
    )
@endcode
@See contract::wrap, Tutorial section
*/
#define CONTRACT_WRAP_TYPE(parenthesized_type)

namespace contract {

/**
Metafunction used to wrap type expressions containing commas so they can be passed as macro parameters.

@Warning Attempting to use this template directly will generate a compile-time error.
Only the template specialization <c>contract::wrap<void(T)></c> can be used.

@See <c>contract::wrap<void(T)></c> specialization, @c CONTRACT_WRAP_TYPE()
*/
template<typename T>
struct wrap {};


/**
Metafunction used to wrap type expressions containing commas so they can be passed as macro parameters.

This metafunction first wrap the specified type @c T within parenthesis @c () (so @c T can be passed as a single macro parameter even if it contains commas) forming a void-function type with one argument of type @c T.
Then the application of the metafunction via its member @c type returns the wrapped type @c T.

@Params
@Param{T, Type to be wrapped so it can be passed within a macro parameter even if it contains commas.}
@EndParams

@See CONTRACT_WRAP_TYPE() for more explanation and examples
*/
template<typename T>
struct wrap<void(T)> {
    /** The type T. */
    typedef T type;
};

} // namespace

