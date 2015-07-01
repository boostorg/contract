
//[n1962_sqrt_d
// Extra newlines, etc. used to align text with this library code.




real mysqrt ( real x ) // No default parameters in D.
    in { assert(x >= 0); } 
    out(root) {

        assert(std.math.fabs(root * root - x) <= 1e6);
    } 
body { 
    return std.math.sqrt(x);
}






//]

