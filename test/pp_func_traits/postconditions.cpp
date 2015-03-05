
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_POSTCONDITIONS_INDEX
#include "../aux_/pp_traits.hpp"
#include "../aux_/pp_assertions.hpp"
#include <boost/contract/oldof.hpp>
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_CONTRACT_TEST_POSTCONDITIONS_(func_traits) \
    postcondition \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS(func_traits)), \
        () BOOST_PP_TUPLE_EAT(3) \
    , \
        BOOST_PP_SEQ_FOLD_LEFT \
    )(BOOST_CONTRACT_TEST_AUX_PP_POST_ASSERTIONS_S_1, (), \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS(func_traits))

#define BOOST_CONTRACT_TEST_EQUAL_(postconditions, parsed_postconditions) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_TEST_POSTCONDITIONS_, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARSE_D, \
        (std::map<int, char>&) (f) ( ) \
                throw(int, double) override final, \
        postconditions, \
        BOOST_PP_EMPTY(), \
        parsed_postconditions \
    )

#define BOOST_CONTRACT_TEST_(postconditions) \
    BOOST_CONTRACT_TEST_EQUAL_(postconditions, postconditions)

#define oldof BOOST_CONTRACT_OLDOF

int main ( ) {
    #define BOOST_CONTRACT_TEST_ASSERTIONS_keyword postcondition
    #define BOOST_CONTRACT_TEST_ASSERTIONS_equal BOOST_CONTRACT_TEST_EQUAL_
    #define BOOST_CONTRACT_TEST_ASSERTIONS_check BOOST_CONTRACT_TEST_
    #define BOOST_CONTRACT_TEST_ASSERTIONS_post \
        auto result1 = return, \
        int const result2 = return, \
        (map<int, char> const&) result3 = return, \
        \
        auto old_size = BOOST_CONTRACT_OLDOF v.size(), \
        unsigned int const old_capacity = oldof v.capacity(), \
        (map<int, char> const) old_map = \
                BOOST_CONTRACT_OLDOF (map<int, char>::clone(m)),
    #define BOOST_CONTRACT_TEST_ASSERTIONS_post_if \
        auto c = return, \
        long long const d = BOOST_CONTRACT_OLDOF v.size(),

    #include "./assertions.hpp" // Include actual assertion tests.
    
    #undef BOOST_CONTRACT_TEST_ASSERTIONS_keyword
    #undef BOOST_CONTRACT_TEST_ASSERTIONS_equal
    #undef BOOST_CONTRACT_TEST_ASSERTIONS_check
    #undef BOOST_CONTRACT_TEST_ASSERTIONS_post
    #undef BOOST_CONTRACT_TEST_ASSERTIONS_post_if
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

