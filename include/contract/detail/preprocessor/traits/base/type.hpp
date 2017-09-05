
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_BASE_TRAITS_TYPE_HPP_
#define CONTRACT_DETAIL_PP_BASE_TRAITS_TYPE_HPP_

#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_BASE_TRAITS_AUX_TYPE_(sign) \
    /* PP_REM because only type left in sign */ \
    CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA(BOOST_PP_TUPLE_REM(1), sign)

// PROTECTED //

#define CONTRACT_DETAIL_PP_BASE_TRAITS_AUX_TYPE(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY_1(traits_sign, \
            CONTRACT_DETAIL_PP_BASE_TRAITS_AUX_TYPE_, \
            BOOST_PP_TUPLE_REM(1)) /* nothing left in sign */

// PUBLIC //

// Expand to `(n, (base_token0, ...))` (array for unwrapped commas).
#define CONTRACT_DETAIL_PP_BASE_TRAITS_TYPE(base_traits) \
    BOOST_PP_ARRAY_ELEM(2, base_traits)

#endif // #include guard

