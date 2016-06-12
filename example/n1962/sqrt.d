
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

