
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_PRECONDITION_INDEX

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_CONTRACT_TEST_(precondition_) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITION, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS, \
        (std::map<int, char>&) (f) ( int x, (std::map<int, char>&) y ) \
                throw(int, double) override final, \
        precondition_, \
        postcondition(x == 0 ? y.empty() : true), \
        precondition_ \
    )

int main ( ) {
    BOOST_CONTRACT_TEST_( BOOST_PP_EMPTY() )

    BOOST_CONTRACT_TEST_( precondition( ) )

    BOOST_CONTRACT_TEST_( precondition( x >= 0, y, z ) )

    BOOST_CONTRACT_TEST_(
        precondition(
            namespace (py) as boost::python,

            using namespace std,
            using std::placeholders::_1,
            using typename T::value_type,
            using (std::map<int, char>::insert),
            using (typename M<int, char>::key_type),
            using (iv) as vector<int>,
            using (icmap) as (map<int, char>),
            template( typename T ) using (vt) as vector<T>,
            template( typename T, int U ) using (xtu) as (x<T, int, U>),

            typedef unsigned long ul,
            typedef (map<int, char>) icmap,

            x >= 0,
            y.size() == x,
        )
    )

    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

