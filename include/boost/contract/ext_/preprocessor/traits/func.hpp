
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/postconditions.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/preconditions.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/virt.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/except.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/ref.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/cv.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/params.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/return.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/classifiers.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/template.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/export.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/verbatim.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/access.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/index/func.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/adt.hpp>

/* PUBLIC */

// Expand class declaration to `(remaining-declaration, parsed-traits)`. If
// there was no error, remaining declaration is `BOOST_PP_NIL`. Parsed traits
// can be inspected via the FUNC_TRAITS_... macros.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARSE_D(d, decl) \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_DONE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_POSTCONDITIONS_PARSE_(d, \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PRECONDITIONS_PARSE_(d, \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VIRT_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TRAILING_RETURN_PARSE_(d, \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXCEPT_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_REF_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CV_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PARAMS_PARSE_(d, \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_NAME_PARSE_(d, \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_RETURN_PARSE_(d, \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CLASSIFIERS_PARSE_(d, \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TEMPLATE_PARSE_(d, \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXPORT_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VERBATIM_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_ACCESS_PARSE_( \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_INIT( \
        decl BOOST_PP_NIL \
    )))))))))))))))))

/* PRIVATE */

// To debug or test the pp parsing code, #define this internal macro to stop
// parsing at a given trait index as #defined in aux_/index/func.hpp:
// #define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST ...

// NOTE: These macros #definitions read TRAITS_FUNC instead of FUNC_TRAITS to
// avoid name clashes with macro #define in func/*.

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_MAX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_DONE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_DONE_ \
        BOOST_CONTRACT_EXT_PP_DECL_TRAITS_AUX_DONE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_ACCESS
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_ACCESS_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_ACCESS_PARSE_ \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_VERBATIM
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VERBATIM_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VERBATIM_PARSE_ \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_EXPORT
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXPORT_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXPORT_PARSE_ \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPORT_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_TEMPLATE
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TEMPLATE_PARSE_(d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TEMPLATE_PARSE_ \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_PARSE_D
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_CLASSIFIERS
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CLASSIFIERS_PARSE_( \
            d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CLASSIFIERS_PARSE_ \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_PARSE_D
#endif
        
#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_RETURN
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_RETURN_PARSE_(d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_RETURN_PARSE_ \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_PARSE_D
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_NAME
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_NAME_PARSE_(d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_NAME_PARSE_ \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_PARSE_D
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_PARAMS
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PARAMS_PARSE_(d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PARAMS_PARSE_ \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_PARSE_D
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_CV
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CV_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CV_PARSE_ \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CV_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_REF
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_REF_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_REF_PARSE_ \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_EXCEPT
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXCEPT_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXCEPT_PARSE_ \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_TRAILING_RETURN
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TRAILING_RETURN_PARSE_( \
            d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TRAILING_RETURN_PARSE_ \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TRAILING_RETURN_PARSE_D
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_VIRT
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VIRT_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VIRT_PARSE_ \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VIRT_PARSE
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_PRECONDITIONS
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PRECONDITIONS_PARSE_( \
            d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PRECONDITIONS_PARSE_ \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITIONS_PARSE_D
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_POSTCONDITIONS
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_POSTCONDITIONS_PARSE_( \
            d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_POSTCONDITIONS_PARSE_ \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITIONS_PARSE_D
#endif

#endif // #include guard

