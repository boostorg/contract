
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_CLASSIFIERS_INDEX

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/preprocessor/list/for_each.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/cat.hpp>
        
#define BOOST_CONTRACT_TEST_FIND_(r, trait_id, elem) \
    BOOST_PP_EXPR_IIF(BOOST_PP_SEQ_CAT((BOOST_CONTRACT_EXT_PP_KEYWORD_IS_) \
            (trait_id)(_FRONT))(elem), \
        elem \
    )

#define BOOST_CONTRACT_TEST_ELEM_(r, unused, elem) elem

#define BOOST_CONTRACT_TEST_TRAIT_(trait_id, traits) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_PP_CAT(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_, trait_id), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS, \
        template( typename T, (std::map<int, char>::value_type) V ), \
        BOOST_PP_LIST_FOR_EACH(BOOST_CONTRACT_TEST_ELEM_, ~, traits), \
        (std::map<int, char>&) (f) ( int x, (std::map<int, char>&) y ), \
        BOOST_PP_LIST_FOR_EACH(BOOST_CONTRACT_TEST_FIND_, trait_id, traits) \
    )

#define BOOST_CONTRACT_TEST_(traits) \
    BOOST_CONTRACT_TEST_TRAIT_(INLINE, traits) \
    BOOST_CONTRACT_TEST_TRAIT_(STATIC, traits)
    
int main ( ) {
    BOOST_CONTRACT_TEST_( BOOST_PP_NIL )

    BOOST_CONTRACT_TEST_( (inline, BOOST_PP_NIL) )
    BOOST_CONTRACT_TEST_( (static, BOOST_PP_NIL) )
    BOOST_CONTRACT_TEST_( (inline, (static, BOOST_PP_NIL)) )
    BOOST_CONTRACT_TEST_( (static, (inline, BOOST_PP_NIL)) )

    // TODO: Test permutations of all classifiers.
    
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

