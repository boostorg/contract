
// Test multiple post error (for free func, but same for all contracts).

#include <boost/contract/function.hpp>
#include <boost/contract/guard.hpp>

void f() {
    boost::contract::guard c = boost::contract::function()
        .postcondition([] {})
        .postcondition([] {}) // Error (multiple post).
    ;
}

int main() {
    f();
    return 0;
}

