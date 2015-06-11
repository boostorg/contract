
// Test multi post around pre error (for free func, but same for all contracts).

#include <boost/contract/function.hpp>
#include <boost/contract/guard.hpp>

void f() {
    boost::contract::guard c = boost::contract::function()
        .postcondition([] {})
        .precondition([] {})
        .postcondition([] {}) // Error (multiple post around pre).
    ;
}

int main() {
    f();
    return 0;
}

