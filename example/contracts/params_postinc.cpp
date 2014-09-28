
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

//[params_postinc
CONTRACT_FUNCTION( // Overload, storage classifiers, and default parameters.
    long const (postinc) ( (long&) value, register unsigned offset, default 1 )
        // precondition:    value < std::numeric_limits<long>::max()
        // postcondition:   value == oldof value + offset
        //                  result == oldof value
) {
    long result = value;
    if(offset > 0) {
        value += 1;
        postinc(value, offset - 1); // Recursive calls.
    }
    return result;
}
//]

int main ( void )
{
    //[params_postinc_call
    long value = 1;
    BOOST_TEST(postinc(value) == 1);    // Increment of 1 (it is 1).
    BOOST_TEST(postinc(value, 4) == 2); // Increment of 4 (it is 2).
    BOOST_TEST(value == 6);             // Incremented of 4 (it was 2).
    //]
    return boost::report_errors();
}

