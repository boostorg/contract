
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <limits>

//[post_also_postinc
CONTRACT_FUNCTION(
    int const (postinc) ( (int&) value )
        precondition( value < std::numeric_limits<int>::max() )
        postcondition(                              // Postconditions.
            auto result = return,                   // Result value.
            auto old_value = CONTRACT_OLDOF value,  // Old value(s).
            value == old_value + 1,                 // Assertion(s)...
            result == old_value
        )
) {
    return value++;
}
//]

int main ( void )
{
    int value = 1;
    BOOST_TEST(postinc(value) == 1);
    BOOST_TEST(value == 2);
    return boost::report_errors();
}

