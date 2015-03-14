
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/aux_/index/func.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_PRECONDITIONS

#include "../aux_/pp_traits.hpp"
#include "../aux_/pp_assertions.hpp"
#include <boost/contract/oldof.hpp>
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_CONTRACT_TEST_PRECONDITIONS_(f) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITIONS(f)), \
        () BOOST_PP_TUPLE_EAT(3) \
    , \
        BOOST_PP_SEQ_FOLD_LEFT \
    )(BOOST_CONTRACT_TEST_AUX_PP_ASSERTIONS_S_1, (), \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITIONS(f))

#define BOOST_CONTRACT_TEST_EQUAL_(preconditions, parsed_preconditions) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_TEST_PRECONDITIONS_, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARSE_D, \
        (std::map<int, char>&) (f) ( ) throw(int, double) override final, \
        BOOST_PP_EXPR_IIF(BOOST_PP_COMPL( \
                BOOST_CONTRACT_EXT_PP_IS_EMPTY(preconditions)), \
            precondition \
        ) \
        preconditions, \
        postcondition( auto result = return, result == x * x ), \
        parsed_preconditions \
    )

#define BOOST_CONTRACT_TEST_(preconditions) \
    BOOST_CONTRACT_TEST_EQUAL_(preconditions, preconditions)

int main ( ) {
    #define BOOST_CONTRACT_TEST_ASSERTIONS_equal BOOST_CONTRACT_TEST_EQUAL_
    #define BOOST_CONTRACT_TEST_ASSERTIONS_check BOOST_CONTRACT_TEST_
    #define BOOST_CONTRACT_TEST_ASSERTIONS_post
    #define BOOST_CONTRACT_TEST_ASSERTIONS_post_if

    #include "./assertions.hpp" // Include actual assertion tests.
    
    #undef BOOST_CONTRACT_TEST_ASSERTIONS_equal
    #undef BOOST_CONTRACT_TEST_ASSERTIONS_check
    #undef BOOST_CONTRACT_TEST_ASSERTIONS_post
    #undef BOOST_CONTRACT_TEST_ASSERTIONS_post_if
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

