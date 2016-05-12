
//[n1962_equal
#include <boost/contract.hpp>
#include <cassert>

// Forward declaration because == and != contracts use one another's function.
template<typename T>
bool operator==(T const& left, T const& right);

template<typename T>
bool operator!=(T const& left, T const& right) {
    bool result;
    boost::contract::guard c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(result == !(left == right));
        })
    ;

    return result = (left.value != right.value);
}

template<typename T>
bool operator==(T const& left, T const& right) {
    bool result;
    boost::contract::guard c = boost::contract::function()
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

    assert((n == n) == true);   // Explicitly call operator==.
    assert((n != n) == false);  // Explicitly call operator!=.

    return 0;
}
//]

