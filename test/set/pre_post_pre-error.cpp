
// Test multi pre around post error (for free func, but same for all contracts).

#include <boost/contract/free_function.hpp>
#include <boost/contract/scoped.hpp>

void f() {
    boost::contract::scoped c = boost::contract::free_function()
        .precondition([] {})
        .postcondition([] {})
        .precondition([] {}) // Error (multiple pre around post).
    ;
}

int main() {
    f();
    return 0;
}

