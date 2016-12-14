
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test throw from free function .except().

#include "../detail/oteststream.hpp"
#include <boost/contract/function.hpp>
#include <boost/contract/check.hpp>
#include <boost/contract/assert.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::test::detail::oteststream out;

struct err {};
struct body_err {};

void f() {
    boost::contract::check c = boost::contract::function()
        .precondition([] { out << "f::pre" << std::endl; })
        .old([] { out << "f::old" << std::endl; })
        .postcondition([] { out << "f::post" << std::endl; })
        .except([] {
            try { throw; } catch(...) {}
            out << "f::except" << std::endl;
            BOOST_CONTRACT_ASSERT(false);
            throw err();
            //try { throw; }
            //catch(body_err const&) { throw err(); } // Test this throws.
        })
    ;
    out << "f::body" << std::endl;
    throw body_err();
}

int main() {
    std::ostringstream ok;

    boost::contract::set_except_failure(
            [] (boost::contract::from) { throw; });

    try {
        out.str("");
        f();
#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        BOOST_TEST(false);
    } catch(err const&) {
#endif
        ok.str(""); ok << "" // Suppress a warning.
            #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                << "f::pre" << std::endl
            #endif
            #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                    !defined(BOOST_CONTRACT_NO_EXCEPTS)
                << "f::old" << std::endl
            #endif
            << "f::body" << std::endl
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                << "f::post" << std::endl // Test this threw.
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

