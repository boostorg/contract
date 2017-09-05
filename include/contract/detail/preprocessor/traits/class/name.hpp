
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_CLASS_TRAITS_NAME_HPP_
#define CONTRACT_DETAIL_PP_CLASS_TRAITS_NAME_HPP_

#include <contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <contract/detail/preprocessor/traits/aux_/name.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PROTECTED //

#define CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_NAME(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            CONTRACT_DETAIL_PP_TRAITS_AUX_NAME, \
            CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME)

// PUBLIC //

// Expand to `class_name`.
#define CONTRACT_DETAIL_PP_CLASS_TRAITS_NAME(class_traits) \
    BOOST_PP_ARRAY_ELEM(6, class_traits)

#endif // #include guard

