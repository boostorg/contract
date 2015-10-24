
// Test error when make_old(...) not used by mistake.

#include <boost/contract/old.hpp>

int main() {
    int x = 1;
    boost::contract::old_ptr<int> old_x = boost::contract::copy_old() ? x :
            boost::contract::make_old(); // Error (missing outer make_old(...)).
    return 0;
}

