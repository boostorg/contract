
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n2081_find_error
// File: find_error.cpp
#include "find.hpp"
#include <vector>

struct num
{
    int value;
    explicit num ( int v = 0 ) : value(v) {}
};

int main ( void )
{
    std::vector<num> nums(3);
    nums[0] = num(1); nums[1] = num(2); nums[2] = num(3);
    // Error: Correctly, num does not meet concept requirements.
    myfind(nums.begin(), nums.end(), num(2));
    return 0;
}
//]

