
-- Copyright (C) 2008-2012 Lorenzo Caminiti
-- Use, modification, and distribution is subject to the
-- Boost Software License, Version 1.0 (see accompanying file
-- LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
-- Documentation at http://contractpp.sourceforge.net.

//[meyer97_gcd_e
-- File: gcd.e
-- Extra spaces, newlines, etc used to align text with this library code.



-- Greatest common divisor of a and b.
gcd ( a, b : INTEGER ) : INTEGER is
    require
        a > 0; b > 0
    local
        x, y : INTEGER
    do
        from
            x := a; y := b
        invariant
            x > 0; y > 0
        variant
            x.max(y)
        until
            x = y
        loop
            if x > y then x := x - y else y := y - x end
        end
        Result := x
    end







//]

