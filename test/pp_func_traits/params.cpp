
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_PARAMS_INDEX

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/preprocessor/list/for_each_i.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

// NOTE: Some extra test macros are necessary here to regenerate the sign back
// from the parsed trait to check if the parsing was correct. But, at the end
// these are valuable tests also because they use the PARAM_TRAITS macros.

// Assume all 1-tuple types were specified without parenthesis. This is usually
// NOT true, but it is true in these tests. This is relevant only in these
// tests where generated code must match original signature and its parenthesis
// (the extra parenthesis of the original signature do not need to be
// reproduced when generating C++ code so this assumption is not necessary).
#define BOOST_CONTRACT_TEST_PARAM_REM_(type) \
    BOOST_PP_EXPR_IIF(BOOST_PP_EQUAL(BOOST_PP_TUPLE_SIZE(type), 1), \
        BOOST_PP_TUPLE_REM(0) \
    ) \
    type

#define BOOST_CONTRACT_TEST_PARAM_(r, unused, i, param) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_CONTRACT_TEST_PARAM_REM_( \
            BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE(param)) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME(param) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT(param)), \
        BOOST_PP_TUPLE_EAT(2) \
    , \
        BOOST_PP_TUPLE_REM(2) \
    )( \
        BOOST_PP_EMPTY(), \
        default BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT(param) \
    )

#define BOOST_CONTRACT_TEST_PARAMS_(func_traits) \
    ( \
        BOOST_PP_LIST_FOR_EACH_I(BOOST_CONTRACT_TEST_PARAM_, ~, \
                BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS(func_traits)) \
    )

// Variadic to allow to specify empty params `( )`.
#define BOOST_CONTRACT_TEST_EQUAL_(params_sign, parsed_params) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_TEST_PARAMS_, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS, \
        (std::map<int, char>&) (f), \
        params_sign, \
        const volatile, \
        parsed_params \
    )

#define BOOST_CONTRACT_TEST_(...) \
    BOOST_CONTRACT_TEST_EQUAL_( (__VA_ARGS__), (__VA_ARGS__) )

int main ( ) {
    // Test empty and void.
    BOOST_CONTRACT_TEST_( )
    BOOST_CONTRACT_TEST_EQUAL_( ( void ), ( ) )

    // Test named.
    BOOST_CONTRACT_TEST_( int x )
    // Test named with default.
    BOOST_CONTRACT_TEST_( int x, default 123 )
    // Test unnamed.
    BOOST_CONTRACT_TEST_( int )
    // Test unnamed with default.
    BOOST_CONTRACT_TEST_( int, default 123 )

    // Test named with parenthesis.
    BOOST_CONTRACT_TEST_( (std::map<int, char>&) y )
    // Test named with parenthesis and default.
    BOOST_CONTRACT_TEST_(
        (std::map<int, char>&) y, default (pair<int, char>::sizeof_first)
    )
    // Test unnamed with parenthesis.
    BOOST_CONTRACT_TEST_( (std::map<int, char>&) )
    // Test unnamed with parenthesis and default.
    BOOST_CONTRACT_TEST_(
        (std::map<int, char>&), default (pair<int, char>::sizeof_first)
    )
    
    // Test named arity.
    BOOST_CONTRACT_TEST_( int x, (std::map<int, char>&) y )
    // Test named arity with default.
    BOOST_CONTRACT_TEST_(
        int x, default 123,
        (std::map<int, char>&) y, default (pair<int, char>::sizeof_first)
    )
    // Test unnamed arity.
    BOOST_CONTRACT_TEST_( int, (std::map<int, char>&) )
    // Test unnamed arity with default.
    BOOST_CONTRACT_TEST_(
        int, default 123,
        (std::map<int, char>&), default (pair<int, char>::sizeof_first)
    )
    
    // Test variadics.
    BOOST_CONTRACT_TEST_EQUAL_( ( int count, (...) ), ( int count, ... ) )

    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

