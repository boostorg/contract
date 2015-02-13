
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_POSTCONDITIONS_INDEX
#include "../aux_/pp_traits.hpp"
#include <boost/contract/oldof.hpp>
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_CONTRACT_TEST_(postconditions) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARSE_D, \
        /*(std::map<int, char>&)*/ (f) ( ) \
                throw(int, double) override final, \
        postconditions, \
        remove_this_trailing_stuff, \
        postconditions \
    )

#define oldof BOOST_CONTRACT_OLDOF

int main ( ) {
    BOOST_CONTRACT_TEST_( BOOST_PP_EMPTY() )

    BOOST_CONTRACT_TEST_( postcondition( ) )

    BOOST_CONTRACT_TEST_( postcondition( x >= 0, y, z ) )

    BOOST_CONTRACT_TEST_(
        postcondition(
//            namespace (py) as boost::python,
//
//            // Using directives.
//            using namespace std,
//            // Using declarations.
//            using std::placeholders::_1,
//            using typename T::value_type,
//            using (std::map<int, char>::insert),
//            using (typename M<int, char>::key_type),
//            // Using aliases.
//            using (iv) as vector<int>,
//            using (icmap) as (map<int, char>),
//            template( typename T ) using (vt) as vector<T>,
//            template( typename T, int U ) using (xtu) as (x<T, int, U>),
//
//            typedef unsigned long ul,
//            typedef (map<int, char>) icmap,
//
//            auto result1 = return,
//            int const result2 = return,
//            (map<int, char> const&) result3 = return,
//
            auto old_size = BOOST_CONTRACT_OLDOF v.size(),
            unsigned int const old_capacity = oldof v.capacity(),
            (map<int, char> const) old_map =
                    BOOST_CONTRACT_OLDOF (map<int, char>::clone(m)),
//
//            x >= 0,
//            x == 0 ? !result : true,
//            (!y),
//            (std::map<int, char>::key_size > 0),
//
//            const( std::cout ) !std::cout.error(),
//            const( std::cout, x ) std::cout.flags == x,
//            const( ) true,
//            const( int const n, x, (::std::map<int, char> const&) m )
//                    (m.size() == map<int, char>::key_size == x),

            if(const( int const x ) x >= 0) (
                a >= 0,
                typedef bool b,
                auto c = return,
                long long const d = BOOST_CONTRACT_OLDOF v.size(),
                d >= v.size(),
            ) else (
                x,
                y,
                z,
            )
            u, v, w,

        )
    )
    
    // Test if with all then statements and no else.
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c),
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( )
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( t1, t2, )
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( t1, t2, ),
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) t1,
    after, ) )
    
    // Test if with empty then and all else statements.
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( ) else,
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( ) else ( )
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( ) else ( e1, e2, )
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( ) else ( e1, e2, ),
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( ) else e1,
    after, ) )

    // Test if with non-empty then and all else statements.
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( t1, t2, ) else,
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( t1, t2, ) else ( )
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( t1, t2, ) else ( e1, e2, )
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( t1, t2, ) else ( e1, e2, ),
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( t1, t2, ) else e1,
    after, ) )
    
    // Test if with no then, a comma, and all else statements (allowed in C++).
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c), else,
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c), else ( )
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c), else ( e1, e2, )
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c), else ( e1, e2, ),
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c), else e1,
    after, ) )
    
    // Test if with no then and all else statements (not allowed by C++ for no
    // reason... so allowed by this syntax so less cryptic errors).
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) else,
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) else ( )
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) else ( e1, e2, )
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) else ( e1, e2, ),
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) else e1,
    after, ) )
    
    // Test if with empty then, a comma, and all else statements (not allowed by
    // C++ for no reason... so allowed by this syntax so less cryptic errors).
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( ), else,
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( ), else ( )
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( ), else ( e1, e2, )
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( ), else ( e1, e2, ),
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( ), else e1,
    after, ) )

    // Test if with non-empty then, a comma, and all else statements (not
    // allowed by C++ for no reason... so allowed by this syntax so less
    // cryptic errors).
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( t1, t2, ), else,
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( t1, t2, ), else ( )
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( t1, t2, ), else ( e1, e2, )
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( t1, t2, ), else ( e1, e2, ),
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( t1, t2, ), else e1,
    after, ) )
    
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) t1, else,
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) t1, else ( )
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) t1, else ( e1, e2, )
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) t1, else ( e1, e2, ),
    after, ) )
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) t1, else e1,
    after, ) )
    
    // Extra else correctly threated as a boolean-assertion `bool(else e2)`.
    BOOST_CONTRACT_TEST_( postcondition( before,
        if(c) ( t1, t2, ), else e1, else e2,
    after, ) )

    // TODO: Test `if ... else if ...` and `static if ... else if ...` (note
    // that static-if's else-if does NOT repeat static but it is still static).
    
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

