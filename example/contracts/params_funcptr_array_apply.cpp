
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>

//[params_funcptr_array_apply
// Contracts cannot directly use array type syntax, use via `typedef` instead.
typedef int array_2x3[2][3];
typedef int (*func_ptr) ( int );

CONTRACT_FUNCTION(
    void (apply) ( (func_ptr) f, (array_2x3) m )
        // precondition:    f != NULL
        //                  m != NULL
) {
    for ( size_t i = 0; i < 2; ++i) 
        for ( size_t j = 0; j < 3; ++j)
            m[i][j] = f(m[i][j]);
}

int offset ( int i ) { return i + 10; }
//]

int main ( void )
{
    //[params_funcptr_array_apply_call
    int x[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    apply(offset, x);
    //]
    
    BOOST_TEST(x[0][0] == 11);
    BOOST_TEST(x[0][1] == 12);
    BOOST_TEST(x[0][2] == 13);
    
    BOOST_TEST(x[1][0] == 14);
    BOOST_TEST(x[1][1] == 15);
    BOOST_TEST(x[1][2] == 16);
    
    return boost::report_errors();
}

