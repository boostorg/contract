
#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_TEMPLATE_INDEX

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/contract/ext_/preprocessor/utility/is_empty.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/list/for_each_i.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>

// NOTE: Some extra test macros are necessary here to regenerate the sign back
// from the parsed trait to check if the parsing was correct. But, at the end
// these are valuable tests also because they use the TPARAM_TRAITS macros.
        
#define BOOST_CONTRACT_TEST_TPARAM_(r, unused, i, tparam_traits) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_KIND(tparam_traits) \
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
    BOOST_CONTRACT_TEST_( BOOST_PP_EMPTY() ) // None.

    BOOST_CONTRACT_TEST_( // Type, w/ default, and variadic.
        template(
            typename T,
            class U, default (std::map<int, char>),
            typename... V
        )
    )
    
    //BOOST_CONTRACT_TEST_( template( class... T ) )
    
    //BOOST_CONTRACT_TEST_( template( typename T ) )
    //BOOST_CONTRACT_TEST_( template( typename... T ) )
    
    //BOOST_CONTRACT_TEST_( class T, default (std::pair<int, int>) )
    //BOOST_CONTRACT_TEST_( typename T, default (std::pair<int, int>) )
    
/* 
    BOOST_CONTRACT_TEST_(
        template(
            typename T,
            class U,
            bool B,
            (std::size_t) S,
            (std::pair<int, int>::first_type) I,
            template(
                typename TT,
                class UU,
                bool BB,
                std::pair<int, int>::first_type II,
                template<
                    typename TTT,
                    class UUU,
                    bool BBB,
                    std::pair<int, int>::first_type III
                > class PP
            ) class P
        )
    )
    
    BOOST_CONTRACT_TEST_( // Without names.
        template(
            typename,
            class,
            bool,
            std::size_t, // Also without parenthesis.
            (std::pair<int, int>::first_type),
            template(
                typename,
                class,
                bool,
                std::pair<int, int>::first_type,
                template<
                    typename,
                    class,
                    bool,
                    std::pair<int, int>::first_type
                > class
            ) class
        )
    )
*/
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

