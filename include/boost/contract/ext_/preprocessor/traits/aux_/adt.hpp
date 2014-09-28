
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ADT_PUSH_BACK_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ADT_PUSH_BACK_HPP_

#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/replace.hpp>

// NOTE: These macros Abstract the Data Type (ADT) used to implement the traits
// (pp-sequence, pp-array, pp-list, etc.).

// PUBLIC //

// ELEM(index, traits)
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM BOOST_PP_SEQ_ELEM

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PUSH_BACK(traits, trait) \
    traits (trait)

// REPLACE(traits, index, trait)
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_REPLACE BOOST_PP_SEQ_REPLACE

#endif // #include guard

