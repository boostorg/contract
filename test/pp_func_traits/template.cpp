
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_TEMPLATE_INDEX

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/list/for_each_i.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>

// NOTE: Some extra test macros are necessary here to regenerate the sign back
// from the parsed trait to check if the parsing was correct. But, at the end
// these are valuable tests also because they use the TPARAM_TRAITS macros.

// Assume all 1-tuple types were specified without parenthesis. This is usually
// NOT true, but it is true in these tests. This is relevant only in these
// tests where generated code must match original signature and its parenthesis
// (the extra parenthesis of the original signature do not need to be
// reproduced when generating C++ code so this assumption is not necessary).
#define BOOST_CONTRACT_TEST_TPARAM_REM_YES_(tokens) \
    BOOST_PP_EXPR_IIF(BOOST_PP_EQUAL(BOOST_PP_TUPLE_SIZE(tokens), 1), \
        BOOST_PP_TUPLE_REM(0) \
    ) \
    tokens

#define BOOST_CONTRACT_TEST_TPARAM_REM_(tokens) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(tokens), \
        BOOST_CONTRACT_TEST_TPARAM_REM_YES_ \
    , \
        BOOST_PP_TUPLE_REM(1) \
    )(tokens)
        
#define BOOST_CONTRACT_TEST_TPARAM_(r, unused, i, tparam_traits) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_CONTRACT_TEST_TPARAM_REM_( \
            BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_KIND(tparam_traits)) \
    BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_NAME(tparam_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_DEFAULT(tparam_traits)), \
        BOOST_PP_TUPLE_EAT(2) \
    , \
        BOOST_PP_TUPLE_REM(2) \
    )( \
        BOOST_PP_EMPTY(), \
        default BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_DEFAULT(tparam_traits) \
    )

#define BOOST_CONTRACT_TEST_TPARAMS_(func_traits) \
    ( \
        BOOST_PP_LIST_FOR_EACH_I(BOOST_CONTRACT_TEST_TPARAM_, ~, \
                BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TPARAMS(func_traits)) \
    )

#define BOOST_CONTRACT_TEST_TEMPLATE_(func_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE(func_traits)), \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        template BOOST_CONTRACT_TEST_TPARAMS_ \
    )(func_traits)

#define BOOST_CONTRACT_TEST_(trait) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_TEST_TEMPLATE_, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS, \
        BOOST_PP_EMPTY(), \
        trait, \
        (std::map<int, char>&) (f) ( int x, (std::map<int, char>&) y ), \
        trait \
    )

int main ( ) {
    // Test no template.
    BOOST_CONTRACT_TEST_( BOOST_PP_EMPTY() )

    // Test template with no parameter.
    BOOST_CONTRACT_TEST_( template( ) )

    // Test named typename.
    BOOST_CONTRACT_TEST_( template( typename T ) )
    // Test named typename with default.
    BOOST_CONTRACT_TEST_(
            template( typename T, default (std::map<int, char>) ) )
    // Test named variadic typename.
    BOOST_CONTRACT_TEST_( template( typename... T) )
    // Test unnamed typename.
    BOOST_CONTRACT_TEST_( template( typename ) )
    // Test unnamed typename with default.
    BOOST_CONTRACT_TEST_(
          template( typename, default (std::map<int, char>) ) )
    // Test unnamed variadic typename.
    BOOST_CONTRACT_TEST_( template( typename... ) )
    
    // Test named class.
    BOOST_CONTRACT_TEST_( template( class T ) )
    // Test named class with default.
    BOOST_CONTRACT_TEST_( template( class T, default (std::map<int, char>) ) )
    // Test named variadic class.
    BOOST_CONTRACT_TEST_( template( class... T) )
    // Test unnamed class.
    BOOST_CONTRACT_TEST_( template( class ) )
    // Test unnamed class with default.
    BOOST_CONTRACT_TEST_( template( class, default (std::map<int, char>) ) )
    // Test unnamed variadic class.
    BOOST_CONTRACT_TEST_( template( class... ) )
    
    // Test named value.
    BOOST_CONTRACT_TEST_( template( int I ) )
    // Test named value with default.
    BOOST_CONTRACT_TEST_( template( int I, default 123 ) )
    // Test unnamed value.
    BOOST_CONTRACT_TEST_( template( int ) )
    // Test unnamed value with default.
    BOOST_CONTRACT_TEST_( template( int, default 123 ) )

    // Test named value (of parenthesized type).
    BOOST_CONTRACT_TEST_( template( (std::map<int, char>::key_type) I ) )
    // Test named value (of parenthesized type) with default.
    BOOST_CONTRACT_TEST_(
            template( (std::map<int, char>::key_type) I, default 123 ) )
    // Test unnamed value (of parenthesized type).
    BOOST_CONTRACT_TEST_( template( (std::map<int, char>::key_type) ) )
    // Test unnamed value (of parenthesized type) with default.
    BOOST_CONTRACT_TEST_(
            template( (std::map<int, char>::key_type), default 123 ) )
/*
    // Test template-template parameter with no parameters.
    //BOOST_CONTRACT_TEST_( template( template( ) class P ) )
    // Test template-template parameter with parameters.
    //BOOST_CONTRACT_TEST_(
    //    template(
    //        template(
    //            typename T,
    //            class C,
    //            std::map<int, char>::key_type I,
    //            typename... V
    //        ) class P
    //    )
    //)
    // Test template-template parameter with defaults.
    //BOOST_CONTRACT_TEST_(
    //    template(
    //        template(
    //            typename T = std::map<int, char>::key_type,
    //            class C = std::map<int, char>::key_type,
    //            std::map<int, char>::key_type I = 123,
    //            typename... V
    //        ) class P
    //    )
    //)
    // Test template-template parameter with unnamed parameters.
    //BOOST_CONTRACT_TEST_(
    //    template(
    //        template(
    //            typename,
    //            class,
    //            std::map<int, char>::key_type,
    //            typename...
    //        ) class
    //    )
    //)
    // Test template-template parameter with unnamed and defaults.
    //BOOST_CONTRACT_TEST_(
    //    template(
    //        template(
    //            typename = std::map<int, char>::key_type,
    //            class = std::map<int, char>::key_type,
    //            std::map<int, char>::key_type = 123,
    //            typename...
    //        ) class
    //    )
    //)
*/
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

