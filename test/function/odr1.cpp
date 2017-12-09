
#include <boost/contract.hpp>
#include <cassert>

extern int f();

int main() {
    assert(f() == 123);
    return 0;
}

