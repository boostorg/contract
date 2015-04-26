
#include <boost/contract/free_function.hpp>

// Test pre cannot be set twice for free functions
// (member functions use same setter objects, so no need to test those too).

int main() {
    auto c = boost::contract::free_function()
        .precondition([&] {})
        .precondition([&] {}) // Error.
    ;
    return 0;
}

