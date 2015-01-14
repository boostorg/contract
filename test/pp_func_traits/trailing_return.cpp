
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_TRAILING_RETURN_INDEX

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/control/iif.hpp>

// Wrap with parenthesis (if no parenthesis already).
// Precondition: trait != EMPTY().
#define BOOST_CONTRACT_TEST_PARENTHESIZE_(trait) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_RETURN_REMOVE_FRONT(trait)), \
        BOOST_PP_TUPLE_REM(1) \
    , \
        BOOST_PP_EMPTY() \
    )(BOOST_CONTRACT_EXT_PP_KEYWORD_RETURN_REMOVE_FRONT(trait))
        
#define BOOST_CONTRACT_TEST_(before, trait, after) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TRAILING_RETURN, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS, \
        before, \
        trait, \
        after, \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(trait), \
            BOOST_PP_TUPLE_EAT(1) \
        , \
            BOOST_CONTRACT_TEST_PARENTHESIZE_ \
        )(trait) \
    )

int main ( ) {
    // No trailing return.
    BOOST_CONTRACT_TEST_(
        void (f) ( ), BOOST_PP_EMPTY(), final override
    )

    // Trailing return with decltype.
    BOOST_CONTRACT_TEST_(
        template( typename L, typename R )
        auto (add) ( (L) left, (R) right ), return decltype(left + right),
                final override
    )
    // Trailing return with decltype and commas.
    BOOST_CONTRACT_TEST_(
        auto (f) ( ), return decltype(std::map<int, char>()), final override
    )
    
    // Trailing return without parenthesis.
    BOOST_CONTRACT_TEST_(
        auto (f) ( ), return int const, final override
    )
    // Trailing return with parenthesis.
    BOOST_CONTRACT_TEST_(
        auto (f) ( ), return (std::ostream&), final override
    )
    // Trailing return with parenthesis and commas.
    BOOST_CONTRACT_TEST_(
        auto (f) ( ), return (std::map<int, char>), final override
    )
    
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

