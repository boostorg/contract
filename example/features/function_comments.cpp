
#include <limits>
#include <cassert>

//[no_contracts
int inc(int& x)
    // Precondition:    x < std::numeric_limits<int>::max()
    // Postcondition:   x == oldof(x) + 1
    //                  result == oldof(x)
{
    return x++;
}
//]

int main() {
    int x = std::numeric_limits<int>::max() - 1;
    assert(inc(x) == std::numeric_limits<int>::max() - 1);
    assert(x == std::numeric_limits<int>::max());
    return 0;
}

