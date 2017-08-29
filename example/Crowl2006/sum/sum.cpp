// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include "sum.hpp"

double CONTRACT_BODY(sum)(int count, double* array) {
    double accum = 0.0;
    for (int i = 0; i < count; ++i) accum += array[i];
    return accum;
}

