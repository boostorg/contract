
// Test error when make_old(...) not used by mistake.

#ifndef BOOST_CONTRACT_TEST_OLD_PTR_TYPE
    #error "must define BOOST_CONTRACT_TEST_OLD_PTR_TYPE"
#endif

#include <boost/contract/old.hpp>

int main() {
    int x = 1;
    // Error (missing outer make_old(...)).
    BOOST_CONTRACT_TEST_OLD_PTR_TYPE<int> old_x = boost::contract::copy_old() ?
            x : boost::contract::null_old();
    return 0;
}

