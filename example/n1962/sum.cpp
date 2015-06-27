
#include <boost/contract.hpp>
#include <boost/detail/lightweight_test.hpp>

int sum(int count, int* array) {
    int result;
    auto c = boost::contract::function()
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
    BOOST_TEST_EQ(sum(4, a), 10);
    return boost::report_errors();
}

