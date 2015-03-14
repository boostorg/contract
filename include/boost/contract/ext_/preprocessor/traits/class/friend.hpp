
#ifndef BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_FRIEND_HPP_
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_FRIEND_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/index/class.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/keyword.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/friend.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

/* PUBLIC */

// Expand to `friend | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_FRIEND(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_FRIEND, traits)()

// Implementation: Trailing EMPTY already put by KEYWORD1.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_FRIEND_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD1_PARSE( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
            friend, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_FRIEND_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_FRIEND_REMOVE_FRONT \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#endif // #include guard

