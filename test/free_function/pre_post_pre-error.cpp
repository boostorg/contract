
// Test double pre error (for free func, but same for all contracts).

#include <boost/contract/free_function.hpp>
#include <boost/contract/var.hpp>

void f() {
    boost::contract::var contract = boost::contract::free_function()
        .precondition([] {})
        .postcondition([] {})
        .precondition([] {}) // Error (double pre, after a post).
    ;
}

int main() {
    f();
    return 0;
}

