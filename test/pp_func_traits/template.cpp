
#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/detail/lightweight_test.hpp>

#include <boost/preprocessor/variadic/size.hpp>

#define BOOST_CONTRACT_TEST_(trait) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS_CHECK_EQUAL( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE, \
        trait (int&) (f) ( int x, (int&) y ), \
        trait \
    )

int main ( ) {
    BOOST_CONTRACT_TEST_( BOOST_PP_EMPTY() )

    BOOST_CONTRACT_TEST_(
        template(
            typename T,
            class U, default (std::pair<int, char>),
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
    return boost::report_errors();
}

