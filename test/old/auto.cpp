
// Test that OLDOF macro allows to use C++11 auto declarations.

#include <boost/config.hpp>
#ifndef BOOST_NO_CXX11_AUTO_DECLARATIONS
    #include <boost/contract/old.hpp>
    #include <boost/type_traits.hpp>
    #include <boost/static_assert.hpp>
#endif

int main() {
    #ifndef BOOST_NO_CXX11_AUTO_DECLARATIONS
        int x = 0;
        auto old_x = BOOST_CONTRACT_OLDOF(x);
        BOOST_STATIC_ASSERT(boost::is_same<decltype(old_x),
                boost::contract::old_ptr<int> >::value);

        boost::contract::virtual_* v = 0;
        char y = 'a';
        auto old_y = BOOST_CONTRACT_OLDOF(v, y);
        BOOST_STATIC_ASSERT(boost::is_same<decltype(old_y),
                boost::contract::old_ptr<char> >::value);
    #endif // Else, nothing to test.
    return 0;
}

