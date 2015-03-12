
#ifndef BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_HPP_
#define BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_HPP_

#include "pp_1tuple_rem.hpp"
#include <boost/contract/ext_/preprocessor/traits/param.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#ifndef BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK
#   error "must #define BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK macro"
#endif

/* PUBLIC */

#define BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE(template_, template_params) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(template_), \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        template BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_PARAMS_ \
    )(template_params)

/* PRIVATE */

#define BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_PARAMS_(template_params) \
    ( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(template_params), \
            BOOST_PP_TUPLE_EAT(3) \
        , \
            BOOST_PP_SEQ_FOR_EACH_I \
        )(BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_PARAM_, ~, template_params) \
    )

#define BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_PARAM_( \
        r, unused, i, template_param) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE(template_param)), \
        BOOST_CONTRACT_TEST_AUX_PP_1TUPLE_REM \
    , \
        BOOST_PP_TUPLE_REM(1) \
    )(BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE(template_param)) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME(template_param) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT(template_param)), \
        BOOST_PP_TUPLE_EAT(2) \
    , \
        BOOST_PP_TUPLE_REM(2) \
    )( \
        BOOST_PP_EMPTY(), \
        default BOOST_CONTRACT_TEST_AUX_PP_1TUPLE_REM( \
                BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT(template_param)) \
    )

/* CODE */

namespace boost { namespace contract { namespace test { namespace aux {

void pp_template ( ) {
    // Test no template.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK( BOOST_PP_EMPTY() )

    // Test template with no parameter.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK( template( ) )

    // Test named typename.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK( template( typename T ) )
    // Test named typename with default.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK(
            template( typename T, default (std::map<int, char>) ) )
    // Test named variadic typename.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK( template( typename... T) )
    // Test unnamed typename.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK( template( typename ) )
    // Test unnamed typename with default.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK(
          template( typename, default (std::map<int, char>) ) )
    // Test unnamed variadic typename.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK( template( typename... ) )
    
    // Test named class.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK( template( class T ) )
    // Test named class with default.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK(
            template( class T, default (std::map<int, char>) ) )
    // Test named variadic class.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK( template( class... T) )
    // Test unnamed class.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK( template( class ) )
    // Test unnamed class with default.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK(
            template( class, default (std::map<int, char>) ) )
    // Test unnamed variadic class.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK( template( class... ) )
    
    // Test named value.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK( template( int I ) )
    // Test named value with default.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK( template( int I, default 123 ) )
    // Test unnamed value.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK( template( int ) )
    // Test unnamed value with default.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK( template( int, default 123 ) )

    // Test named value (of parenthesized type).
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK(
            template( (std::map<int, char>::key_type) I ) )
    // Test named value (of parenthesized type) with default.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK(
            template( (std::map<int, char>::key_type) I, default 123 ) )
    // Test unnamed value (of parenthesized type).
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK(
            template( (std::map<int, char>::key_type) ) )
    // Test unnamed value (of parenthesized type) with default.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK(
            template( (std::map<int, char>::key_type), default 123 ) )

    // Test template-template parameter with no parameters.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK( template( template( ) class P ) )
    // Test template-template parameter with parameters.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK(
        template(
            template(
                typename T,
                class C,
                std::map<int, char>::key_type I,
                typename... V
            ) class P
        )
    )
    // Test template-template parameter with defaults.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK(
        template(
            template(
                typename T = std::map<int, char>::key_type,
                class C = std::map<int, char>::key_type,
                std::map<int, char>::key_type I = 123,
                typename... V
            ) class P, default (::n::c<int, char>::template t)
        )
    )
    // Test template-template parameter with unnamed parameters.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK(
        template(
            template(
                typename,
                class,
                std::map<int, char>::key_type,
                typename...
            ) class
        )
    )
    // Test template-template parameter with unnamed and defaults.
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK(
        template(
            template(
                typename = std::map<int, char>::key_type,
                class = std::map<int, char>::key_type,
                std::map<int, char>::key_type = 123,
                typename...
            ) class, default (::n::c<int, char>::template t)
        )
    )
}

} } } } // namespace

#endif // #include guard

