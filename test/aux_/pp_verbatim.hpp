
#ifndef BOOST_CONTRACT_TEST_AUX_PP_VERBATIM_HPP_
#define BOOST_CONTRACT_TEST_AUX_PP_VERBATIM_HPP_

#include <boost/preprocessor/facilities/empty.hpp>

#ifndef BOOST_CONTRACT_TEST_AUX_PP_VERBATIM_CHECK
#   error "must #define BOOST_CONTRACT_TEST_AUX_PP_VERBATIM_CHECK macro"
#endif

namespace boost { namespace contract { namespace test { namespace aux {

void pp_verbatim ( ) {
    // Test no attributes (for all C++11, MSVC, GCC, etc).
    BOOST_CONTRACT_TEST_AUX_PP_VERBATIM_CHECK( BOOST_PP_EMPTY() )
    
    // Test C++11 attributes with commas.
    BOOST_CONTRACT_TEST_AUX_PP_VERBATIM_CHECK(
            verbatim([[noreturn, deprecated("reason")]]) )
    // Test multiple C++11 attributes.
    BOOST_CONTRACT_TEST_AUX_PP_VERBATIM_CHECK(
           verbatim([[noreturn]] [[deprecated("reason")]]) )
    // Test single C++11 attribute.
    BOOST_CONTRACT_TEST_AUX_PP_VERBATIM_CHECK( verbatim([[export]]) )
    
    // NOTE: MSVC declaration specifications do not allow for commas.
    // Test multiple MSVC declaration specifications.
    BOOST_CONTRACT_TEST_AUX_PP_VERBATIM_CHECK(
            verbatim(__declspec(noreturn) __declspec(deprecated("reason"))) )
    // Test single MSVC declaration specification.
    BOOST_CONTRACT_TEST_AUX_PP_VERBATIM_CHECK( verbatim(__declspec(dllexport)) )

    // NOTE: GCC attributes do not allow for commas.
    // Test multiple GCC attributes.
    BOOST_CONTRACT_TEST_AUX_PP_VERBATIM_CHECK(
        verbatim(
            __attribute__((noreturn))
            __attribute__((deprecated("reason")))
        )
    )
    // Test single GCC attribute.
    BOOST_CONTRACT_TEST_AUX_PP_VERBATIM_CHECK(
            verbatim(__attribute__((dllexport))) )
}

} } } } // namespace

#endif // #include guard

