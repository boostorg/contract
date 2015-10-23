
// Test contract checking and old value copies disabled within contracts.

#include "../aux_/oteststream.hpp"
#include "../aux_/counter.hpp"
#include <boost/contract/oldof.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/public_function.hpp>
#include <boost/contract/assert.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct a {
    void invariant() const { out << "a::inv" << std::endl; }
    static void static_invariant() { out << "a::static_inv" << std::endl; }

    struct x_tag;
    typedef boost::contract::aux::test::counter<x_tag, int> x_type;

    int f(x_type& x) {
        int result;
        boost::shared_ptr<x_type const> old_x = BOOST_CONTRACT_OLDOF(
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
    void invariant() const { out << "b::inv" << std::endl; }
    static void static_invariant() { out << "b::static_inv" << std::endl; }

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
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        
        << "b::g::pre" << std::endl
        // Test only f's body (but not its contract) executed here.
        << "a::f::body" << std::endl

        << "b::g::old" << std::endl

        << "b::g::body" << std::endl
        
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        
        // No old call here because not a base object.
        << "b::g::post" << std::endl
        // Test only f's body (but not its contract) executed here.
        << "a::f::body" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    // Test old values not copied for disabled contracts.
    BOOST_TEST_EQ(a::x_type::copies(), 0); BOOST_TEST_EQ(a::x_type::evals(), 0);

    out << std::endl;

    out.str("");
    call_f();
    // Double check a call to f outside another contract checks f's contracts.
    ok.str(""); ok
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        << "a::f::pre" << std::endl
        << "a::f::old" << std::endl
        << "a::f::body" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        // No old call here because not a base object.
        << "a::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

