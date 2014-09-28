
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <limits>

//[function_template_postinc
CONTRACT_FUNCTION(
    template( typename T ) // Template parameter(s).
    (T const) (postinc) ( (T&) value )
        precondition( value < std::numeric_limits<T>::max() )
        postcondition(
            auto result = return,
            auto old_value = CONTRACT_OLDOF value,
            value == old_value + 1,
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

