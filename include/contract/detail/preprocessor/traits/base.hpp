
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_BASE_TRAITS_HPP_
#define CONTRACT_DETAIL_PP_BASE_TRAITS_HPP_

#include <contract/detail/preprocessor/traits/base/virtual.hpp>
#include <contract/detail/preprocessor/traits/base/access.hpp>
#include <contract/detail/preprocessor/traits/base/type.hpp>
#include <contract/detail/preprocessor/traits/base/type.hpp>
#include <contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

#define CONTRACT_DETAIL_PP_BASE_TRAITS(base_sign) \
    BOOST_PP_TUPLE_ELEM(2, 0, /* get traits from `(traits, sign)` */ \
    CONTRACT_DETAIL_PP_BASE_TRAITS_AUX_TYPE( \
    CONTRACT_DETAIL_PP_BASE_TRAITS_AUX_VIRTUAL( \
    CONTRACT_DETAIL_PP_BASE_TRAITS_AUX_ACCESS( \
        ( \
            CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* no traits to start with */ \
        , \
            base_sign \
            /* no trailing NIL because always type at end */ \
        ) \
    ))))

#endif // #include guard

