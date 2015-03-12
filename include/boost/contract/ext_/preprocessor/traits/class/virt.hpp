
#ifndef BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_VIRT_HPP_
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_VIRT_HPP_

#include <boost/contract/ext_/preprocessor/traits/aux_/class_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/keyword.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/final.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

/* PUBLIC */

// Expand to `final | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_FINAL(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_FINAL_INDEX, traits)()

// Implementation: Trailing EMPTY already put by KEYWORD1.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_VIRT_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_KEYWORD1_TRAITS_PARSE( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
            final, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_FINAL_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_FINAL_REMOVE_FRONT \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )

#endif // #include guard

