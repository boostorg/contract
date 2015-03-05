
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_POSTCONDITIONS_INDEX
#include "../aux_/pp_traits.hpp"
#include "../aux_/pp_assertions.hpp"
#include "../aux_/pp_tuple.hpp"
#include <boost/contract/oldof.hpp>
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_CONTRACT_TEST_POSTCONDITIONS_(func_traits) \
    postcondition \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS(func_traits)), \
        () BOOST_PP_TUPLE_EAT(3) \
    , \
        BOOST_PP_SEQ_FOLD_LEFT \
    )(BOOST_CONTRACT_TEST_AUX_PP_POST_ASSERTIONS_S_1, (), \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS(func_traits))

#define BOOST_CONTRACT_TEST_EQUAL_(postconditions, parsed_postconditions) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_TEST_POSTCONDITIONS_, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARSE_D, \
        (std::map<int, char>&) (f) ( ) \
                throw(int, double) override final, \
        postconditions, \
        BOOST_PP_EMPTY(), \
        parsed_postconditions \
    )

#define BOOST_CONTRACT_TEST_(postconditions) \
    BOOST_CONTRACT_TEST_EQUAL_(postconditions, postconditions)

#define oldof BOOST_CONTRACT_OLDOF

int main ( ) {
    // Test no postconditions.
    BOOST_CONTRACT_TEST_EQUAL_( BOOST_PP_EMPTY(), postcondition( ) )
    // Test empty postconditions.
    BOOST_CONTRACT_TEST_( postcondition( ) )

    // Test no trailing comma.
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x >= 0, y, z ),
        postcondition( x >= 0, y, z, )
    )

    // Test everything together.
    BOOST_CONTRACT_TEST_( postcondition(
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

        auto result1 = return,
        int const result2 = return,
        (map<int, char> const&) result3 = return,

        auto old_size = BOOST_CONTRACT_OLDOF v.size(),
        unsigned int const old_capacity = oldof v.capacity(),
        (map<int, char> const) old_map =
                BOOST_CONTRACT_OLDOF (map<int, char>::clone(m)),

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
            auto c = return,
            long long const d = BOOST_CONTRACT_OLDOF v.size(),
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
    
    // Test if with all then statements and no else.
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c), y, ),
        postcondition( x, if(c) ( ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( ) y, ),
        postcondition( x, if(c) ( ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( t1, t2, ) y, ),
        postcondition( x, if(c) ( t1, t2, ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( t1, t2, ), y, ),
        postcondition( x, if(c) ( t1, t2, ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) t1, y, ),
        postcondition( x, if(c) ( t1, ) else ( ) y, )
    )
    
    // Test if with empty then and all else statements.
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( ) else, y, ),
        postcondition( x, if(c) ( ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_(
        postcondition( x, if(c) ( ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_(
        postcondition( x, if(c) ( ) else ( e1, e2, ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( ) else ( e1, e2, ), y, ),
        postcondition( x, if(c) ( ) else ( e1, e2, ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( ) else e1, y, ),
        postcondition( x, if(c) ( ) else ( e1, ) y, )
    )

    // Test if with non-empty then and all else statements.
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( t1, t2, ) else, y, ),
        postcondition( x, if(c) ( t1, t2, ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_(
        postcondition( x, if(c) ( t1, t2, ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_(
        postcondition( x, if(c) ( t1, t2, ) else ( e1, e2, ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( t1, t2, ) else ( e1, e2, ), y, ),
        postcondition( x, if(c) ( t1, t2, ) else ( e1, e2, ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( t1, t2, ) else e1, y, ),
        postcondition( x, if(c) ( t1, t2, ) else ( e1, ) y, )
    )
    
    // Test if with no then, a comma, and all else statements (allowed in C++).
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c), else, y, ),
        postcondition( x, if(c) ( ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c), else ( ) y, ),
        postcondition( x, if(c) ( ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c), else ( e1, e2, ) y, ),
        postcondition( x, if(c) ( ) else ( e1, e2, ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c), else ( e1, e2, ), y, ),
        postcondition( x, if(c) ( ) else ( e1, e2, ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c), else e1, y, ),
        postcondition( x, if(c) ( ) else ( e1, ) y, )
    )
    
    // Test if with no then and all else statements (not allowed by C++ for no
    // reason... so allowed by this syntax so less cryptic errors).
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) else, y, ),
        postcondition( x, if(c) ( ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) else ( ) y, ),
        postcondition( x, if(c) ( ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) else ( e1, e2, ) y, ),
        postcondition( x, if(c) ( ) else ( e1, e2, ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) else ( e1, e2, ), y, ),
        postcondition( x, if(c) ( ) else ( e1, e2, ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) else e1, y, ),
        postcondition( x, if(c) ( ) else ( e1, ) y, )
    )
    
    // Test if with empty then, a comma, and all else statements (not allowed by
    // C++ for no reason... so allowed by this syntax so less cryptic errors).
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( ), else, y, ),
        postcondition( x, if(c) ( ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( ), else ( ) y, ),
        postcondition( x, if(c) ( ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( ), else ( e1, e2, ) y, ),
        postcondition( x, if(c) ( ) else ( e1, e2, ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( ), else ( e1, e2, ), y, ),
        postcondition( x, if(c) ( ) else ( e1, e2, ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( ), else e1, y, ),
        postcondition( x, if(c) ( ) else ( e1, ) y, )
    )

    // Test if with non-empty then, a comma, and all else statements (not
    // allowed by C++ for no reason... so allowed by this syntax so less
    // cryptic errors).
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( t1, t2, ), else, y, ),
        postcondition( x, if(c) ( t1, t2, ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( t1, t2, ), else ( ) y, ),
        postcondition( x, if(c) ( t1, t2, ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( t1, t2, ), else ( e1, e2, ) y, ),
        postcondition( x, if(c) ( t1, t2, ) else ( e1, e2, ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( t1, t2, ), else ( e1, e2, ), y, ),
        postcondition( x, if(c) ( t1, t2, ) else ( e1, e2, ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( t1, t2, ), else e1, y, ),
        postcondition( x, if(c) ( t1, t2, ) else ( e1, ) y, )
    )
    // Test same as above with single then statement.    
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) t1, else, y, ),
        postcondition( x, if(c) ( t1, ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) t1, else ( ) y, ),
        postcondition( x, if(c) ( t1, ) else ( ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) t1, else ( e1, e2, ) y, ),
        postcondition( x, if(c) ( t1, ) else ( e1, e2, ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) t1, else ( e1, e2, ), y, ),
        postcondition( x, if(c) ( t1, ) else ( e1, e2, ) y, )
    )
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) t1, else e1, y, ),
        postcondition( x, if(c) ( t1, ) else ( e1, ) y, )
    )
    
    // Extra else correctly treated as a boolean-assertion `bool(else e2)`.
    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition( x, if(c) ( t1, t2, ), else e1, else e2, y, ),
        postcondition( x, if(c) ( t1, t2, ) else ( e1, ) bool(else e2), y, )
    )

    BOOST_CONTRACT_TEST_EQUAL_(
        postcondition(
            x,
            if(c) (
                t1,
                t2,
            ) else if(cc) (
                tt1,
                tt2,
            ) else if(ccc) (
                ttt1,
                ttt2,
            ) else (
                e1,
                e2,
            )
            y,
        ),
        postcondition(
            x,
            if(c) (
                t1,
                t2,
            ) else (
                if(cc) (
                    tt1,
                    tt2,
                ) else (
                    if(ccc) (
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
//    
//    BOOST_CONTRACT_TEST_( postcondition( before,
//        static if(c1) (
//            t11,
//            t12,
//        ) else static if(c2) (
//            t21,
//            t22,
//        ) else static if(c3) (
//            t31,
//            t32,
//        ) else (
//            e1,
//            e2,
//        )
//    after, ) )
          
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

