/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include <dbc.hpp>
#include <iostream>
#include <algorithm>

/** Calculate greater common denominator. */
int gcd(const int& a, const int& b) {
    class GcdLoop: dbc::loop {
    public:
        int x, y;
        GcdLoop(const int& a, const int& b): x(a), y(b) 
                { run(__FILE__, __LINE__); }
    private:
        void invariant() {
            DBC_ASSERT(x > 0, "positive x");
            DBC_ASSERT(y > 0, "positive y");
        }
        unsigned int variant() { return std::max(x, y); }
        bool until() { return x == y; }
        void body() {
            if (x > y) { x = x - y; }
            else { y = y - x; }
            // The "else" above with one commented out below, intentionally 
            // introcuces a bug: it assigns x instead of y. This bug is catched
            // by a loop variant violation -- try it!
            //  else { x = y - x; }
        }
    } gcdLoop(a, b);
    return gcdLoop.x;
}

/** Main program. */
int main() {
    int a = 6, b = 12;
    std::cout << "Greatest Common Divisor: GCD(" << a << ", " << b << ") = " 
            << gcd(a, b) << std::endl;
    return 0;
}

