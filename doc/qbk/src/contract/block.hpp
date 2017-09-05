// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

/** @file
Assert block (and loop) invariants and loop variants.
*/










/**
Macro used to assert invariant contract conditions from within a code block.

To assert class invariants, preconditions, and postcondition use @c CONTRACT_ASSERT() instead.

The code asserting the boolean condition is also used as the description of the condition.
For example (see the Tutorial section for more information):
@code
    ...
    { // From within this code block.
        int x = 0;
        CONTRACT_ASSERT_BLOCK_INVARIANT( x == 0 );
    }
    ...
@endcode

@Params
@Param{boolean_condition, The boolean contract condition being asserted.}
@EndParams

@Returns This macro expands to code that will automatically invoke @c contract::block_invariant_failed() if the specified condition is evaluated to be @c false.
The macro expands to code equivalent to the following:
@code
    try {
        CONTRACT_ASSERT( boolean_condition );
    } catch (...) {
        contract::block_invariant_failed(contract::FROM_BLOCK);
    }
@endcode

@See @c CONTRACT_ASSERT_BLOCK_INVARIANT_MSG()
*/
#define CONTRACT_ASSERT_BLOCK_INVARIANT(boolen_condition)










/**
Macro used to assert invariant contract conditions from within a code block specifying also a human readable message.

To assert class invariants, preconditions, and postcondition use @c CONTRACT_ASSERT_MSG() instead.

For example (see the Tutorial section for more information):
@code
    ...
    { // From within this code block.
        int x = 0;
        CONTRACT_ASSERT_BLOCK_INVARIANT_MSG( x == 0, "x is zero" );
    }
    ...
@endcode

@Params
@Param{boolean_condition, The boolean contract condition being asserted.}
@Param{string_description,
    A string providing a human readable description of the condition being asserted. (used for error reporting).}
@EndParams

@Returns This macro expands to code that will automatically invoke @c contract::block_invariant_failed() if the specified condition is evaluated to be @c false.
The macro expands to code equivalent to the following:
@code
    try {
        CONTRACT_ASSERT_MSG( boolean_condition, string_description );
    } catch (...) {
        contract::block_invariant_failed(contract::FROM_BLOCK);
    }
@endcode

@See @c CONTRACT_ASSERT_BLOCK_INVARIANT()
*/
#define CONTRACT_ASSERT_BLOCK_INVARIANT_MSG(boolean_condition, string_description)











/**
Macro used to assert loop variant.

At each loop iteration, the value of the specified loop variant expression is automatically evaluated and asserted to be positive (<c>> 0</c>) and to decrease (<c><</c>) from the variant value at previous loop iteration.
A loop can only have one variant.

@Note Loop variants can be used to check <b>loop correctness</b> (see the Tutorial section and related references):
Because the loop variant decreases monotonically at each loop iteration and it cannot be zero or smaller than zero, it is possible to guarantee loop termination.

The macro @c CONTRACT_INIT_LOOP_VARIANT must be used (once and only once) before asserting the loop variant and within the same or higher scope of the block containing @c CONTRACT_ASSERT_LOOP_VARIANT().

Loops are code blocks that repeat themselves in iteration. Therefore, it is possible to use @c CONTRACT_ASSERT_BLOCK_INVARIANT() (or @c CONTRACT_ASSERT_BLOCK_INVARIANT_MSG()) to assert loop invariants together with loop variants.
A loop can have multiple invariants.

For example (see the Tutorial section for more information):
@code
    ...
    {
        CONTRACT_INIT_LOOP_VARIANT; // Declare variant within scope.
        for (i = 0; i < v.size(); ++i) {
            // Loop invariants.
            CONTRACT_ASSERT_BLOCK_INVARIANT( i >= 0 );
            CONTRACT_ASSERT_BLOCK_INVARIANT( i < v.size() );
            // Loop variant (assert always positive and decreasing).
            CONTRACT_ASSERT_LOOP_VARIANT( v.size() - i );
            
            std::cout << v[i] << std::endl;
    }
    ...
@endcode

The variant expression code is used as a human readable description of the variant (see @c CONTRACT_ASSERT_LOOP_VARIANT_MSG()).

@Params
@Param{integer_expression, The integer expression which is evaluated at each loop iteration and asserted to be positive and decreasing from one iteration to the next one.}
@EndParams

@Returns This macro expands to code that will automatically invoke @c contract::block_invariant_failed() if the specified variant is not positive or it does not decrease.

@See @c CONTRACT_INIT_LOOP_VARIANT, @c CONTRACT_ASSERT_LOOP_VARIANT_MSG()
*/
#define CONTRACT_ASSERT_LOOP_VARIANT(integer_expression)










/**
Macro used to assert loop variant specifying also a human readable description.

See @c CONTRACT_ASSERT_LOOP_VARIANT() explanations and examples.

@Params
@Param{integer_expression, The integer expression which is evaluated at each loop iteration and asserted to be positive and decreasing from one iteration to the next one.}
@Param{string_description, A human readable description of the loop variant expression (used for error reporting).}
@EndParams

@Returns This macro expands to code that will automatically invoke @c contract::block_invariant_failed() if the specified variant is not positive or it does not decrease.

@See @c CONTRACT_INIT_LOOP_VARIANT(), @c CONTRACT_ASSERT_LOOP_VARIANT()
*/
#define CONTRACT_ASSERT_LOOP_VARIANT_MSG(integer_expression, string_description)











/**
Initialize the evaluation of the loop variant expression of type @c contract::loop_variant_type.

It must be used once, and only once, in a given code block.
It must be used before using @c CONTRACT_ASSERT_LOOP_VARIANT() (or @c CONTRACT_ASSERT_LOOP_VARIANT_MSG()) at same of higher scope level.

It can also be used within a @c for loop initialization argument, for example:
@code
    void offset(int& i) {
        ...
        for (CONTRACT_INIT_LOOP_VARIANT; i < MAX; ) {
            CONTRACT_ASSERT_LOOP_VARIANT( MAX - i );
            ...
            i += DELTA;
        }
    }
@endcode

@See @c contract::loop_variant_type, @c CONTRACT_ASSERT_LOOP_VARIANT(), @c CONTRACT_ASSERT_LOOP_VARIANT_MSG()
*/
#define CONTRACT_INIT_LOOP_VARIANT









namespace contract {

/**
The type of the loop variant expression.

The @c __Integer__ type is a signed integer type but its actual type is library implementation specific.

@Note While the loop variant expression type is signed, the loop variant value is asserted to be always positive (<c>> 0</c>).

For example, you can use this type to convert (not cast) the variant expression into the variant type:
@code
    CONTRACT_INIT_LOOP_VARIANT;
    for (size_t i = 0; i < v.size(); ++i) {
        CONTRACT_ASSERT_LOOP_VARIANT( loop_variant_type(v.size() - i) );
        ...
    }
@endcode
Note this is @b not a type cast so it will generate a compile-time error if the type conversion if not possible.
*/
typedef __Integer__ loop_variant_type;

} // namespace

