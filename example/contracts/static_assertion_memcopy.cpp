
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <cstring>

//[static_assertion_memcopy
CONTRACT_FUNCTION(
    template( typename To, typename From )
    (To*) (memcopy) ( (To*) to, (From*) from )
        precondition( // Static assertions.
            static_assert(sizeof(To) >= sizeof(From), "destination too small"),
            // Wrapping parenthesis for asserted condition with commas.
            static_assert((boost::is_convertible<From, To>::value),
                    "incompatible types"),
            to, // pointer not null
            from // pointer not null
        )
) ;
//]

template< typename To, typename From >
To* CONTRACT_FREE_BODY(memcopy)( To* to, From* from )
{
    memcpy(to, from, sizeof(From));
    return to;
}

int main ( void )
{
    int x = 0, y = 123;
    memcopy(&x, &y);
    BOOST_TEST(x == 123);
    BOOST_TEST(y == 123);
    return boost::report_errors();
}

