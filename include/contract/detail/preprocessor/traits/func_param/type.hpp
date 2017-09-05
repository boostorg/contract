
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE_HPP_
#define CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE_HPP_

#include <contract/detail/preprocessor/traits/aux_/apply_1.hpp>
#include <contract/detail/preprocessor/traits/aux_/type.hpp>
#include <contract/detail/preprocessor/keyword/contract/requires.hpp>
#include <contract/detail/preprocessor/keyword/contract/deduce.hpp>
#include <contract/detail/preprocessor/keyword/auto.hpp>
#include <contract/detail/preprocessor/keyword/void.hpp>
#include <contract/detail/preprocessor/keyword/using.hpp>
#include <contract/detail/preprocessor/keyword/namespace.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/array/push_front.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE_NO_(sign, after01) \
    BOOST_PP_IIF(after01, \
        sign \
    , \
        (0, ()) /* no type */ \
    )
    
#define CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE_YES_(sign, after01) \
    BOOST_PP_IIF(after01, \
        CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TYPE \
    , \
        CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE \
    )(sign)

#define CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE_(sign, after01) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_VOID_FRONT(sign), \
        /* skip `void` for empty param list `(void)` */ \
        CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE_NO_ \
    , BOOST_PP_IIF(BOOST_PP_AND( /* BITAND doesn't expand properly on MSVC */ \
            CONTRACT_DETAIL_PP_KEYWORD_IS_USING_FRONT(sign), \
            CONTRACT_DETAIL_PP_KEYWORD_IS_NAMESPACE_FRONT( \
                    CONTRACT_DETAIL_PP_KEYWORD_USING_REMOVE_FRONT(sign))), \
        /* skip named params `using namespace tag` as it has no type */ \
        CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE_NO_ \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT(sign), \
        /* skip deduced named params list `deduce( ... )` has no type */ \
        CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE_NO_ \
    , \
        /* actual type or requirement (for positional and named param) */ \
        CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE_YES_ \
    )))(sign, after01)

#define CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_AUX_TYPE_TRAIT_(sign) \
    CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE_(sign, 0 /* current */)

#define CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_AUX_TYPE_SIGN_(sign) \
    CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE_(sign, 1 /* after */)

// PROTECTED //

#define CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_AUX_TYPE(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY_1(traits_sign, \
            CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_AUX_TYPE_TRAIT_, \
            CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_AUX_TYPE_SIGN_)

// PUBLIC //

// Expand to type or named param only requirement `(n, (type_token0, ...))`
// (0-sized array for no type (e.g., named param any type), array to handle
// unwrapped commas).
#define CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE(fparam_traits) \
    BOOST_PP_ARRAY_ELEM(1, BOOST_PP_TUPLE_ELEM(2, 0, fparam_traits))

#endif // #include guard

