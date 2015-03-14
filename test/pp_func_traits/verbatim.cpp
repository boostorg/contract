
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/aux_/index/func.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_VERBATIM

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/verbatim.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_CONTRACT_TEST_AUX_PP_VERBATIM_CHECK(verbatim) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARSE_D, \
        BOOST_PP_EMPTY(), \
        verbatim, \
        (std::map<int, char>&) (f) ( int x, (std::map<int, char>&) y ), \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(verbatim), \
            BOOST_PP_TUPLE_EAT(1) \
        , \
            BOOST_CONTRACT_EXT_PP_KEYWORD_VERBATIM_REMOVE_FRONT \
        )(verbatim) \
    )

#include "../aux_/pp_verbatim.hpp"

int main ( ) {
    boost::contract::test::aux::pp_verbatim();
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

