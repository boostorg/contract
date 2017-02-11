
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test public static member function contract compilation on/off (w/ macros).

#include "../detail/oteststream.hpp"
#include <boost/contract/core/config.hpp>
#include <boost/contract_macro.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::test::detail::oteststream out;

struct a {
    BOOST_CONTRACT_STATIC_INVARIANT({ out << "a::static_inv" << std::endl; })
    BOOST_CONTRACT_INVARIANT({ out << "a::inv" << std::endl; })

    static void f(int x) {
        BOOST_CONTRACT_OLD_PTR(int)(old_x, x);
        BOOST_CONTRACT_STATIC_PUBLIC_FUNCTION(a)
            BOOST_CONTRACT_PRECONDITION([] { out << "a::f::pre" << std::endl; })
            BOOST_CONTRACT_OLD([] { out << "a::f::old" << std::endl; })
            BOOST_CONTRACT_POSTCONDITION([] {
                out << "a::f::post" << std::endl;
            })
        ;
        out << "a::f::body" << std::endl;
    }
};

int main() {
    std::ostringstream ok;

    out.str("");
    a::f(123);
    ok.str(""); ok
        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "a::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            << "a::f::pre" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "a::f::old" << std::endl
        #endif
        << "a::f::body" << std::endl
        // Test no post (but still static inv) because body threw.
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "a::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "a::f::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

