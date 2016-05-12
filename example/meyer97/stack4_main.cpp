
//[meyer97_stack4_main
#include "stack4.hpp"
#include <cassert>

int main() {
    stack4<int> s(3);
    assert(s.capacity() == 3);
    assert(s.count() == 0);
    assert(s.empty());
    assert(!s.full());

    s.put(123);
    assert(!s.empty());
    assert(!s.full());
    assert(s.item() == 123);

    s.remove();
    assert(s.empty());
    assert(!s.full());

    return 0;
}
//]

