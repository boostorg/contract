
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/aux_/index/class.hpp>
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_SPECIALIZATION

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/class.hpp>

#define BOOST_CONTRACT_TEST_(specialization) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_SPECIALIZATION, \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_PARSE_D, \
        template( typename T, (std::map<int, char>::value_type) V ) \
        class (a), \
        specialization, \
        extends( b, c ), \
        specialization \
    )
    
int main ( ) {
    BOOST_CONTRACT_TEST_( BOOST_PP_EMPTY() )
    BOOST_CONTRACT_TEST_( ( T, V, std::pair<T, V> const& ) )
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

