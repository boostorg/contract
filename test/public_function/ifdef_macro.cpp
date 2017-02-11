
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test contract compilation on/off (using macro interface).

#include "../detail/oteststream.hpp"
#include <boost/contract/core/config.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract_macro.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::test::detail::oteststream out;

struct b {
    BOOST_CONTRACT_STATIC_INVARIANT({ out << "b::static_inv" << std::endl; })
    BOOST_CONTRACT_INVARIANT({ out << "b::inv" << std::endl; })

    virtual void f(int x, boost::contract::virtual_* v = 0) = 0;
};

void b::f(int x, boost::contract::virtual_* v) {
    BOOST_CONTRACT_OLD_PTR(int)(v, old_x, x);
    BOOST_CONTRACT_PUBLIC_FUNCTION(v, this)
        BOOST_CONTRACT_PRECONDITION([] { out << "b::f::pre" << std::endl; })
        BOOST_CONTRACT_OLD([] { out << "b::f::old" << std::endl; })
        BOOST_CONTRACT_POSTCONDITION([] { out << "b::f::post" << std::endl; })
    ;
    out << "b::f::body" << std::endl;
}

struct a
    #define BASES public b
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types; // OK, always in code.
    BOOST_CONTRACT_OVERRIDE(f) // OK if always in code.

    BOOST_CONTRACT_STATIC_INVARIANT({ out << "a::static_inv" << std::endl; })
    BOOST_CONTRACT_INVARIANT({ out << "a::inv" << std::endl; })

    virtual void f(int x, boost::contract::virtual_* v = 0) {
        BOOST_CONTRACT_OLD_PTR(int)(v, old_x, x);
        BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(override_f)(v, &a::f, this, x)
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
    
    a aa;
    out.str("");
    aa.f(123);
    ok.str(); ok
        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            << "b::f::pre" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::f::old" << std::endl
            << "a::f::old" << std::endl
        #endif
        << "a::f::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::f::old" << std::endl
            << "b::f::post" << std::endl
            << "a::f::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

