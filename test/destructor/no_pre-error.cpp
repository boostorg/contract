
// Test destructor cannot use `.precondition(...)`.

#include <boost/contract/destructor.hpp>
#include <boost/contract/guard.hpp>

struct a {
    ~a() {
        boost::contract::guard c = boost::contract::destructor(this)
            .precondition([] {}) // Error (no dtor func arg so never pre).
        ;
    }
};

int main() {
    a aa;
    return 0;
}

