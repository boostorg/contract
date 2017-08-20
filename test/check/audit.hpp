
// no #include guard

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/check.hpp>
#include <boost/detail/lightweight_test.hpp>

int main() {
    struct err {};
    boost::contract::set_check_failure([] { throw err(); });

    bool threw = false;
    try {
        #ifdef BOOST_CONTRACT_TEST_ERROR
            BOOST_CONTRACT_CHECK_AUDIT(some-invalid-expression);
        #else
            BOOST_CONTRACT_CHECK_AUDIT(false);
        #endif
    } catch(err const&) { threw = true; }
    
    #ifdef BOOST_CONTRACT_AUDITS
        BOOST_TEST(threw);
    #else
        BOOST_TEST(!threw);
    #endif
    
    return boost::report_errors();
}

