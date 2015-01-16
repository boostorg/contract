
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/precondition.hpp>
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
#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>

/* PRIVATE */

// To debug the pp parsing code, you can #define this internal macro to stop
// parsing at a given trait index as #defined in index.hpp (this is what some
// of this library tests do).
// #define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST ..._INDEX

// NOTE: These macros #definitions read TRITS_FUNC instead of FUNC_TRAITS to
// avoid name clashes with macro #define in func/*.

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_PRECONDITION_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PRECONDITION_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PRECONDITION_PARSE_(decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PRECONDITION_PARSE(decl_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_VIRT_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VIRT_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VIRT_PARSE_(decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VIRT_PARSE(decl_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_TRAILING_RETURN_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TRAILING_RETURN_PARSE_( \
            decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TRAILING_RETURN_PARSE_( \
            decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TRAILING_RETURN_PARSE(decl_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_EXCEPT_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXCEPT_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXCEPT_PARSE_(decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_PARSE(decl_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_REF_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_REF_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_REF_PARSE_(decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_PARSE(decl_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_CV_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CV_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CV_PARSE_(decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CV_PARSE(decl_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_PARAMS_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PARAMS_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PARAMS_PARSE_(decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_PARSE(decl_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_NAME_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_NAME_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_NAME_PARSE_(decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_PARSE(decl_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_RETURN_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_RETURN_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_RETURN_PARSE_(decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_PARSE(decl_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_CLASSIFIERS_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CLASSIFIERS_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CLASSIFIERS_PARSE_(decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_PARSE(decl_traits)
#endif
        
#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_TEMPLATE_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TEMPLATE_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TEMPLATE_PARSE_(decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_PARSE(decl_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_EXPORT_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXPORT_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXPORT_PARSE_(decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPORT_PARSE(decl_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_VERBATIM_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VERBATIM_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VERBATIM_PARSE_(decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_PARSE(decl_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_ACCESS_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_ACCESS_PARSE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_ACCESS_PARSE_(decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_PARSE(decl_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_DONE_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_DONE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_DONE_ \
        BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE
#endif

/* PUBLIC */

// Expand specified function declaration into its traits which can then be
// inspected using the ..._FUNC_TRAITS_... macros.
// WARNING: Order of these macros must match ..._INDEX values (see index.hpp).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS(decl) \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_DONE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PRECONDITION_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VIRT_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TRAILING_RETURN_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXCEPT_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_REF_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CV_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PARAMS_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_NAME_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_RETURN_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CLASSIFIERS_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TEMPLATE_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXPORT_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VERBATIM_PARSE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_ACCESS_PARSE_( \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl \
    ))))))))))))))))

#endif // #include guard

