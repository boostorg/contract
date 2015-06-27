
#include <boost/contract.hpp>
#include <boost/detail/lightweight_test.hpp>

// Forward declaration because == and != contracts use one another's function.
template<typename T>
bool operator==(T const& left, T const& right);

template<typename T>
bool operator!=(T const& left, T const& right) {
    bool result;
    auto c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(result == !(left == right));
        })
    ;

    return result = (left.value != right.value);
}

template<typename T>
bool operator==(T const& left, T const& right) {
    bool result;
    auto c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(result == !(left != right));
        })
    ;

    return result = (left.value == right.value);
}

struct number { int value; };

int main() {
    number n;
    n.value = 123;

    BOOST_TEST_EQ(n == n, true);    // Explicitly call operator==.
    BOOST_TEST_EQ(n != n, false);   // Explicitly call operator!=.

    return boost::report_errors();
}

