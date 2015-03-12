
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_VIRT_INDEX
#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/class.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_CONTRACT_TEST_(virt) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_FINAL, \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_PARSE_D, \
        template( typename T, (std::map<int, char>::value_type) V ) \
        class (a), \
        virt, \
        extends( b, c ), \
        virt \
    )
    
int main ( ) {
    BOOST_CONTRACT_TEST_( BOOST_PP_EMPTY() )
    BOOST_CONTRACT_TEST_( final )
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

