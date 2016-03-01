
#ifndef BOOST_TEST_LIB_B_INLINED_HPP_
#define BOOST_TEST_LIB_B_INLINED_HPP_

// Test other contract checking disabled within contract checking [among libs].

#include "lib_b.hpp"
#include "lib_a.hpp"
#include <boost/contract/public_function.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/assert.hpp>

bool call_f() {
    a aa;
    a::x_type x; x.value = -123;
    return aa.f(x) == -123;
}

void b::static_invariant() { out("b::static_inv\n"); }
void b::invariant() const { out("b::inv\n"); }
    
void b::g() {
    boost::contract::guard c = boost::contract::public_function(this)
        .precondition([&] {
            out("b::g::pre\n");
            BOOST_CONTRACT_ASSERT(call_f());
        })
        .old([&] { out("b::g::old\n"); })
        .postcondition([&] {
            out("b::g::post\n");
            BOOST_CONTRACT_ASSERT(call_f());
        })
    ;
    out("b::g::body\n");
}

bool b::test_disable_pre_failure() {
    a::disable_pre_failure();
    out("");
    boost::contract::precondition_failure(boost::contract::from());
    return boost::contract::test::detail::oteststream::eq(out(),
            "a::pre_failure");
}

bool b::test_disable_post_failure() {
    a::disable_post_failure();
    out("");
    boost::contract::postcondition_failure(boost::contract::from());
    return boost::contract::test::detail::oteststream::eq(out(),
            "a::post_failure");
}
    
bool b::test_disable_entry_inv_failure() {
    a::disable_entry_inv_failure();
    out("");
    boost::contract::entry_invariant_failure(boost::contract::from());
    return boost::contract::test::detail::oteststream::eq(out(),
            "a::entry_inv_failure");
}
    
bool b::test_disable_exit_inv_failure() {
    a::disable_exit_inv_failure();
    out("");
    boost::contract::exit_invariant_failure(boost::contract::from());
    return boost::contract::test::detail::oteststream::eq(out(),
            "a::exit_inv_failure");
}
    
bool b::test_disable_inv_failure() {
    a::disable_inv_failure();
    out("");
    boost::contract::entry_invariant_failure(boost::contract::from());
    bool entry_inv = boost::contract::test::detail::oteststream::eq(out(),
            "a::inv_failure");
    out("");
    boost::contract::exit_invariant_failure(boost::contract::from());
    bool exit_inv = boost::contract::test::detail::oteststream::eq(out(),
            "a::inv_failure");
    return entry_inv && exit_inv;
}
    
bool b::test_disable_failure() {
    a::disable_failure();
    out("");
    boost::contract::precondition_failure(boost::contract::from());
    bool pre = boost::contract::test::detail::oteststream::eq(out(),
            "a::failure");
    out("");
    boost::contract::postcondition_failure(boost::contract::from());
    bool post = boost::contract::test::detail::oteststream::eq(out(),
            "a::failure");
    out("");
    boost::contract::entry_invariant_failure(boost::contract::from());
    bool entry_inv = boost::contract::test::detail::oteststream::eq(out(),
            "a::failure");
    out("");
    boost::contract::exit_invariant_failure(boost::contract::from());
    bool exit_inv = boost::contract::test::detail::oteststream::eq(out(),
            "a::failure");
    return pre && post && entry_inv && exit_inv;
}

#endif // #include guard

