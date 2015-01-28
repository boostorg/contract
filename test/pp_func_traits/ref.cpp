
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_REF_INDEX

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#include <boost/preprocessor/variadic/size.hpp>

#define BOOST_CONTRACT_TEST_(ref_) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARSE_D, \
        (std::map<int, char>&) (f) ( int x, (std::map<int, char>&) y ) const, \
        ref_, \
        noexcept(my::map<int, char>::key_size) final override, \
        ref_ \
    )

int main ( ) {
    BOOST_CONTRACT_TEST_( BOOST_PP_EMPTY() )
    BOOST_CONTRACT_TEST_( ref )
    BOOST_CONTRACT_TEST_( ref ref )

    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

