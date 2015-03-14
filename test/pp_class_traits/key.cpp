
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/aux_/index/class.hpp>
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_KEY

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/class.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_CONTRACT_TEST_(key) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_KEY, \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_PARSE_D, \
        template( typename T, (std::map<int, char>::value_type) V ), \
        key, \
        (a) extends( b, c ), \
        key \
    )
    
int main ( ) {
    BOOST_CONTRACT_TEST_( class )
    BOOST_CONTRACT_TEST_( struct )
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

