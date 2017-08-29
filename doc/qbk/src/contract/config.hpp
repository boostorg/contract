// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

/** @file
Macros to change some of the library compile-time configuration.

Configuration macros can be \#defined by the user to change some of the library behaviour.
If the user does not \#define these macros, the library uses proper default values:

@code
    #ifndef CONTRACT_CONFIG_SOMETHING
    #   define CONTRACT_CONFIG_SOMETHING some-default-value
    #endif
@endcode

@Note It is strongly recommended not to changed the configuration macro default values unless strictly necessary.
*/

/**
The maximum number of function arguments supported by this library.

@Warning Increasing this number can @b significantly increase compilation time.
If possible, do not increase this number.

If you need to write a contract for a function with a number of arguments larger than the one specified by this macro default value, consider alternatives like wrapping the arguments within a @c struct.
For example, consider the function:
@code
    // Many arguments thus need to increase configuration macro value.
    void f(int i1, int i2, int i3, int i4, int i5, int i6, int i7);
@endcode
However, this function could be rewritten as a single argument function using a @c struct:
@code
    struct ints {
        int i1;
        int i2;
        int i3;
        int i4;
        int i5;
        int i6;
        int i7;
    };

    // Just one argument and default macro value suffice.    
    void f(ints i);
@endcode
Now the contract for @c f only requires one argument and this macro value does not need to be increased.
*/
#define CONTRACT_CONFIG_MAX_FUNCTION_ARITY

/**
The maximum number of base classes supported when subcontracting with multiple inheritance.

@Warning Increasing this number can @b significantly increase compilation time.
If possible, do not increase this number.
*/
#define CONTRACT_CONFIG_MAX_MULTIPLE_INHERITANCE

