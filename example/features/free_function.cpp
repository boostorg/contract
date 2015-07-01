
//[free_function
#include <boost/contract.hpp>

int inc(int& x) {
    int result;
    boost::shared_ptr<int const> old_x = BOOST_CONTRACT_OLDOF(x);
    boost::contract::guard c = boost::contract::function()
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(x < std::numberic_limits<int>::max());
        })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(x == *old_x + 1);
            BOOST_CONTRACT_ASSERT(result == *old_x);
        })
    ;

    return result = x++; // Function body.
}
//]

