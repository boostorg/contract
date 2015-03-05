
// NOTE: This header does not use #include guards.

#ifndef BOOST_CONTRACT_TEST_ASSERTIONS_keyword
#   error "#undefined header macro parameter (can be #defined to empty)"
#endif
#ifndef BOOST_CONTRACT_TEST_ASSERTIONS_equal
#   error "#undefined header macro parameter"
#endif
#ifndef BOOST_CONTRACT_TEST_ASSERTIONS_check
#   error "#undefined header macro parameter"
#endif
#ifndef BOOST_CONTRACT_TEST_ASSERTIONS_if
#   error "#undefined header macro parameter"
#endif

// TODO: Fix indentation in this file.

// Test if with all then statements and no else.
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c), y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ), y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) t1, y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, ) else ( ) y, )
)

// Test if with empty then and all else statements.
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else, y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_check(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_check(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( e1, e2, ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( e1, e2, ), y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( e1, e2, ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else e1, y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( e1, ) y, )
)

// Test if with non-empty then and all else statements.
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) else, y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_check(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_check(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) else ( e1, e2, ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) else ( e1, e2, ), y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) else ( e1, e2, ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) else e1, y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) else ( e1, ) y, )
)

// Test if with no then, a comma, and all else statements (allowed in C++).
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c), else, y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c), else ( ) y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c), else ( e1, e2, ) y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( e1, e2, ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c), else ( e1, e2, ), y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( e1, e2, ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c), else e1, y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( e1, ) y, )
)

// Test if with no then and all else statements (not allowed by C++ for no
// reason... so allowed by this syntax so less cryptic errors).
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) else, y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) else ( ) y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) else ( e1, e2, ) y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( e1, e2, ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) else ( e1, e2, ), y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( e1, e2, ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) else e1, y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( e1, ) y, )
)

// Test if with empty then, a comma, and all else statements (not allowed by
// C++ for no reason... so allowed by this syntax so less cryptic errors).
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ), else, y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ), else ( ) y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ), else ( e1, e2, ) y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( e1, e2, ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ), else ( e1, e2, ), y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( e1, e2, ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ), else e1, y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( ) else ( e1, ) y, )
)

// Test if with non-empty then, a comma, and all else statements (not
// allowed by C++ for no reason... so allowed by this syntax so less
// cryptic errors).
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ), else, y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ), else ( ) y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ), else ( e1, e2, ) y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) else ( e1, e2, ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ), else ( e1, e2, ), y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) else ( e1, e2, ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ), else e1, y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) else ( e1, ) y, )
)
// Test same as above with single then statement.    
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) t1, else, y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) t1, else ( ) y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, ) else ( ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) t1, else ( e1, e2, ) y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, ) else ( e1, e2, ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) t1, else ( e1, e2, ), y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, ) else ( e1, e2, ) y, )
)
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) t1, else e1, y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, ) else ( e1, ) y, )
)

// Extra else correctly treated as a boolean-assertion `bool(else e2)`.
BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ), else e1, else e2, y, ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword( x, BOOST_CONTRACT_TEST_ASSERTIONS_if(c) ( t1, t2, ) else ( e1, ) bool(else e2), y, )
)

BOOST_CONTRACT_TEST_ASSERTIONS_equal(
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword(
        x,
        BOOST_CONTRACT_TEST_ASSERTIONS_if(c) (
            t1,
            t2,
        ) else BOOST_CONTRACT_TEST_ASSERTIONS_if(cc) (
            tt1,
            tt2,
        ) else BOOST_CONTRACT_TEST_ASSERTIONS_if(ccc) (
            ttt1,
            ttt2,
        ) else (
            e1,
            e2,
        )
        y,
    ),
    BOOST_CONTRACT_TEST_ASSERTIONS_keyword(
        x,
        BOOST_CONTRACT_TEST_ASSERTIONS_if(c) (
            t1,
            t2,
        ) else (
            BOOST_CONTRACT_TEST_ASSERTIONS_if(cc) (
                tt1,
                tt2,
            ) else (
                BOOST_CONTRACT_TEST_ASSERTIONS_if(ccc) (
                    ttt1,
                    ttt2,
                ) else (
                    e1,
                    e2,
                )
            )
        )
        y,
    )
)

