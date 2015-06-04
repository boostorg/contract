
// Test constructor cannot use `.precondition(...)`.

#include <boost/contract/constructor.hpp>
#include <boost/contract/scoped.hpp>

struct a {
    a() {
        boost::contract::scoped c = boost::contract::constructor(this)
            .precondition([] {}) // Error (must use constructor_precondition).
        ;
    }
};

int main() {
    a aa;
    return 0;
}

