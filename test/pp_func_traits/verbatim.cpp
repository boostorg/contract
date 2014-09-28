
#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/contract/ext_/preprocessor/utility/is_empty.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/detail/lightweight_test.hpp>

#define BOOST_CONTRACT_TEST_(trait) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS_CHECK_EQUAL( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM, \
        BOOST_PP_EXPR_IIF(BOOST_PP_COMPL( \
                BOOST_CONTRACT_DETAIL_PP_IS_EMPTY(trait)), \
            verbatim trait \
        ) \
        (int&) (f) ( int x, (int&) y ), \
        trait \
    )

int main ( ) {
    // None.
    BOOST_CONTRACT_TEST_( BOOST_PP_EMPTY() )
    
    // C++11 attributes with commas.
    BOOST_CONTRACT_TEST_( ([[noreturn, deprecated("reason")]]) )
    // Multiple C++11 attributes.
    BOOST_CONTRACT_TEST_( ([[noreturn]] [[deprecated("reason")]]) )
    // Single C++11 attribute.
    BOOST_CONTRACT_TEST_( ([[export]]) )
    
    // MSVC declaration specifications do not allow for commas.
    // Multiple MSVC declaration specifications.
    BOOST_CONTRACT_TEST_(
            (__declspec(noreturn) __declspec(deprecated("reason"))) )
    // Single MSVC declaration specification.
    BOOST_CONTRACT_TEST_( (__declspec(dllexport)) )

    // GCC attributes do not allow for commas.
    // Multiple GCC attributes.
    BOOST_CONTRACT_TEST_(
            (__attribute__((noreturn)) __attribute__((deprecated("reason")))) )
    // Single GCC attribute.
    BOOST_CONTRACT_TEST_( (__attribute__((dllexport))) )
    
    return boost::report_errors();
}

