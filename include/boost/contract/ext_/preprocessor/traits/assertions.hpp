
#ifndef BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion/typedef.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/using.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/namespace.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/enum_to_seq.hpp>
#include <boost/contract/ext_/preprocessor/keyword/namespace.hpp>
#include <boost/contract/ext_/preprocessor/keyword/using.hpp>
#include <boost/contract/ext_/preprocessor/keyword/typedef.hpp>

/* PRIVATE */

// TODO: To be correct, I should probably check that using is after
// template(,,,) here, and not just check IS_TEMPLATE_FRONT...

#define BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_APPEND_ASSERTION_( \
        s, decl, a, d, allow_oldof, allow_return, traits) \
    ( \
        a, \
        d, \
        allow_oldof, \
        allow_return, \
        BOOST_PP_LIST_APPEND_D( \
            d, \
            traits, \
            ( \
                BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT( \
                        decl), \
                    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS \
                , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_USING_FRONT( \
                        decl), \
                    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS \
                , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT(\
                        decl), \
                    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS \
                , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT( \
                        decl), \
                    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS \
                , \
                    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS \
                ))))(decl), \
                BOOST_PP_NIL \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_ASSERTION_( \
        s, a_d_oldof_return_traits, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_APPEND_ASSERTION_( \
        s, \
        decl, \
        BOOST_PP_TUPLE_ELEM(5, 0, a_d_oldof_return_traits), \
        BOOST_PP_TUPLE_ELEM(5, 1, a_d_oldof_return_traits), \
        BOOST_PP_TUPLE_ELEM(5, 2, a_d_oldof_return_traits), \
        BOOST_PP_TUPLE_ELEM(5, 3, a_d_oldof_return_traits), \
        BOOST_PP_TUPLE_ELEM(5, 4, a_d_oldof_return_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_( \
        a, d, s, allow_oldof, allow_return, decl) \
    BOOST_PP_SEQ_FOLD_LEFT_ ## s( \
        BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_ASSERTION_, \
        (a, d, allow_oldof, allow_return, BOOST_PP_NIL), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ENUM_TO_SEQ decl \
    )

#define BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_A_D_S_( \
        a, d, s, allow_oldof, allow_return, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY decl, \
        BOOST_PP_NIL BOOST_PP_TUPLE_EAT(6) \
    , \
        BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_ \
    )(a, d, s, allow_oldof, allow_return, decl)

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_A_D_S(a, d, s, decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_A_D_S_(a, d, s, 1, 1, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS(decl) \
    BOOST_CONTRACT_EXT_PP_ASSERTIONS_TRAITS_A_D_S(1, 1, 1, decl)

#endif // #include guard

