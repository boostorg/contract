
//[no_contracts
int inc(int& x)
    // Precondition:    x < std::numeric_limits<int>::max()
    // Postcondition:   x == oldof(x) + 1
    //                  result == oldof(x)
{
    return x++;
}
//]

