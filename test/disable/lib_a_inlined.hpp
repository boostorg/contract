
#ifndef BOOST_TEST_LIB_A_INLINED_HPP_
#define BOOST_TEST_LIB_A_INLINED_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test other contract checking disabled within contract checking [among libs].

#include "lib_a.hpp"
#include <boost/contract/public_function.hpp>
#include <boost/contract/old.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/assert.hpp>

BOOST_CONTRACT_TEST_DETAIL_OTESTSTREAM_STR_DEF(out)

void a::static_invariant() { out("a::static_inv\n"); }
void a::invariant() const { out("a::inv\n"); }

int a::f(x_type& x) {
    int result;
    boost::contract::old_ptr<x_type> old_x = BOOST_CONTRACT_OLDOF(
            x_type::eval(x));
    boost::contract::guard c = boost::contract::public_function(this)
        .precondition([&] { out("a::f::pre\n"); })
        .old([&] { out("a::f::old\n"); })
        .postcondition([&] {
            out("a::f::post\n");
            BOOST_CONTRACT_ASSERT(x.value == -old_x->value);
            BOOST_CONTRACT_ASSERT(result == old_x->value);
        })
    ;
    out("a::f::body\n");
    result = x.value;
    x.value = -x.value;
    return result;
}

void a::disable_pre_failure() {
    boost::contract::set_precondition_failure([] (boost::contract::from)
            { out("a::pre_failure\n"); });
}

void a::disable_post_failure() {
    boost::contract::set_postcondition_failure([] (boost::contract::from)
            { out("a::post_failure\n"); });
}

void a::disable_entry_inv_failure() {
    boost::contract::set_entry_invariant_failure([] (boost::contract::from)
            { out("a::entry_inv_failure\n"); });
}

void a::disable_exit_inv_failure() {
    boost::contract::set_exit_invariant_failure([] (boost::contract::from)
            { out("a::exit_inv_failure\n"); });
}

void a::disable_inv_failure() {
    boost::contract::set_invariant_failure([] (boost::contract::from)
            { out("a::inv_failure\n"); });
}

void a::disable_failure() {
    boost::contract::set_failure([] (boost::contract::from)
            { out("a::failure\n"); });
}

#endif // #include guard

