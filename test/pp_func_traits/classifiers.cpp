
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_CLASSIFIERS_INDEX

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/preprocessor/seq/to_list.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/list/for_each.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/cat.hpp>
        
#define BOOST_CONTRACT_TEST_FIND_(r, classifier_upper, classifier) \
    BOOST_PP_EXPR_IIF(BOOST_PP_SEQ_CAT((BOOST_CONTRACT_EXT_PP_KEYWORD_IS_) \
            (classifier_upper)(_FRONT))(classifier), \
        classifier \
    )

#define BOOST_CONTRACT_TEST_ELEM_(r, unused, classifier) classifier

#define BOOST_CONTRACT_TEST_TRAIT_(classifier_upper, classifiers_list) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_PP_CAT(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_, classifier_upper), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARSE_D, \
        template( typename T, (std::map<int, char>::value_type) V ), \
        BOOST_PP_LIST_FOR_EACH(BOOST_CONTRACT_TEST_ELEM_, ~, \
                classifiers_list), \
        (std::map<int, char>&) (f) ( int x, (std::map<int, char>&) y ), \
        BOOST_PP_LIST_FOR_EACH(BOOST_CONTRACT_TEST_FIND_, classifier_upper, \
                classifiers_list) \
    )

#define BOOST_CONTRACT_TEST_LIST_(classifiers_list) \
    BOOST_CONTRACT_TEST_TRAIT_(INLINE, classifiers_list) \
    BOOST_CONTRACT_TEST_TRAIT_(STATIC, classifiers_list) \
    BOOST_CONTRACT_TEST_TRAIT_(EXTERN, classifiers_list) \
    BOOST_CONTRACT_TEST_TRAIT_(EXPLICIT, classifiers_list) \
    BOOST_CONTRACT_TEST_TRAIT_(VIRTUAL, classifiers_list) \
    BOOST_CONTRACT_TEST_TRAIT_(FRIEND, classifiers_list)

#define BOOST_CONTRACT_TEST_(classifiers_seq) \
    BOOST_CONTRACT_TEST_LIST_( \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(classifiers_seq), \
            BOOST_PP_NIL BOOST_PP_TUPLE_EAT(1) \
        , \
            BOOST_PP_SEQ_TO_LIST \
        )(classifiers_seq) \
    )
    
int main ( ) {
    // Test a few combinations verified to be valid C++. (Other combinations
    // are also supported by the macro syntax but it would be overwhelming to
    // test them all and of little use given they are not valid C++.)

    BOOST_CONTRACT_TEST_( BOOST_PP_EMPTY() )

    BOOST_CONTRACT_TEST_( (inline) )
    
    BOOST_CONTRACT_TEST_( (static) )
    BOOST_CONTRACT_TEST_( (static) (inline) )
    BOOST_CONTRACT_TEST_( (inline) (static) )
    
    BOOST_CONTRACT_TEST_( (extern) )
    BOOST_CONTRACT_TEST_( (extern) (inline) )
    BOOST_CONTRACT_TEST_( (inline) (extern) )
    
    // This triplet combination is valid for C++11 type-conversion operators.
    BOOST_CONTRACT_TEST_( (explicit) (inline) (virtual) )
    BOOST_CONTRACT_TEST_( (explicit) (virtual) (inline) )

    BOOST_CONTRACT_TEST_( (inline) (explicit) (virtual) )
    BOOST_CONTRACT_TEST_( (inline) (virtual) (explicit) )

    BOOST_CONTRACT_TEST_( (virtual) (explicit) (inline) )
    BOOST_CONTRACT_TEST_( (virtual) (inline) (explicit) )
    
    BOOST_CONTRACT_TEST_( (explicit) (virtual) )
    BOOST_CONTRACT_TEST_( (virtual) (explicit) )
    
    BOOST_CONTRACT_TEST_( (explicit) )
    BOOST_CONTRACT_TEST_( (explicit) (inline) )
    BOOST_CONTRACT_TEST_( (inline) (explicit) )
    
    BOOST_CONTRACT_TEST_( (virtual) )
    BOOST_CONTRACT_TEST_( (virtual) (inline) )
    BOOST_CONTRACT_TEST_( (inline) (virtual) )

    BOOST_CONTRACT_TEST_( (friend) )
    BOOST_CONTRACT_TEST_( (friend) (inline) )
    BOOST_CONTRACT_TEST_( (inline) (friend) )

    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

