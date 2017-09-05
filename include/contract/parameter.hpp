
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_PARAMETER_HPP_
#define CONTRACT_PARAMETER_HPP_

/** @file
@brief Macros used to program named and deduced parameters (this header is
automatically included by <c>contract.hpp</c>).
*/

#include <contract/aux_/named_params.hpp>
#include <contract/aux_/macro/parameter.hpp>
#include <contract/aux_/macro/body.hpp>
#include <contract/aux_/macro/code_/named_params_/constructor.hpp>
#include <contract/detail/preprocessor/keyword/namespace.hpp>

// PRIVATE //

#ifndef DOXYGEN

#define CONTRACT_PARAMETER_TRAITS_NAMESPACE_SPLIT_namespace(tag_namespace) \
    tag_namespace,

#define CONTRACT_PARAMETER_TRAITS_NAMESPACE_YES_(sign) \
    ( CONTRACT_PARAMETER_TRAITS_NAMESPACE_SPLIT_ ## sign )

#define CONTRACT_PARAMETER_TRAITS_NAMESPACE_(sign) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_NAMESPACE_FRONT(sign), \
        CONTRACT_PARAMETER_TRAITS_NAMESPACE_YES_ \
    , \
        (CONTRACT_AUX_CONFIG_NAMED_PARAMETER_TAG_NAMESPACE_DEFAULT, sign) \
        BOOST_PP_TUPLE_EAT(1) \
    )(sign)
     
#define CONTRACT_PARAMETER_TRAITS_PASSING_SPLIT_(passing_name) \
    passing_name,

#define CONTRACT_PARAMETER_TRAITS_PASSING_YES_(tag_namespace, sign) \
    ( \
        tag_namespace \
    , \
        BOOST_PP_TUPLE_ELEM(2, 0, \
                (CONTRACT_PARAMETER_TRAITS_PASSING_SPLIT_ sign) ) \
    , \
        BOOST_PP_TUPLE_ELEM(2, 1, \
                (CONTRACT_PARAMETER_TRAITS_PASSING_SPLIT_ sign) ) \
    )

#define CONTRACT_PARAMETER_TRAITS_PASSING_NO_(tag_namespace, name) \
    /* default passing name postfixed with `_` (postfix like for Boost */ \
    /* keyword identifiers, named parameters are also called keyword */ \
    /* parameters, plus if prefix like for placeholder then can generate */ \
    /* reserved symbols if in global namespace and starting with upper */ \
    /* case, for example for template parameters _Valuetype) */ \
    (tag_namespace, BOOST_PP_CAT(name, _), name)

#define CONTRACT_PARAMETER_TRAITS_PASSING_(namespace_sign) \
    BOOST_PP_IIF(BOOST_PP_IS_UNARY(BOOST_PP_TUPLE_ELEM(2, 1, namespace_sign)), \
        CONTRACT_PARAMETER_TRAITS_PASSING_YES_ \
    , \
        CONTRACT_PARAMETER_TRAITS_PASSING_NO_ \
    )( \
          BOOST_PP_TUPLE_ELEM(2, 0, namespace_sign) \
        , BOOST_PP_TUPLE_ELEM(2, 1, namespace_sign) \
    )

#define CONTRACT_PARAMETER_TRAITS_(sign) \
    CONTRACT_PARAMETER_TRAITS_PASSING_( \
    CONTRACT_PARAMETER_TRAITS_NAMESPACE_( \
        sign \
    ))

#endif // DOXYGEN

// PUBLIC //

/**
@brief Macro used to access constructor named or deduced arguments within
member initializers.

This macro must be used to access the constructor arguments within the member
initializers.
Outside of the member initializers, the parameter names are used directly as
usual and without using this macro.

@Params
@Param{parameter_name,
The name of a constructor named or deduced parameter previously declared using
the @RefMacro{CONTRACT_PARAMETER} macro.
}
@EndParams

@SeeAlso @RefSect{named_parameters, Named Parameters} section.
*/
// To be used to access parameter values within constructor member initializers
// and try-blocks (this limitation comes from lack of delegating constructors).
#define CONTRACT_CONSTRUCTOR_ARG(parameter_name) \
    /* extra parenthesis () to make sure this expr is evaluated as whole */ \
    ( CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG(parameter_name) )

/**
@brief Macro used to access the actual type of a named or deduced parameter.

Named and deduced parameters can have generic types (possibly matching
predicate type requirements) so the actual parameter types are known at
compile-time but only after the function call has been resolved.
This macro is used to refer to the actual parameter type as it was determined
by the function call resolution.

@Params
@Param{parameter_name,
The name of a named or deduced parameter previously declared using the
@RefMacro{CONTRACT_PARAMETER} macro.
}
@EndParams

This macro can be used within both the function declaration and the body
definition.

@SeeAlso @RefSect{named_parameters, Named Parameters} section.
*/
// Do not expose Boost.Parameter's internal conventions to use
// tag::param_name::_ or param_name_type to access type plus uses the same
// way to access param type in all requirement expressions, concepts, etc.
#define CONTRACT_PARAMETER_TYPEOF(parameter_name) \
    CONTRACT_AUX_PARAMETER_BOOST_TYPE(parameter_name)

/**
@brief Macro used to declare a named or deduced function parameter.

This macro is used to declare a named or deduced parameter that will later be
used within a function declared using the @RefMacro{CONTRACT_FUNCTION} or the
@RefMacro{CONTRACT_CONSTRUCTOR} macros.
This macro should be used at namespace scope.

@Params
@Param{named_parameter_declaration,
The syntax of named and deduced parameter declarations is explained in the
@RefSect{grammar\, Grammar} section.
At lest the parameter name must be specified.
}
@EndParams

It is recommended to always use this macro within an enclosing namespace
different from the global namespace so to control and avoid clashing
declarations of named and deduced parameters that have the same name.

@SeeAlso @RefSect{named_parameters, Named Parameters} section.
*/
// sign: [namespace(tag_namespace_)] [(passing_name_)] name_
#define CONTRACT_PARAMETER(named_parameter_declaration) \
    BOOST_PP_EXPAND(CONTRACT_AUX_PARAMETER_BOOST_PARAM \
            CONTRACT_PARAMETER_TRAITS_(named_parameter_declaration))

/**
@brief Macro used to declare a named or deduced template parameter.

This macro is used to declare a named or deduced parameter that will later be
used within a class template declared using the @RefMacro{CONTRACT_CLASS}
macro.
This macro should be used at namespace scope.

@Params
@Param{named_parameter_declaration,
The syntax of named and deduced parameter declarations is explained in the
@RefSect{grammar\, Grammar} section.
At lest the template parameter name must be specified.
}
@EndParams

It is recommended to always use this macro within an enclosing namespace
different from the global namespace so to control and avoid clashing
declarations of named and deduced parameters that have the same name.

@SeeAlso @RefSect{named_parameters, Named Parameters} section.
*/
// sign: [namespace(tag_namespace_)] [(passing_name_)] name_
#define CONTRACT_TEMPLATE_PARAMETER(named_parameter_declaration) \
    BOOST_PP_EXPAND(CONTRACT_AUX_PARAMETER_BOOST_TEMPLATE_PARAM \
            CONTRACT_PARAMETER_TRAITS_(named_parameter_declaration))

/**
@brief Macro used to name the body of free and member functions with named
parameters.

This macro is used to name the body of a function with named parameters when
the body is defined separately from the function declaration.

@Params
@Param{function_name,
The name of the function with named parameters.
}
@EndParams

For member functions, the class type must precede this macro (this allows to
use this same macro for both free and member functions):
@code
class_type::CONTRACT_PARAMETER_BODY(function_name)
@endcode

@Note Named parameters are currently not supported for operators so this
function name cannot be the name of an operator (because of a Boost.Parameter
bug).
Constructors with named parameters cannot defer the definition of their body
(because of lack of delegating constructors in C++03).
Finally, destructors have no parameter so named parameters do not apply to
destructors.
Therefore, this macro is never used for operators, constructors, and
destructors.

@SeeAlso @RefSect{named_parameters, Named Parameters} section.
*/
#define CONTRACT_PARAMETER_BODY(function_name) \
    /* always "contracted" because named parameter functions always need to */ \
    /* use the extra body function regardless of contract enabled or not */ \
    CONTRACT_AUX_BODY_PARAMETER_FUNCTION_CONTRACTED(function_name)

#endif // #include guard

