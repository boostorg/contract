
#include <boost/contract/constructor.hpp>

// Test pre cannot be set for constructors
// (destructors use same setter objects, so no need to test those too).

struct a {
    explicit a() {
        auto c = boost::contract::constructor(this)
            .precondition([&] {}) // Error.
        ;
    }
};

int main() {
    a aa;
    return 0;
}

