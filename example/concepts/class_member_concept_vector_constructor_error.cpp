
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include "class_member_concept_vector.hpp"
#include <boost/utility.hpp>
#include <boost/detail/lightweight_test.hpp>

struct x {};

int main ( void )
{
    x begin, end;
    vector<int> v(begin, end); // Correctly error: `x` is not `InputIterator`.
    return 0;
}

