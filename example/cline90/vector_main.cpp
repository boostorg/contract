
//[cline90_vector_main
#include "vector.hpp"
#include <cassert>

int main() {
    vector<int> v (3);
    assert(v.size() == 3);
    
    v[0] = 123;
    v.resize(2);
    assert(v[0] == 123);
    assert(v.size() == 2);
    
    return 0;
}
//]

