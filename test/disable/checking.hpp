
// Test contract checking and old value copies disabled within contracts.

#include "../aux_/oteststream.hpp"
#include "../aux_/counter.hpp"
#include <boost/contract/old.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/public_function.hpp>
#include <boost/contract/assert.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::test::aux::oteststream out;

struct a {
    static void static_invariant() { out << "a::static_inv" << std::endl; }
    void invariant() const { out << "a::inv" << std::endl; }

    struct x_tag;
    typedef boost::contract::test::aux::counter<x_tag, int> x_type;

    int f(x_type& x) {
        int result;
        boost::contract::old_ptr<x_type> old_x = BOOST_CONTRACT_OLDOF(
                x_type::eval(x));
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] { out << "a::f::pre" << std::endl; })
            .old([&] { out << "a::f::old" << std::endl; })
            .postcondition([&] {
                out << "a::f::post" << std::endl;
                BOOST_CONTRACT_ASSERT(x.value == -old_x->value);
                BOOST_CONTRACT_ASSERT(result == old_x->value);
            })
        ;
        out << "a::f::body" << std::endl;
        result = x.value;
        x.value = -x.value;
        return result;
    }
};

bool call_f() {
    a aa;
    a::x_type x; x.value = -123;
    return aa.f(x) == -123;
}

struct b {
    static void static_invariant() { out << "b::static_inv" << std::endl; }
    void invariant() const { out << "b::inv" << std::endl; }

    void g() {
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([&] {
                out << "b::g::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(call_f());
            })
            .old([&] { out << "b::g::old" << std::endl; })
            .postcondition([&] {
                out << "b::g::post" << std::endl;
                BOOST_CONTRACT_ASSERT(call_f());
            })
        ;
        out << "b::g::body" << std::endl;
    }
};

int main() {
    std::ostringstream ok;
    b bb;

    out.str("");
    bb.g();
    ok.str(""); ok
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_PRECONDITIONS
            << "b::g::pre" << std::endl
            #ifndef BOOST_CONTRACT_CONFIG_PRECONDITIONS_DISABLE_NOTHING
                // Test call while checking executes body (but no contracts).
                << "a::f::body" << std::endl
            #else
                // Test preconditions have disabled no contract.
                #if BOOST_CONTRACT_ENTRY_INVARIANTS
                    << "a::static_inv" << std::endl
                    << "a::inv" << std::endl
                #endif
                << "a::f::pre" << std::endl
                #if BOOST_CONTRACT_POSTCONDITIONS
                    << "a::f::old" << std::endl
                #endif
                << "a::f::body" << std::endl
                #if BOOST_CONTRACT_EXIT_INVARIANTS
                    << "a::static_inv" << std::endl
                    << "a::inv" << std::endl
                #endif
                #if BOOST_CONTRACT_POSTCONDITIONS
                    << "a::f::post" << std::endl
                #endif
            #endif
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::g::old" << std::endl
        #endif
        << "b::g::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS    
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
        #endif 
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::g::post" << std::endl
            // Test call while checking executes body (but no contracts).
            << "a::f::body" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));

    // Test old values not copied for disabled contracts.
    unsigned const cnt =
        #if defined(BOOST_CONTRACT_CONFIG_PRECONDITIONS_DISABLE_NOTHING) && \
                BOOST_CONTRACT_PRECONDITIONS && BOOST_CONTRACT_POSTCONDITIONS
            1
        #else
            0
        #endif
    ;
    BOOST_TEST_EQ(a::x_type::copies(), cnt);
    BOOST_TEST_EQ(a::x_type::evals(), cnt);
    BOOST_TEST_EQ(a::x_type::ctors(), a::x_type::dtors());

    out << std::endl;

    out.str("");
    call_f();
    // Double check a call to f outside another contract checks f's contracts.
    ok.str(""); ok
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_PRECONDITIONS
            << "a::f::pre" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::f::old" << std::endl
        #endif
        << "a::f::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::f::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

