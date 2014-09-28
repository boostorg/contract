
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>

template<
      typename X
    , template< typename S, typename T = S > class Y
    , class Z = int
    , Z V = 0
> struct x {};

//[template_params_class
CONTRACT_CLASS( // Class template parameters.
    template(
          typename A            // Type template parameter.
        , int B                 // Value template parameter.
        , class C, default A    // Optional type template parameter.
        , (A) D, default B      // Optional value template parameter.
        , template(             // Template template parameter: Outer template
              typename X        // uses `()` but rest uses usual syntax.
            , template< typename S, typename T = S > class Y
            , class Z = int
            , Z V = 0
          ) class E, default x  // Optional template template parameter.
    )
    struct (a)
) {
    // ...
//]
    CONTRACT_CLASS_INVARIANT_TPL( void )
};

//[template_params_function
CONTRACT_FUNCTION( // Function template parameters.
    template( // As usual, no default template parameters allowed in functions.
          typename A            // Type template parameter.
        , int B                 // Value template parameter.
        , class C               // Type template parameter.
        , (A) D                 // Value template parameter.
        , template(             // Template template parameter: Outer template
              typename X        // uses `()` but rest uses usual syntax.
            , template< typename S, typename T = S > class Y
            , class Z = int
            , Z V = 0
          ) class E
    )
    void (f) ( void ) 
) {
    // ...
//]
}

int main ( void )
{
    a<int, 0> aa;
    f<int, 0, double, 123, x>();
    return 0;
};

