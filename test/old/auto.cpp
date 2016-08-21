
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test that OLD macro allows to use C++11 auto declarations.

#include <boost/config.hpp>
#ifndef BOOST_NO_CXX11_AUTO_DECLARATIONS
    #include <boost/contract/old.hpp>
    #include <boost/type_traits.hpp>
    #include <boost/static_assert.hpp>
#endif

int main() {
    #ifndef BOOST_NO_CXX11_AUTO_DECLARATIONS
        int x = 0;
        auto old_x = BOOST_CONTRACT_OLD(x);
        BOOST_STATIC_ASSERT(boost::is_same<decltype(old_x),
                boost::contract::old_ptr<int> >::value);

        boost::contract::virtual_* v = 0;
        char y = 'a';
        auto old_y = BOOST_CONTRACT_OLD(v, y);
        BOOST_STATIC_ASSERT(boost::is_same<decltype(old_y),
                boost::contract::old_ptr<char> >::value);
    #endif // Else, nothing to test.
    return 0;
}

