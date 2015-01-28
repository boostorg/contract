
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/postcondition.hpp>
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
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>

/* PRIVATE */

// To debug the pp parsing code, you can #define this internal macro to stop
// parsing at a given trait index as #defined in index.hpp (this is what some
// of this library tests do).
// #define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST ..._INDEX

// NOTE: These macros #definitions read TRITS_FUNC instead of FUNC_TRAITS to
// avoid name clashes with macro #define in func/*.

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_POSTCONDITION_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_POSTCONDITION_PARSE_D( \
            d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_POSTCONDITION_PARSE_( \
            d, decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_POSTCONDITION_PARSE_D(d, decl_traits)
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
            d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TRAILING_RETURN_PARSE_( \
            d, decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TRAILING_RETURN_PARSE_D( \
                d, decl_traits)
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
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PARAMS_PARSE_(d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PARAMS_PARSE_(d, decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_PARSE_D(d, decl_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_NAME_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_NAME_PARSE_(d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_NAME_PARSE_(d, decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_PARSE_D(d, decl_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_RETURN_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_RETURN_PARSE_(d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_RETURN_PARSE_(d, decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_PARSE_D(d, decl_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_CLASSIFIERS_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CLASSIFIERS_PARSE_( \
            d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CLASSIFIERS_PARSE_( \
            d, decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_PARSE_D(d, decl_traits)
#endif
        
#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_TEMPLATE_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TEMPLATE_PARSE_(d, decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TEMPLATE_PARSE_(d, decl_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_PARSE_D(d, decl_traits)
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
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_MAX_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_DONE_(decl_traits) \
        decl_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_DONE_(decl_traits) \
        ( \
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
            BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(2, 1, \
                    decl_traits)) \
        )
#endif

/* PUBLIC */

// Expand function declaration to `(remaining-declaration, parsed-traits)`:
// * Parsed traits can be inspected using the FUNC_TRAITS macros.
// * Reaming declaration is `BOOST_PP_NIL` if there was no error.
// Implementation: These macros order must match INDEX values (see index.hpp).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARSE_D(d, decl) \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_DONE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_POSTCONDITION_PARSE_(d, \
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
        (decl BOOST_PP_NIL, BOOST_CONTRACT_EXT_PP_TRAITS_INIT) \
    )))))))))))))))

#endif // #include guard

