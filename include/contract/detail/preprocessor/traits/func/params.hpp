
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS_HPP_
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS_HPP_

#include <contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <contract/detail/preprocessor/traits/aux_/list.hpp>
#include <contract/detail/preprocessor/traits/params.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS_INDEX_ 12

// PROTECTED //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_PARAMS(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            CONTRACT_DETAIL_PP_FUNC_PARAMS_TRAITS, \
            CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_LIST)

// PUBLIC //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(func_traits) \
    BOOST_PP_ARRAY_ELEM(CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS_INDEX_, \
            func_traits)

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS_REPLACE( \
        func_traits, fparams_sign) \
    /* can't use ARRAY_REPLACE because it has reentrancy _D */ \
    ( BOOST_PP_ARRAY_SIZE(func_traits), \
    ( \
          CONTRACT_DETAIL_PP_ARRAY_REM(CONTRACT_DETAIL_PP_ARRAY_FIRST_N( \
                CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS_INDEX_, \
                func_traits)) \
        , CONTRACT_DETAIL_PP_FUNC_PARAMS_TRAITS(fparams_sign) \
        , CONTRACT_DETAIL_PP_ARRAY_REM(CONTRACT_DETAIL_PP_ARRAY_REST_N( \
                BOOST_PP_INC(CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS_INDEX_), \
                func_traits)) \
    ) )

#endif // #include guard

