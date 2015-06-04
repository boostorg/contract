
// Test multi post around pre error (for free func, but same for all contracts).

#include <boost/contract/free_function.hpp>
#include <boost/contract/scoped.hpp>

void f() {
    boost::contract::scoped c = boost::contract::free_function()
        .postcondition([] {})
        .precondition([] {})
        .postcondition([] {}) // Error (multiple post around pre).
    ;
}

int main() {
    f();
    return 0;
}

