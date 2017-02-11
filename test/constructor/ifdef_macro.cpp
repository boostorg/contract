
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test contract compilation on/off (using macro interface).

#include "../detail/oteststream.hpp"
#include <boost/contract/core/config.hpp>
#include <boost/contract/constructor.hpp> // Outside #if below for ctor pre.
#include <boost/contract_macro.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::test::detail::oteststream out;

struct b :
    private boost::contract::constructor_precondition<b> // OK, always in code.
{
    BOOST_CONTRACT_STATIC_INVARIANT({ out << "b::static_inv" << std::endl; })
    BOOST_CONTRACT_INVARIANT({ out << "b::inv" << std::endl; })

    explicit b(int x) :
        BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION(b)([] {
            out << "b::ctor::pre" << std::endl;
        })
    {
        BOOST_CONTRACT_OLD_PTR(int)(old_x, x);
        BOOST_CONTRACT_CONSTRUCTOR(this)
            BOOST_CONTRACT_OLD([] { out << "b::f::old" << std::endl; })
            BOOST_CONTRACT_POSTCONDITION([] {
                out << "b::ctor::post" << std::endl;
            })
        ;
        out << "b::ctor::body" << std::endl;
    }
};

struct a:
    private boost::contract::constructor_precondition<a>, // OK, always in code.
    public b
{
    BOOST_CONTRACT_STATIC_INVARIANT({ out << "a::static_inv" << std::endl; })
    BOOST_CONTRACT_INVARIANT({ out << "a::inv" << std::endl; })

    explicit a(int x) :
        BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION(a)([] {
            out << "a::ctor::pre" << std::endl; }
        ),
        b(x)
    {
        BOOST_CONTRACT_OLD_PTR(int)(old_x, x);
        BOOST_CONTRACT_CONSTRUCTOR(this)
            BOOST_CONTRACT_OLD([] { out << "a::f::old" << std::endl; })
            BOOST_CONTRACT_POSTCONDITION([] {
                out << "a::ctor::post" << std::endl;
            })
        ;
        out << "a::ctor::body" << std::endl;
    }
};

int main() {
    std::ostringstream ok;
    out.str("");
    a aa(123);
    ok.str(""); ok
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
        #endif
        
        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::f::old" << std::endl
        #endif
        << "b::ctor::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::ctor::post" << std::endl
        #endif

        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "a::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "a::f::old" << std::endl
        #endif
        << "a::ctor::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "a::ctor::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));
    return boost::report_errors();
}

