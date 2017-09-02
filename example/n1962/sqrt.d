
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

//[n1962_sqrt_d
// Extra spaces, newlines, etc. for visual alignment with this library code.



real mysqrt(real x)
    in {
        assert(x >= 0.0);
    } 
    out(result) {
        assert(std.math.fabs(result * result - x) <= 1e-6);
    } 
body {
    return std.math.sqrt(x);
}








// End.
//]

