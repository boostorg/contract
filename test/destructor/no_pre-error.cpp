
// Test destructor cannot use `.precondition(...)`.

#include <boost/contract/destructor.hpp>
#include <boost/contract/var.hpp>

struct a {
    ~a() {
        boost::contract::var contract = boost::contract::destructor(this)
            .precondition([] {}) // Error (no func arg so never pre).
        ;
    }
};

int main() {
    a aa;
    return 0;
}

