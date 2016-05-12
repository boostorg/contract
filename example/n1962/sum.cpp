
//[n1962_sum
#include <boost/contract.hpp>
#include <cassert>

int sum(int count, int* array) {
    int result;
    boost::contract::guard c = boost::contract::function()
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(count % 4 == 0);
        })
    ;

    result = 0;
    for(int i = 0; i < count; ++i) result += array[i];
    return result;
}

int main() {
    int a[4] = {1, 2, 3, 4};
    assert(sum(4, a) == 10);
    return 0;
}
//]

