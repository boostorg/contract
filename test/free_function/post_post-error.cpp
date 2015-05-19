
// Test double post error (for free func, but same for all contracts).

#include <boost/contract/free_function.hpp>
#include <boost/contract/var.hpp>

void f() {
    boost::contract::var contract = boost::contract::free_function()
        .postcondition([] {})
        .postcondition([] {}) // Error (double post).
    ;
}

int main() {
    f();
    return 0;
}

