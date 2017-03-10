
#include <boost/contract.hpp>
#include <vector>
#include <algorithm>
#include <limits>

int main() {
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    int total = 10;
    
    //[code_block
    {
        // Contract for a code block.
        boost::contract::old_ptr<int> old_total = BOOST_CONTRACT_OLDOF(total);
        boost::contract::check c = boost::contract::function()
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(v.size() == 3);
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(total == *old_total + v[0] + v[1] + v[2]);
            })
        ;

        total += v[0] + v[1] + v[2]; // Code block body.
    }
    //]

    assert(total == 16);
    return 0;
}

