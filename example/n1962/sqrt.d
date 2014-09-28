
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Use, modification, and distribution is subject to the
// Boost Software License, Version 1.0 (see accompanying file
// LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// Documentation at http://contractpp.sourceforge.net.

//[n1962_sqrt_d
// File: sqrt.d
// Extra spaces, newlines, etc used to align text with this library code.




real mysqrt ( real x ) // No default parameters in D.
    in { assert(x >= 0); } 
    out(root) {

        assert(std.math.fabs(root * root - x) <= 1e6);
    } 
body { 
    return std.math.sqrt(x);
}






//]

