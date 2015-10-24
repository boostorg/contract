
// Test that OLDOF macro allows to use C++11 auto declarations.

#include <boost/contract/old.hpp>
#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/config.hpp>
#include <iostream>

int main() {
#ifdef BOOST_NO_CXX11_AUTO_DECLARATIONS
    std::cout << "No C++11 auto declarations (nothing to test)" << std::endl;
#else
    int x = 0;
    auto old_x = BOOST_CONTRACT_OLDOF(x);
    BOOST_STATIC_ASSERT(boost::is_same<decltype(old_x),
            boost::contract::old_ptr<int> >::value);

    boost::contract::virtual_* v = 0;
    char y = 'a';
    auto old_y = BOOST_CONTRACT_OLDOF(v, y);
    BOOST_STATIC_ASSERT(boost::is_same<decltype(old_y),
            boost::contract::old_ptr<char> >::value);
#endif
    return 0;
}

