
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_POSTCONDITION_INDEX

#include "../aux_/pp_traits.hpp"
#include <boost/contract/oldof.hpp>
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_CONTRACT_TEST_(postcondition_) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITION, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARSE_D, \
        (std::map<int, char>&) (f) ( int x, (std::map<int, char>&) y ) \
                throw(int, double) override final, \
        postcondition_, \
        remove_this_trailing_stuff, \
        postcondition_ \
    )

#define Z(z) BOOST_PP_EXPAND(BOOST_CONTRACT_EXT_PP_IS_EMPTY z)

#define X(x) Z(BOOST_PP_TUPLE_ELEM(2, 1, x))

#define Y(y) Z(BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_ELEM(2, 1, y)))

X(BOOST_CONTRACT_EXT_PP_TRAITS_TYPE_PARSE_D(1, int const n BOOST_PP_NIL))
X(BOOST_CONTRACT_EXT_PP_TRAITS_TYPE_PARSE_D(1, (::map<int, char>) n BOOST_PP_NIL))
X(BOOST_CONTRACT_EXT_PP_TRAITS_TYPE_PARSE_D(1, n BOOST_PP_NIL))

Y(BOOST_CONTRACT_EXT_PP_TRAITS_TYPE_SEQ_PARSE_D(1, int const n BOOST_PP_NIL))
Y(BOOST_CONTRACT_EXT_PP_TRAITS_TYPE_SEQ_PARSE_D(1, (::map<int, char>) n BOOST_PP_NIL))
Y(BOOST_CONTRACT_EXT_PP_TRAITS_TYPE_SEQ_PARSE_D(1, n BOOST_PP_NIL))

int main ( ) {
    BOOST_CONTRACT_TEST_( BOOST_PP_EMPTY() )

    BOOST_CONTRACT_TEST_( postcondition( ) )

    BOOST_CONTRACT_TEST_( postcondition( x >= 0, y, z ) )

    BOOST_CONTRACT_TEST_(
        postcondition(
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
            unsigned int const old_capacity =
                    BOOST_CONTRACT_OLDOF v.capacity(),
            (map<int, char> const) old_map =
                    BOOST_CONTRACT_OLDOF (map<int, char>::clone(m)),

            x >= 0,
            x == 0 ? !result : true,
            (!y),
            (std::map<int, char>::key_size > 0),

            const( std::cout ) !std::cout.error(),
            const( std::cout, x ) std::cout.flags == x,
            const( ) true,
            const( int const n, x, (::std::map<int, char> const&) m )
                    (m.size() == map<int, char>::key_size == x),
        )
    )

    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

