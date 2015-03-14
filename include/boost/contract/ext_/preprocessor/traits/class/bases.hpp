
#ifndef BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_BASES_HPP_
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_BASES_HPP_

#include <boost/contract/ext_/preprocessor/traits/base.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/index/class.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/keyword_list.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/list.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/contract/extends.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PUBLIC */

// Expand to EMPTY() if no base class, otherwise expand to pp-seq of base class
// traits (each pp-seq elem. to be inspected via BASE_TRAITS).
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_BASES(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_ELEM( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_BASES, traits)()

#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_BASES_PARSE_D(d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_LIST_PARSE_D(d, \
        decl_traits, \
        BOOST_PP_EMPTY(), \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_EXTENDS_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_EXTENDS_REMOVE_FRONT, \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_BASES_ \
    )

/* PRIVATE */

// Precondition: decl = `(,,,) ...` from `extends(,,,) ...` originally in decl.
// This macro will also parse `(,,,)` into a pp-seq of base traits.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_BASES_(d, decl) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_FIXED_LIST_PARSE_D_1(d, decl, \
            BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_BASE_PARSE_)
    
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_BASE_PARSE_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_BASE_TRAITS_PARSE(decl)
                    
#endif // #include guard

