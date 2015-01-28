
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/keyword.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/public.hpp>
#include <boost/contract/ext_/preprocessor/keyword/protected.hpp>
#include <boost/contract/ext_/preprocessor/keyword/private.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PRIVATE */

// Precondition: access = `[keyword] EMPTY` (so trailing EMPTY already there).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_(decl_access, traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_access), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_access)) \
    )

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_( \
        BOOST_CONTRACT_EXT_PP_TRAITS_KEYWORD3_PARSE( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
            public, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PUBLIC_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_PUBLIC_REMOVE_FRONT, \
            protected, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PROTECTED_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_REMOVE_FRONT, \
            private, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PRIVATE_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_PRIVATE_REMOVE_FRONT \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

// Expand to `public | protected | private | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_ACCESS_INDEX, traits)()

#endif // #include guard

