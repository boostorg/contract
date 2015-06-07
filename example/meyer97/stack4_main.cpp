
#include "stack4.hpp"
#include <boost/detail/lightweight_test.hpp>

int main() {
    stack4<int> s(3);
    BOOST_TEST_EQ(s.capacity(), 3);
    BOOST_TEST_EQ(s.count(), 0);
    BOOST_TEST(s.empty());
    BOOST_TEST(!s.full());

    s.put(123);
    BOOST_TEST(!s.empty());
    BOOST_TEST(!s.full());
    BOOST_TEST_EQ(s.item(), 123);

    s.remove();
    BOOST_TEST(s.empty());
    BOOST_TEST(!s.full());

    return boost::report_errors();
}

