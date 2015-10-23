
// Test destructor body throwing (in middle branch of inheritance tree).

#include "../aux_/oteststream.hpp"
#include <boost/contract/destructor.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/guard.hpp>
#include <boost/config.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <exception>
#include <cstdlib>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct c {
    void invariant() const { out << "c::inv" << std::endl; }
    static void static_invariant() { out << "c::static_inv" << std::endl; }

    ~c() {
        boost::contract::guard c = boost::contract::destructor(this)
            .old([&] { out << "c::dtor::old" << std::endl; })
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

    void invariant() const { out << "b::inv" << std::endl; }
    static void static_invariant() { out << "b::static_inv" << std::endl; }

    struct e {};

    ~b() {
        boost::contract::guard c = boost::contract::destructor(this)
            .old([&] { out << "b::dtor::old" << std::endl; })
            .postcondition([] { out << "b::dtor::post" << std::endl; })
        ;
        out << "b::dtor::body" << std::endl;
        throw b::e(); // Test body throw (from inheritance mid branch).
    }
};

struct a
    #define BASES public b
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const { out << "a::inv" << std::endl; }
    static void static_invariant() { out << "a::static_inv" << std::endl; }

    ~a() {
        boost::contract::guard c = boost::contract::destructor(this)
            .old([&] { out << "a::dtor::old" << std::endl; })
            .postcondition([] { out << "a::dtor::post" << std::endl; })
        ;
        out << "a::dtor::body" << std::endl;
        // Do not throw (from inheritance leaf).
    }
};

void t() {
    std::ostringstream ok;
    ok.str(""); ok
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        << "a::dtor::old" << std::endl
        << "a::dtor::body" << std::endl
        << "a::static_inv" << std::endl
        // Test a destructed (so only static_inv and post).
        << "a::dtor::post" << std::endl

        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "b::dtor::old" << std::endl
        << "b::dtor::body" << std::endl

// TODO: Document this (even if dtors should never throw in C++ anyways...).
// Unfortunately, only Clang gets this right... Both MSVC and GCC seem to stop
// everything as soon as the destructor throws an exception...
#ifdef BOOST_CLANG
        // Test b not destructed (so both static_inv and inv, but no post).
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "c::dtor::old" << std::endl
        << "c::dtor::body" << std::endl
        // Test c not destructed (so both static_inv and inv, but no post).
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
#endif // BOOST_CLANG

    ;
    BOOST_TEST(out.eq(ok.str()));
    std::exit(boost::report_errors());
}

int main() {
    std::set_terminate(&t); // Must use terminate to handle dtor throw.
    {
        out.str("");
        a aa;
    } // Call destructor (which calls t on throw).

    BOOST_TEST(false); // Must not exit from here, but from t.
    return boost::report_errors();
}

