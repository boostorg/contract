
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

struct too_old {};

//[named_param_identifiers_failure
CONTRACT_PARAMETER( (name) name )   // Both parameter and argument 
CONTRACT_PARAMETER( (age) age )     // have same name, but...

CONTRACT_FUNCTION(
    void (print) ( in auto name, default("bob"), in auto age, default 42 )
        precondition( age > 0 )
) {
    if(age >= 40) throw too_old(); // Will throw because age defaulted to 42.
}

void f ( int age ) // Another parameter with the same name.
{
    print(age = 3); // So incorrect call but no compiler-error.
}
//]

int main ( void )
{
    try {
        f(123);
        BOOST_TEST(false);
    } catch(too_old&) {
        BOOST_TEST(true); // Test threw error as expected.
    } catch(...) {
        BOOST_TEST(false);
    }
    return boost::report_errors();
}

