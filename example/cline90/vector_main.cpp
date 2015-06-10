
#include "vector.hpp"
#include <boost/detail/lightweight_test.hpp>

int main() {
    vector<int> v (3);
    BOOST_TEST_EQ(v.size(), 3);
    
    v[0] = 123;
    v.resize(2);
    BOOST_TEST_EQ(v[0], 123);
    BOOST_TEST_EQ(v.size(), 2);
    
    return boost::report_errors();
}

