
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/virt_specifiers.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/except.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/ref.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/cv_qualifiers.hpp>
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

// NOTE: These macros #definitions read TRITS_FUNC instead of FUNC_TRAITS to
// avoid name clashes with macro #define in func/*.

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_VIRT_SPECIFIERS_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VIRT_SPECIFIERS_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VIRT_SPECIFIERS_(sign_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VIRT_SPECIFIERS_PARSE(sign_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_EXCEPT_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXCEPT_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXCEPT_(sign_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT_PARSE(sign_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_REF_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_REF_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_REF_(sign_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF_PARSE(sign_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_CV_QUALIFIERS_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CV_QUALIFIERS_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CV_QUALIFIERS_(sign_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CV_QUALIFIERS_PARSE(sign_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_PARAMS_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PARAMS_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PARAMS_(sign_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS_PARSE(sign_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_NAME_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_NAME_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_NAME_(sign_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME_PARSE(sign_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_RETURN_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_RETURN_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_RETURN_(sign_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN_PARSE(sign_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_CLASSIFIERS_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CLASSIFIERS_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CLASSIFIERS_(sign_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_PARSE(sign_traits)
#endif
        
#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_TEMPLATE_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TEMPLATE_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TEMPLATE_(sign_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_PARSE(sign_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_EXPORT_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXPORT_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXPORT_(sign_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPORT_PARSE(sign_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_VERBATIM_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VERBATIM_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VERBATIM_(sign_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_PARSE(sign_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_ACCESS_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_ACCESS_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_ACCESS_(sign_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_PARSE(sign_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_DONE_INDEX
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_DONE_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_DONE_ \
        BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_DONE
#endif

/* PUBLIC */

// Expand specified function signature into its traits. Function traits are
// are inspected using the FUNC_TRAITS macros.
// WARNING: Order of these macros must match ..._INDEX values (see index.hpp).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS(sign) \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_DONE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VIRT_SPECIFIERS_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXCEPT_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_REF_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CV_QUALIFIERS_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_PARAMS_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_NAME_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_RETURN_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_CLASSIFIERS_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_TEMPLATE_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_EXPORT_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_VERBATIM_( \
    BOOST_CONTRACT_EXT_PP_TRAITS_FUNC_ACCESS_( \
    BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_INIT( \
        sign \
    ))))))))))))))

#endif // #include guard

