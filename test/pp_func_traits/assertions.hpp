
// NOTE: This header does not use #include guards.

#ifndef BOOST_CONTRACT_TEST_ASSERTIONS_equal
#   error "#undefined header macro parameter"
#endif
#ifndef BOOST_CONTRACT_TEST_ASSERTIONS_check
#   error "#undefined header macro parameter"
#endif
#ifndef BOOST_CONTRACT_TEST_ASSERTIONS_post
#   error "#undefined header macro parameter (can be #defined to empty)"
#endif
#ifndef BOOST_CONTRACT_TEST_ASSERTIONS_post_if
#   error "#undefined header macro parameter (can be #defined to empty)"
#endif

// Test no postconditions.
BOOST_CONTRACT_TEST_ASSERTIONS_equal( BOOST_PP_EMPTY(), ( ) )
// Test empty postconditions.
BOOST_CONTRACT_TEST_ASSERTIONS_check( ( ) )

// Test no trailing comma.
BOOST_CONTRACT_TEST_ASSERTIONS_equal( ( x >= 0, y, z ), ( x >= 0, y, z, ) )

// Test everything together.
BOOST_CONTRACT_TEST_ASSERTIONS_check( (
    before,

    namespace (py) as boost::python,

    // Using directives.
    using namespace std,
    // Using declarations.
    using std::placeholders::_1,
    using typename T::value_type,
    using (std::map<int, char>::insert),
    using (typename M<int, char>::key_type),
    // Using aliases.
    using (iv) as vector<int>,
    using (icmap) as (map<int, char>),
    template( typename T ) using (vt) as vector<T>,
    template( typename T, int U ) using (xtu) as (x<T, int, U>),

    typedef unsigned long ul,
    typedef (map<int, char>) icmap,

    BOOST_CONTRACT_TEST_ASSERTIONS_post

    const( std::cout ) !std::cout.error(),
    const( std::cout, x ) std::cout.flags == x,
    const( ) true,
    const( int const n, x, (::std::map<int, char> const&) m )
            (m.size() == map<int, char>::key_size == x),

    x >= 0,
    x == 0 ? !result : true,
    (!y),
    (std::map<int, char>::key_size > 0),


    if(m<a, b>::value) (
        a >= 0,
        typedef bool b,

        BOOST_CONTRACT_TEST_ASSERTIONS_post_if
        
        d >= v.size(),
    ) else (
        x,
        if(const( y, z ) y >= z) (
            y,
            z,
        ) else (
            u,
            v,
        )
        // TODO: A `static if ...` seems to not work... why? Test it.
        w,
    )

    static if(is_same<X, Y>::value) (
        x == y,
    ) else (
        x,
        y,
    )

    after,
) )

#define BOOST_CONTRACT_TEST_ASSERTIONS_if if
#include "./if_assertions.hpp" // Include actual if-assertion tests.
#undef BOOST_CONTRACT_TEST_ASSERTIONS_if

#define BOOST_CONTRACT_TEST_ASSERTIONS_if static if
#include "./if_assertions.hpp" // Include actual static-if-assertion tests.
#undef BOOST_CONTRACT_TEST_ASSERTIONS_if

