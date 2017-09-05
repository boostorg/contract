
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_NAME_HPP_
#define CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_NAME_HPP_

#include <contract/detail/preprocessor/traits/aux_/apply_1.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PROTECTED //

#define CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_AUX_NAME(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY_1(traits_sign, \
            /* there's nothing else left in sign (no trailing nil) */ \
            BOOST_PP_TUPLE_REM(1), \
            BOOST_PP_TUPLE_REM(1))

// PUBLIC //

// Expand to parameter name.
#define CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_NAME(tparam_traits) \
    BOOST_PP_ARRAY_ELEM(2, BOOST_PP_TUPLE_ELEM(2, 0, tparam_traits))

#endif // #include guard

