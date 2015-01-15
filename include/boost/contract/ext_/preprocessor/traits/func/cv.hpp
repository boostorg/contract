
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CV_QUALIFIERS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CV_QUALIFIERS_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/keyword_comb.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/const.hpp>
#include <boost/contract/ext_/preprocessor/keyword/volatile.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CV_QUALIFIERS_( \
        sign_cv, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_FIRST(sign_cv) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
                traits, \
                BOOST_PP_EXPR_IIF(BOOST_PP_TUPLE_ELEM(2, 0, \
                        BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_SECOND(sign_cv)), \
                    const \
                ) \
                BOOST_PP_EMPTY \
            ), \
            BOOST_PP_EXPR_IIF(BOOST_PP_TUPLE_ELEM(2, 1, \
                    BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_SECOND(sign_cv)), \
                volatile \
            ) \
            BOOST_PP_EMPTY \
        ) \
    )

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CV_QUALIFIERS_PARSE(sign_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CV_QUALIFIERS_( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_PARSE( \
            BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_FIRST(sign_traits), \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_CONST_REMOVE_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOLATILE_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_VOLATILE_REMOVE_FRONT \
        ), \
        BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_SECOND(sign_traits) \
    )

// Expand to `const | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CONST(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_CONST_INDEX, traits)()

// Expand to `volatile | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VOLATILE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_VOLATILE_INDEX, traits)()

#endif // #include guard

