
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test contract compilation on/off (using macro interface).

#include "../detail/oteststream.hpp"
#include <boost/contract/core/config.hpp>
#include <boost/contract_macro.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::test::detail::oteststream out;

struct b {
    BOOST_CONTRACT_STATIC_INVARIANT({ out << "b::static_inv" << std::endl; })
    BOOST_CONTRACT_INVARIANT({ out << "b::inv" << std::endl; })

    virtual ~b() {
        BOOST_CONTRACT_OLD_PTR(int)(old_y, y);
        BOOST_CONTRACT_DESTRUCTOR(this)
            BOOST_CONTRACT_OLD([] { out << "b::dtor::old" << std::endl; })
            BOOST_CONTRACT_POSTCONDITION([] {
                out << "b::dtor::post" << std::endl;
            })
        ;
        out << "b::dtor::body" << std::endl;
    }
    
    static int y;
};
int b::y = 0;

struct a : public b {
    BOOST_CONTRACT_STATIC_INVARIANT({ out << "a::static_inv" << std::endl; })
    BOOST_CONTRACT_INVARIANT({ out << "a::inv" << std::endl; })

    virtual ~a() {
        BOOST_CONTRACT_OLD_PTR(int)(old_x, x);
        BOOST_CONTRACT_DESTRUCTOR(this)
            BOOST_CONTRACT_OLD([] { out << "a::dtor::old" << std::endl; })
            BOOST_CONTRACT_POSTCONDITION([] {
                out << "a::dtor::post" << std::endl;
            })
        ;
        out << "a::dtor::body" << std::endl;
    }
    
    static int x;
};
int a::x = 0;

int main() {
    std::ostringstream ok;
    {
        a aa;
        out.str("");
    }
    ok.str(""); ok
        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "a::dtor::old" << std::endl
        #endif
        << "a::dtor::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "a::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "a::dtor::post" << std::endl
        #endif

        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::dtor::old" << std::endl
        #endif
        << "b::dtor::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "b::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::dtor::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));
    return boost::report_errors();
}

