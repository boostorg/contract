
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_CLASSIFIERS_INDEX

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_CONTRACT_TEST_(trait) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS, \
        template( typename T, (std::map<int, char>::value_type) V ), \
        trait, \
        (std::map<int, char>&) (f) ( int x, (std::map<int, char>&) y ), \
        trait \
    )
    
int main ( ) {
    BOOST_CONTRACT_TEST_( BOOST_PP_EMPTY() )
    BOOST_CONTRACT_TEST_( inline )
    BOOST_CONTRACT_TEST_( static )
    BOOST_CONTRACT_TEST_( inline static )
    BOOST_CONTRACT_TEST_( static inline )
    
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

