
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
#include <boost/contract/ext_/preprocessor/traits/aux_/class_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>

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
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl BOOST_PP_NIL \
    )))))))))))

/* PRIVATE */

// To debug or test the pp parsing code, you can #define this internal macro to
// stop parsing at a given trait index as #defined in class_index.hpp (this is
// what some of this library tests do).
// #define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST ..._INDEX

// TODO: If I rename AUX macros in each class/* file then I can use CLASS_TRAITS
// names here (same for func.hpp).
// NOTE: These macros #definitions read TRAITS_CLASS instead of CLASS_TRAITS to
// avoid name clashes with macro #define in class/*.

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_MAX_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_DONE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_DONE_ \
        BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_EXPORT_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_EXPORT_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_EXPORT_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_EXPORT_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_TEMPLATE_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_TEMPLATE_PARSE_(d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_TEMPLATE_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE_PARSE_D
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_FRIEND_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_FRIEND_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_FRIEND_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_FRIEND_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_KEY_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_KEY_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_KEY_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_KEY_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_VERBATIM_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_VERBATIM_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_VERBATIM_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_VERBATIM_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_NAME_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_NAME_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_NAME_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_NAME_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_SPECIALIZATION_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_SPECIALIZATION_PARSE_( \
            decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_SPECIALIZATION_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_SPECIALIZATION_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_VIRT_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_VIRT_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_VIRT_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_VIRT_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_BASES_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_BASES_PARSE_(d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_CLASS_BASES_PARSE_ \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_BASES_PARSE_D
#endif

#endif // #include guard

