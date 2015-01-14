
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_HPP_

#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/keyword_paren.hpp>
#include <boost/contract/ext_/preprocessor/keyword/noexcept.hpp>
#include <boost/contract/ext_/preprocessor/keyword/throw.hpp>
#include <boost/contract/ext_/preprocessor/utility/expand.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_( \
        sign, traits, keyword, is_keyword_macro, remove_keyword_macro) \
    ( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_SKIP(sign, \
                is_keyword_macro, remove_keyword_macro) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            keyword \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN(sign, \
                    is_keyword_macro, remove_keyword_macro) \
            BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_NONE_(sign, traits) \
    (sign, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))
        
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_NOEXCEPT_(sign, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_(sign, traits, \
        noexcept, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NOEXCEPT_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_NOEXCEPT_REMOVE_FRONT \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_THROW_(sign, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_(sign, traits, \
        throw, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_THROW_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_THROW_REMOVE_FRONT \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_PARSE_ARGS_(sign, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NOEXCEPT_FRONT(sign), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_NOEXCEPT_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_THROW_FRONT(sign), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_THROW_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_NONE_ \
    ))(sign, traits)

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_PARSE(sign_traits) \
    BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_PARSE_ARGS_ sign_traits)

// Expand to `noexcept | noexcept(,,,) | throw(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_EXCEPT_INDEX, traits)()

#endif // #include guard

