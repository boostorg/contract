
#include <boost/contract/free_function.hpp>

// Test post cannot be set twice (not even after pre) for free functions
// (member functions use same setter object, so no need to test those too).

int main() {
    auto c = boost::contract::free_function()
        .precondition([&] {})
        .postcondition([&] {})
        .postcondition([&] {}) // Error.
    ;
    return 0;
}

