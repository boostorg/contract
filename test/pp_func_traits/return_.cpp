
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_RETURN_INDEX

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/control/iif.hpp>

// Wrap with parenthesis (if no parenthesis already and it is not `auto`).
// Precondition: return_ != EMPTY().
#define BOOST_CONTRACT_TEST_PARENTHESIZE_(return_) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(return_), \
        BOOST_PP_TUPLE_REM(1) \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT(return_), \
        BOOST_PP_TUPLE_REM(1) \
    , \
        BOOST_PP_EMPTY() \
    ))(return_)
        
#define BOOST_CONTRACT_TEST_(before, return_, after) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARSE_D, \
        before, \
        return_, \
        after, \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(return_), \
            BOOST_PP_TUPLE_EAT(1) \
        , \
            BOOST_CONTRACT_TEST_PARENTHESIZE_ \
        )(return_) \
    )

int main ( ) {
    // Return without and with parenthesis.
    BOOST_CONTRACT_TEST_(
        BOOST_PP_EMPTY(),
        void, (f) ( )
    )
    BOOST_CONTRACT_TEST_(
        BOOST_PP_EMPTY(),
        (::std::map<int, char>), (f) ( )
    )

    // No return for constructor and destructor.
    BOOST_CONTRACT_TEST_(
        BOOST_PP_EMPTY(),
        BOOST_PP_EMPTY(), (ctor) ( int x )
    )
    BOOST_CONTRACT_TEST_(
        BOOST_PP_EMPTY(),
        BOOST_PP_EMPTY(), (~dtor) ( )
    )

    // No return for type conversion operators (with and without paren).
    BOOST_CONTRACT_TEST_(
        BOOST_PP_EMPTY(),
        BOOST_PP_EMPTY(), operator int ( )
    )
    BOOST_CONTRACT_TEST_(
        BOOST_PP_EMPTY(),
        BOOST_PP_EMPTY(), operator(int*)(int_ptr) ( )
    )
    
    // Return for other operators (non type conversions, etc.).
    BOOST_CONTRACT_TEST_(
        BOOST_PP_EMPTY(),
        int, operator(+)(add) ( int, int )
    )
    BOOST_CONTRACT_TEST_(
        BOOST_PP_EMPTY(),
        (::std::map<int, char>&), operator(*)(deref) ( )
    )

    // Return for unified syntax.
    BOOST_CONTRACT_TEST_(
        template( typename L, typename R ),
        auto, (add) ( (L) left, (R) right ) return decltype(left + right)
    )
    
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

