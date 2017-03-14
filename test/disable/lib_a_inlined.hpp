
#ifndef BOOST_CONTRACT_TEST_LIB_A_INLINED_HPP_
#define BOOST_CONTRACT_TEST_LIB_A_INLINED_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include "lib_a.hpp"
#include <boost/contract/public_function.hpp>
#include <boost/contract/old.hpp>
#include <boost/contract/check.hpp>
#include <boost/contract/assert.hpp>

void a::static_invariant() {
    using boost::contract::test::detail::out;
    out("a::static_inv\n");
}

void a::invariant() const {
    using boost::contract::test::detail::out;
    out("a::inv\n");
}

int a::f(x_type& x) {
    using boost::contract::test::detail::out;
    int result;
    boost::contract::old_ptr<x_type> old_x =
            BOOST_CONTRACT_OLDOF(x_type::eval(x));
    boost::contract::check c = boost::contract::public_function(this)
        .precondition([] { out("a::f::pre\n"); })
        .old([] { out("a::f::old\n"); })
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
    using boost::contract::test::detail::out;
    boost::contract::set_precondition_failure([] (boost::contract::from)
            { out("a::pre_failure\n"); });
}

void a::disable_post_failure() {
    using boost::contract::test::detail::out;
    boost::contract::set_postcondition_failure([] (boost::contract::from)
            { out("a::post_failure\n"); });
}

void a::disable_entry_inv_failure() {
    using boost::contract::test::detail::out;
    boost::contract::set_entry_invariant_failure([] (boost::contract::from)
            { out("a::entry_inv_failure\n"); });
}

void a::disable_exit_inv_failure() {
    using boost::contract::test::detail::out;
    boost::contract::set_exit_invariant_failure([] (boost::contract::from)
            { out("a::exit_inv_failure\n"); });
}

void a::disable_inv_failure() {
    using boost::contract::test::detail::out;
    boost::contract::set_invariant_failure([] (boost::contract::from)
            { out("a::inv_failure\n"); });
}

void a::disable_failure() {
    using boost::contract::test::detail::out;
    boost::contract::set_specification_failure([] (boost::contract::from)
            { out("a::failure\n"); });
}

#endif // #include guard

