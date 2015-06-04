
// Test multiple post error (for free func, but same for all contracts).

#include <boost/contract/free_function.hpp>
#include <boost/contract/scoped.hpp>

void f() {
    boost::contract::scoped c = boost::contract::free_function()
        .postcondition([] {})
        .postcondition([] {}) // Error (multiple post).
    ;
}

int main() {
    f();
    return 0;
}

