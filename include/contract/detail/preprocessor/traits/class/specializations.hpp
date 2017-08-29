
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS_HPP_
#define CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS_HPP_

#include <contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <contract/detail/preprocessor/traits/aux_/list.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

// For reentrancy on GCC with C++0x.
#define CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS_REM_(tokens) tokens

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS_TRAIT_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_OPTIONAL_LIST(sign, \
            0, /* might not be empty (when present) */ \
            0, /* might not have defaults */ \
            CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS_REM_)

// PROTECTED //

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_SPECIALIZATIONS(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS_TRAIT_, \
            CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_OPTIONAL_LIST)

// PUBLIC //

// Expand to pp-list of template specialization types (empty iff the class is
// not a template specialization).
#define CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS(class_traits) \
    BOOST_PP_ARRAY_ELEM(7, class_traits)

#endif // #include guard

