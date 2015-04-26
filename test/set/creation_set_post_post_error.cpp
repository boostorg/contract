
#include <boost/contract/constructor.hpp>

// Test post cannot be set twice for constructors
// (destructors use same setter objects, so no need to test those too).

struct a {
    explicit a() {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {})
            .postcondition([&] {}) // Error.
        ;
    }
};

int main() {
    a aa;
    return 0;
}

