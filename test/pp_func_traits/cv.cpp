
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_CV_QUALIFIERS_INDEX

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#include <boost/preprocessor/variadic/size.hpp>

#define BOOST_CONTRACT_TEST_CV_QUALIFIERS_(func_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CONST(func_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VOLATILE(func_traits)

#define BOOST_CONTRACT_TEST_EQUAL_(trait, parsed) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_TEST_CV_QUALIFIERS_, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS, \
        (std::map<int, char>&) (f) ( int x, (std::map<int, char>&) y ), \
        trait, \
        refref throw(int, double) final override, \
        parsed \
    )

#define BOOST_CONTRACT_TEST_(trait) \
    BOOST_CONTRACT_TEST_EQUAL_(trait, trait)

int main ( ) {
    BOOST_CONTRACT_TEST_( BOOST_PP_EMPTY() )
    BOOST_CONTRACT_TEST_( const )
    BOOST_CONTRACT_TEST_( volatile )
    BOOST_CONTRACT_TEST_( const volatile )
    // Same as `const volatile` once parsed (this order does not matter in C++).
    BOOST_CONTRACT_TEST_EQUAL_( volatile const, const volatile )

    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

