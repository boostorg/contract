
#include <limits>
#include <cassert>

//[function
#include <boost/contract.hpp>

int inc(int& x) {
    int result;
    boost::contract::old_ptr<int> old_x = BOOST_CONTRACT_OLDOF(x);
    boost::contract::guard c = boost::contract::function()
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(x < std::numeric_limits<int>::max());
        })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(x == *old_x + 1);
            BOOST_CONTRACT_ASSERT(result == *old_x);
        })
    ;

    return result = x++; // Function body.
}
//]

int main() {
    int x = std::numeric_limits<int>::max() - 1;
    assert(inc(x) == std::numeric_limits<int>::max() - 1);
    assert(x == std::numeric_limits<int>::max());
    return 0;
}

