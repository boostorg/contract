
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

//[const_assertion_number
unsigned even = 0;

CONTRACT_CLASS(
    class (number)
) {
    CONTRACT_CLASS_INVARIANT( void )
    
    public: static unsigned odd;

    CONTRACT_FUNCTION(
        public void (next) ( void )
            postcondition(
                auto old_even = CONTRACT_OLDOF even,
                auto old_odd = CONTRACT_OLDOF odd,
                // `[old_]even` and `[old_]odd` all `const&` within assertions.
                const( even, old_even ) even == old_even + 2,
                const( odd, old_odd ) odd == old_odd + 2
            )
    ) {
        even += 2;
        odd += 2;
    }
};

unsigned number::odd = 1;
//]

int main ( void )
{
    number n;
    n.next();
    BOOST_TEST(even == 2);
    BOOST_TEST(number::odd == 3);
    return boost::report_errors();
}

