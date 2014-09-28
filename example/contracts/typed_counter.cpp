
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

//[typed_counter
CONTRACT_CLASS(
    class (counter)
) {
    CONTRACT_CLASS_INVARIANT( void )
    
    public: static unsigned value;
    
    CONTRACT_FUNCTION(
        public static int (next) ( void )
            postcondition( // Explicit types so no Boost.Typeof.
                auto result = return,
                unsigned const old_value = CONTRACT_OLDOF value,
                const( unsigned value, unsigned const old_value )
                        value == old_value + 1,
                result == int(value)
            )
    ) {
        return ++value;
    }
};

unsigned counter::value = 0;
//]

int main ( void )
{
    BOOST_TEST(counter::next() == 1);
    return boost::report_errors();
}

