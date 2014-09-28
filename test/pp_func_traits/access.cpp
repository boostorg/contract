
#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/detail/lightweight_test.hpp>

#define BOOST_CONTRACT_TEST_(trait) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS_CHECK_EQUAL( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS, \
        trait (int&) (f) ( int x, (int&) y ), \
        trait \
    )
    
int main ( ) {
    BOOST_CONTRACT_TEST_( BOOST_PP_EMPTY() )
    BOOST_CONTRACT_TEST_( public )
    BOOST_CONTRACT_TEST_( protected )
    BOOST_CONTRACT_TEST_( private )
    
    return boost::report_errors();
}

