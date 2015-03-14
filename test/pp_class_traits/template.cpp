
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/aux_/index/class.hpp>
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_TEMPLATE

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/class.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_CONTRACT_TEST_TEMPLATE_(class_traits) \
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE( \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE(class_traits), \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE_PARAMS(class_traits) \
    )

#define BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK(template_params) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_TEST_TEMPLATE_, \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_PARSE_D, \
        BOOST_PP_EMPTY(), \
        template_params, \
        class (a) extends( b, c ), \
        template_params \
    )

#include "../aux_/pp_template.hpp"

int main ( ) {
    boost::contract::test::aux::pp_template();
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

