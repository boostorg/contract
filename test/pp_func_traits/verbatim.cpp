
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_VERBATIM_INDEX

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_CONTRACT_TEST_(verbatim_paren) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS, \
        BOOST_PP_EMPTY(), \
        BOOST_PP_EXPR_IIF(BOOST_PP_COMPL( \
                BOOST_CONTRACT_EXT_PP_IS_EMPTY(verbatim_paren)), \
            verbatim \
        ) verbatim_paren, \
        (std::map<int, char>&) (f) ( int x, (std::map<int, char>&) y ), \
        verbatim_paren \
    )

int main ( ) {
    // Test no attributes (for all C++11, MSVC, GCC, etc).
    BOOST_CONTRACT_TEST_( BOOST_PP_EMPTY() )
    
    // Test C++11 attributes with commas.
    BOOST_CONTRACT_TEST_( ([[noreturn, deprecated("reason")]]) )
    // Test multiple C++11 attributes.
    BOOST_CONTRACT_TEST_( ([[noreturn]] [[deprecated("reason")]]) )
    // Test single C++11 attribute.
    BOOST_CONTRACT_TEST_( ([[export]]) )
    
    // NOTE: MSVC declaration specifications do not allow for commas.
    // Test multiple MSVC declaration specifications.
    BOOST_CONTRACT_TEST_(
            (__declspec(noreturn) __declspec(deprecated("reason"))) )
    // Test single MSVC declaration specification.
    BOOST_CONTRACT_TEST_( (__declspec(dllexport)) )

    // NOTE: GCC attributes do not allow for commas.
    // Test multiple GCC attributes.
    BOOST_CONTRACT_TEST_(
            (__attribute__((noreturn)) __attribute__((deprecated("reason")))) )
    // Test single GCC attribute.
    BOOST_CONTRACT_TEST_( (__attribute__((dllexport))) )
    
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

