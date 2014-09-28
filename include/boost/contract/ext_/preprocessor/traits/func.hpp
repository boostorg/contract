
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/template.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/export.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/verbatim.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/access.hpp>
#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PRIVATE //

// You can set this internal macro to stop and debug at a func-trait index.
// define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_DEBUG_AT_

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_DEBUG_AT_) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_DEBUG_AT_ < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_TEMPLATE_INDEX
#   define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_(sign_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_PARSE(sign_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_DEBUG_AT_) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_DEBUG_AT_ < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_EXPORT_INDEX
#   define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPORT_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPORT_(sign_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPORT_PARSE(sign_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_DEBUG_AT_) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_DEBUG_AT_ < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_VERBATIM_INDEX
#   define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_(sign_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_PARSE(sign_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_DEBUG_AT_) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_DEBUG_AT_ < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_ACCESS_INDEX
#   define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_(sign_traits) \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_PARSE(sign_traits)
#endif

#if defined(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_DEBUG_AT_) && \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_DEBUG_AT_ < \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_DONE_INDEX
#   define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_DONE_(sign_traits) \
        sign_traits
#else
#   define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_DONE_(sign_traits) \
        BOOST_PP_TUPLE_ELEM(2, 1, sign_traits)
#endif

// PUBLIC //

// Expand specified function signature into its traits. Function traits are
// are inspected using the FUNC_TRAITS macros.
// WARNING: Order of these macros must match ..._INDEX values (see index.hpp).
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS(sign) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_DONE_( \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_( \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPORT_( \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM_( \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS_( \
        ( sign, BOOST_PP_EMPTY() ) \
    )))))

#endif // #include guard

