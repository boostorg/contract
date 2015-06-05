
// Test multi pre around post error (for free func, but same for all contracts).

#include <boost/contract/free_function.hpp>
#include <boost/contract/guard.hpp>

void f() {
    boost::contract::guard c = boost::contract::free_function()
        .precondition([] {})
        .postcondition([] {})
        .precondition([] {}) // Error (multiple pre around post).
    ;
}

int main() {
    f();
    return 0;
}

