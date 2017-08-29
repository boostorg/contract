
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_CLASS_TRAITS_HPP_
#define CONTRACT_DETAIL_PP_CLASS_TRAITS_HPP_

#include <contract/detail/preprocessor/traits/class/access.hpp>
#include <contract/detail/preprocessor/traits/class/export.hpp>
#include <contract/detail/preprocessor/traits/class/template.hpp>
#include <contract/detail/preprocessor/traits/class/concepts.hpp>
#include <contract/detail/preprocessor/traits/class/kind.hpp>
#include <contract/detail/preprocessor/traits/class/friend.hpp>
#include <contract/detail/preprocessor/traits/class/name.hpp>
#include <contract/detail/preprocessor/traits/class/specializations.hpp>
#include <contract/detail/preprocessor/traits/class/final.hpp>
#include <contract/detail/preprocessor/traits/class/bases.hpp>
#include <contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand to class traits (inspect using `CLASS_TRAITS`).
#define CONTRACT_DETAIL_PP_CLASS_TRAITS(class_signature) \
    BOOST_PP_TUPLE_ELEM(2, 0, /* get traits from `(traits, sign)` */ \
    CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_BASES( \
    CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_FINAL( \
    CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_SPECIALIZATIONS( \
    CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_NAME( \
    CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_KIND( \
    CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_FRIEND( \
    CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_CONCEPTS( \
    CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_TEMPLATE( \
    CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_EXPORT( \
    CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_ACCESS( \
        ( \
            CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* no traits to start with */ \
        , \
            class_signature \
            CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* terminates and for empty */ \
        ) \
    )))))))))))

#endif // #include guard

