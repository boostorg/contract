
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/func_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/keyword.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/public.hpp>
#include <boost/contract/ext_/preprocessor/keyword/protected.hpp>
#include <boost/contract/ext_/preprocessor/keyword/private.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PUBLIC */

// Expand to `public | protected | private | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_ACCESS_INDEX, traits)()

// Implementation: Trailing EMPTY already put by KEYWORD3.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_KEYWORD3_TRAITS_PARSE( \
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

#endif // #include guard

