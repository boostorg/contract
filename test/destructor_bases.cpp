
#include "aux_/oteststream.hpp"
#include <boost/contract/destructor.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/scope_exit.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

// Test destructor contracts for classes with and without bases.

boost::contract::aux::test::oteststream out;

struct d { // Test inheritance level 0.
    void invariant() const {
        out << "d::inv" << std::endl;
    }

    static void static_invariant() {
        out << "d::static_inv" << std::endl;
    }

    ~d() {
        boost::contract::type c = boost::contract::destructor(this)
            .postcondition([&] () {
                out << "d::dtor::post" << std::endl;
            })
        ;
        out << "d::dtor::body" << std::endl;
    }
};

struct c // Test inheritance level 1.
    #define BASES public d
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        out << "c::inv" << std::endl;
    }

    static void static_invariant() {
        out << "c::static_inv" << std::endl;
    }

    ~c() {
        boost::contract::type c = boost::contract::destructor(this)
            .postcondition([&] () {
                out << "c::dtor::post" << std::endl;
            })
        ;
        out << "c::dtor::body" << std::endl;
    }
};

struct b { // Test inheritance level 0.
    void invariant() const {
        out << "b::inv" << std::endl;
    }

    static void static_invariant() {
        out << "b::static_inv" << std::endl;
    }

    ~b() {
        boost::contract::type c = boost::contract::destructor(this)
            .postcondition([&] () {
                out << "b::dtor::post" << std::endl;
            })
        ;
        out << "b::dtor::body" << std::endl;
    }
};

struct a // Test multiple inheritance and inheritance level 2.
    #define BASES public b, public c
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        out << "a::inv" << std::endl;
    }

    static void static_invariant() {
        out << "a::static_inv" << std::endl;
    }

    ~a() {
        boost::contract::type c = boost::contract::destructor(this)
            .postcondition([&] () {
                out << "a::dtor::post" << std::endl;
            })
        ;
        out << "a::dtor::body" << std::endl;
    }
};

int main() {
    std::ostringstream ok;

    {
        a aa;
        out.str("");
    } // `a`'s destructor called, and `out` set, here.
    ok.str("");
    ok
        << "a::static_inv" << std::endl
        << "a::dtor::body" << std::endl
        << "a::static_inv" << std::endl
        << "a::dtor::post" << std::endl

        << "c::static_inv" << std::endl
        << "c::dtor::body" << std::endl
        << "c::static_inv" << std::endl
        << "c::dtor::post" << std::endl
        
        << "d::static_inv" << std::endl
        << "d::dtor::body" << std::endl
        << "d::static_inv" << std::endl
        << "d::dtor::post" << std::endl
        
        << "b::static_inv" << std::endl
        << "b::dtor::body" << std::endl
        << "b::static_inv" << std::endl
        << "b::dtor::post" << std::endl
    ;
    BOOST_TEST(out.check(ok.str()));
    
    return boost::report_errors();
}

