
// Test constructor cannot use `.precondition(...)`.

#include <boost/contract/constructor.hpp>
#include <boost/contract/guard.hpp>

struct a {
    a() {
        boost::contract::guard c = boost::contract::constructor(this)
            .precondition([] {}) // Error (must use constructor_precondition).
        ;
    }
};

int main() {
    a aa;
    return 0;
}

