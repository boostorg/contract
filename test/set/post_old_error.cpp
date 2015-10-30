
// Test post before old error (for free func, but same for all contracts).

#include <boost/contract/function.hpp>
#include <boost/contract/guard.hpp>

void f() {
    boost::contract::guard c = boost::contract::function()
        .postcondition([] {}) // Error (post before old).
        .old([] {})
    ;
}

int main() {
    f();
    return 0;
}

