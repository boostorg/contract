
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_BODY_HPP_
#define CONTRACT_BODY_HPP_

/** @file
@brief Macros used to program body definitions separately from the contract
declarations (this header is automatically include by <c>contract.hpp</c>).
*/

#include <contract/aux_/config.hpp>
#include <contract/aux_/symbol.hpp>
#include <contract/aux_/macro/body.hpp>

// PRIVATE //

#ifndef DOXYGEN

#define CONTRACT_FREE_BODY_(function_name, contracted01) \
    BOOST_PP_IIF(contracted01, \
        CONTRACT_AUX_BODY_FUNCTION_CONTRACTED \
    , \
        CONTRACT_AUX_BODY_FUNCTION \
    )(function_name)

#define CONTRACT_MEMBER_BODY_(class_type, function_name, contracted01) \
    CONTRACT_AUX_BODY_CLASS_TYPE(class_type) :: \
    CONTRACT_FREE_BODY_(function_name, contracted01)

#define CONTRACT_CONSTRUCTOR_BODY_(class_type, constructor_name, contracted01) \
    BOOST_PP_EXPR_IF(contracted01, void) \
    CONTRACT_AUX_BODY_CLASS_TYPE(class_type) :: \
    BOOST_PP_IIF(contracted01, \
        CONTRACT_AUX_BODY_CONSTRUCTOR_CONTRACTED \
    , \
        BOOST_PP_TUPLE_REM(1) \
    )(constructor_name)

#define CONTRACT_DESTRUCTOR_BODY_(class_type, destructor_name, contracted01) \
    BOOST_PP_EXPR_IF(contracted01, void) \
    CONTRACT_AUX_BODY_CLASS_TYPE(class_type) :: \
    BOOST_PP_IIF(contracted01, \
        CONTRACT_AUX_BODY_DESTRUCTOR_CONTRACTED \
    , \
        BOOST_PP_TUPLE_REM(1) \
    )(destructor_name)

#endif // DOXYGEN

// PUBLIC //

/**
@brief Macro used to name the body of free functions and free function
operators.

This macro is used to name the body of free functions and free function
operators when the body is defined separately from the contract declaration.
Free functions and free function operators with contracts are declared
using the @RefMacro{CONTRACT_FUNCTION} macro.

@Params
@Param{function_name,
The syntax for free function and free function operator names is explained in
the @RefSect{grammar\, Grammar} section.
}
@EndParams

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#define CONTRACT_FREE_BODY(function_name) \
    CONTRACT_FREE_BODY_(function_name, \
        BOOST_PP_BITOR( \
              CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
            , CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
        ) \
    )

/**
@brief Macro used to name the body of member functions and member function
operators.

This macro is used to name the body of member functions and member function
operators when the body is defined separately from the contract declaration.
Member functions and member function operators with contracts are declared
using the @RefMacro{CONTRACT_FUNCTION} macro.

@Params
@Param{class_type,
The syntax for the class type is explained in the @RefSect{grammar\, Grammar}
section (for class templates\, this type is qualified with the template
parameters).
}
@Param{function_name,
The syntax for function and operator names is explained in the
@RefSect{grammar\, Grammar} section.
}
@EndParams

@Warning This macro must also be used when a virtual function invokes the
overridden function from one of its base classes (see the
@RefSect{tutorial, Tutorial} section).

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
// class_type: `vect<T>`, `(vect<T, A>)`, or `comma(1)(vect<T, A>)`.
#define CONTRACT_MEMBER_BODY(class_type, function_name) \
    /* NOTE: this must be a different macro from FREE_BODY because it */ \
    /* expands also if invariants (not just pre and post) */ \
    /* class type is specified so this macro API is same as ctor and dtor */ \
    CONTRACT_MEMBER_BODY_(class_type, function_name, \
        BOOST_PP_BITOR( \
              CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
            , BOOST_PP_BITOR( \
                  CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
                , CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
              ) \
        ) \
    )

/**
@brief Macro used to name the body of constructors.

This macro is used to name the body of constructors when the body is defined
separately from the contract declaration.
Constructors with contracts are declared using the
@RefMacro{CONTRACT_CONSTRUCTOR} macro.

@Params
@Param{class_type,
The syntax for the class type is explained in the @RefSect{grammar\, Grammar}
section (for class templates\, this type is qualified with the template parameters).
}
@Param{constructor_name,
This is the class name and its syntax is explained in the
@RefSect{grammar\, Grammar} section (for class templates\, this name is
<em>not</em> qualified with the template parameters).
}
@EndParams

@Warning The body of constructors with member initializers should always be
defined together with the constructor declaration and its contract.

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
// class_type: `vect<T>`, `(vect<T, A>)`, or `comma(1)(vect<T, A>)`.
#define CONTRACT_CONSTRUCTOR_BODY(class_type, constructor_name) \
    CONTRACT_CONSTRUCTOR_BODY_(class_type, constructor_name, \
        BOOST_PP_BITOR( \
              CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
            , BOOST_PP_BITOR( \
                  CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
                , CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
              ) \
        ) \
    )

/**
@brief Macro used to name the body of destructors.

This macro is used to name the body of destructors when the body is defined
separately from the contract declaration.
Destructors with contracts are declared using the
@RefMacro{CONTRACT_DESTRUCTOR} macro.

@Params
@Param{class_type,
The syntax for the class type is explained in the @RefSect{grammar\, Grammar}
section (for class templates\, this type is qualified with the template
parameters).
}
@Param{destructor_name,
This is the class name prefixed by the tilde symbol <c>~</c> and its syntax is
explained in the @RefSect{grammar\, Grammar} section (for class templates\,
this name is <em>not</em> qualified with the template parameters).
}
@EndParams

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
// class_type: `vect<T>`, `(vect<T, A>)`, or `comma(1)(vect<T, A>)`.
#define CONTRACT_DESTRUCTOR_BODY(class_type, destructor_name) \
    CONTRACT_DESTRUCTOR_BODY_(class_type, destructor_name, \
        CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
    )

#endif // #include guard

