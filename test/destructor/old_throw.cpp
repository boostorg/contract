
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test throw from destructor .old() (in middle branch of inheritance tree).

#include "../detail/oteststream.hpp"
#include <boost/contract/destructor.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/check.hpp>
#include <boost/config.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::test::detail::oteststream out;

struct c {
    static void static_invariant() { out << "c::static_inv" << std::endl; }
    void invariant() const { out << "c::inv" << std::endl; }

    ~c() BOOST_NOEXCEPT_IF(false) {
        boost::contract::check c = boost::contract::destructor(this)
            .old([] { out << "c::dtor::old" << std::endl; })
            .postcondition([] { out << "c::dtor::post" << std::endl; })
        ;
        out << "c::dtor::body" << std::endl;
        // Do not throw (from inheritance root).
    }
};

struct b
    #define BASES public c
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    static void static_invariant() { out << "b::static_inv" << std::endl; }
    void invariant() const { out << "b::inv" << std::endl; }

    struct err {};

    ~b() BOOST_NOEXCEPT_IF(false) {
        boost::contract::check c = boost::contract::destructor(this)
            .old([] {
                out << "b::dtor::old" << std::endl;
                throw b::err(); // Test .old() throw (from mid branch).
            })
            .postcondition([] { out << "b::dtor::post" << std::endl; })
        ;
        out << "b::dtor::body" << std::endl;
    }
};

struct a
    #define BASES public b
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    static void static_invariant() { out << "a::static_inv" << std::endl; }
    void invariant() const { out << "a::inv" << std::endl; }

    ~a() BOOST_NOEXCEPT_IF(false) {
        boost::contract::check c = boost::contract::destructor(this)
            .old([] { out << "a::dtor::old" << std::endl; })
            .postcondition([] { out << "a::dtor::post" << std::endl; })
        ;
        out << "a::dtor::body" << std::endl;
        // Do not throw (from inheritance leaf).
    }
};

int main() {
    std::ostringstream ok;

    boost::contract::set_postcondition_failure(
            [] (boost::contract::from) { throw; });

    try {
        {
            a aa;
            out.str("");
        }
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                BOOST_TEST(false);
            } catch(b::err const&) {
        #endif
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
                // Test a destructed (so only static_inv and post, but no inv).
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
                << "b::dtor::old" << std::endl // Test this threw.
            #else
                << "b::dtor::body" << std::endl
                #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                    << "b::static_inv" << std::endl
                #endif
            #endif

            #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                << "c::static_inv" << std::endl
                << "c::inv" << std::endl
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                << "c::dtor::old" << std::endl
            #endif
            << "c::dtor::body" << std::endl
            #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                << "c::static_inv" << std::endl
                #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                    // Test c not destructed (so both static_inv and inv).
                    << "c::inv" << std::endl
                #endif
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

