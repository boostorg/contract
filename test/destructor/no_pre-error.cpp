
// Test destructor cannot use `.precondition(...)`.

#include <boost/contract/destructor.hpp>
#include <boost/contract/scoped.hpp>

struct a {
    ~a() {
        boost::contract::scoped c = boost::contract::destructor(this)
            .precondition([] {}) // Error (no dtor func arg so never pre).
        ;
    }
};

int main() {
    a aa;
    return 0;
}

