
#include <boost/contract.hpp>
#include <vector>
#include <algorithm>
#include <limits>

int main() {
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    //[lambda_function
    int total = 0;
    std::for_each(v.cbegin(), v.cend(),
        // Contract for a lambda function.
        [&total] (int const x) {
            boost::contract::old_ptr<int> old_total = BOOST_CONTRACT_OLD(total);
            boost::contract::check c = boost::contract::function()
                .precondition([&] {
                    BOOST_CONTRACT_ASSERT(
                            total + x <= std::numeric_limits<int>::max());
                })
                .postcondition([&] {
                    BOOST_CONTRACT_ASSERT(total == *old_total + x);
                })
            ;

            total += x; // Lambda function body.
        }
    );
    //]

    assert(total == 6);
    return 0;
}

