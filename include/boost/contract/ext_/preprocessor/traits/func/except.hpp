
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_HPP_

#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/keyword_paren.hpp>
#include <boost/contract/ext_/preprocessor/keyword/noexcept.hpp>
#include <boost/contract/ext_/preprocessor/keyword/throw.hpp>
#include <boost/contract/ext_/preprocessor/utility/expand.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PRIVATE */

// Precondition: except = `[(,,,)] EMPTY` (so trailing EMPTY already there).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_( \
        decl_except, keyword, traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_except) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                keyword BOOST_PP_TUPLE_ELEM(2, 1, decl_except)) \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_NONE_(decl, traits) \
    (decl, BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, BOOST_PP_EMPTY))

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_THROW_(decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_( \
        BOOST_CONTRACT_EXT_PP_TRAITS_KEYWORD_PAREN_PARSE( \
            decl, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_THROW_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_THROW_REMOVE_FRONT \
        ), \
        throw, \
        traits \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_NOEXCEPT_(decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_( \
        BOOST_CONTRACT_EXT_PP_TRAITS_KEYWORD_PAREN_PARSE( \
            decl, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NOEXCEPT_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_NOEXCEPT_REMOVE_FRONT \
        ), \
        noexcept, \
        traits \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_PARSE_ARGS_(decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NOEXCEPT_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_NOEXCEPT_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_THROW_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_THROW_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_NONE_ \
    ))(decl, traits)

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_PARSE_ARGS_ decl_traits)

// Expand to `noexcept | noexcept(,,,) | throw(,,,) | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_EXCEPT_INDEX, traits)()

#endif // #include guard

