
#ifndef BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/class/bases.hpp>
#include <boost/contract/ext_/preprocessor/traits/class/virt.hpp>
#include <boost/contract/ext_/preprocessor/traits/class/specialization.hpp>
#include <boost/contract/ext_/preprocessor/traits/class/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/class/verbatim.hpp>
#include <boost/contract/ext_/preprocessor/traits/class/key.hpp>
#include <boost/contract/ext_/preprocessor/traits/class/friend.hpp>
#include <boost/contract/ext_/preprocessor/traits/class/template.hpp>
#include <boost/contract/ext_/preprocessor/traits/class/export.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/index/class.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>

/* PUBLIC */

// Expand class declaration to `(remaining-declaration, parsed-traits)`. If
// there was no error, remaining declaration is `BOOST_PP_NIL`. Parsed traits
// can be inspected via the CLASS_TRAITS_... macros.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_PARSE_D(d, decl) \
    BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_DONE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_BASES_PARSE_(d, \
    BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_VIRT_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_SPECIALIZATION_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_NAME_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_VERBATIM_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_KEY_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_FRIEND_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_TEMPLATE_PARSE_(d, \
    BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_EXPORT_PARSE_( \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_INIT( \
        decl BOOST_PP_NIL \
    )))))))))))

/* PRIVATE */

// To debug or test the pp parsing code, #define this internal macro to stop
// parsing at a given trait index as #defined in aux_/index/class.hpp:
// #define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST ...

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_MAX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_DONE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_DONE_ \
        BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_DONE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_EXPORT
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_EXPORT_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_EXPORT_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_EXPORT_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_TEMPLATE
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_TEMPLATE_PARSE_(d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_TEMPLATE_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE_PARSE_D
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_FRIEND
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_FRIEND_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_FRIEND_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_FRIEND_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_KEY
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_KEY_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_KEY_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_KEY_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_VERBATIM
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_VERBATIM_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_VERBATIM_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_VERBATIM_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_NAME
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_NAME_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_NAME_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_NAME_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_SPECIALIZATION
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_SPECIALIZATION_PARSE_( \
            decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_SPECIALIZATION_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_SPECIALIZATION_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_VIRT
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_VIRT_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_VIRT_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_VIRT_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_BASES
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_BASES_PARSE_(d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_BASES_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_BASES_PARSE_D
#endif

#endif // #include guard

