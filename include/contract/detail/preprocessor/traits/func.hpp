
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_FUNC_TRAITS_HPP_
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_HPP_

#include <contract/detail/preprocessor/traits/func/access.hpp>
#include <contract/detail/preprocessor/traits/func/export.hpp>
#include <contract/detail/preprocessor/traits/func/template.hpp>
#include <contract/detail/preprocessor/traits/func/concepts.hpp>
#include <contract/detail/preprocessor/traits/func/explicit.hpp>
#include <contract/detail/preprocessor/traits/func/inline.hpp>
#include <contract/detail/preprocessor/traits/func/extern.hpp>
#include <contract/detail/preprocessor/traits/func/static.hpp>
#include <contract/detail/preprocessor/traits/func/virtual.hpp>
#include <contract/detail/preprocessor/traits/func/friend.hpp>
#include <contract/detail/preprocessor/traits/func/result_type.hpp>
#include <contract/detail/preprocessor/traits/func/name.hpp>
#include <contract/detail/preprocessor/traits/func/params.hpp>
#include <contract/detail/preprocessor/traits/func/param_concepts.hpp>
#include <contract/detail/preprocessor/traits/func/const.hpp>
#include <contract/detail/preprocessor/traits/func/volatile.hpp>
#include <contract/detail/preprocessor/traits/func/override.hpp>
#include <contract/detail/preprocessor/traits/func/new.hpp>
#include <contract/detail/preprocessor/traits/func/final.hpp>
#include <contract/detail/preprocessor/traits/func/exceptions.hpp>
#include <contract/detail/preprocessor/traits/func/preconditions.hpp>
#include <contract/detail/preprocessor/traits/func/postconditions.hpp>
#include <contract/detail/preprocessor/traits/func/initializers.hpp>
#include <contract/detail/preprocessor/traits/func/catches.hpp>
#include <contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS(function_signature) \
    BOOST_PP_TUPLE_ELEM(2, 0, \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_CATCHES( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_INITIALIZERS( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_POSTCONDITIONS( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_PRECONDITIONS( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_EXCEPTIONS( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_FINAL( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_NEW( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_OVERRIDE( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_VOLATILE( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_CONST( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_PARAM_CONCEPTS( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_PARAMS( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_NAME( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_RESULT_TYPE( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_FRIEND( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_VIRTUAL( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_STATIC( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_EXTERN( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_INLINE( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_EXPLICIT( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_CONCEPTS( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_TEMPLATE( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_EXPORT( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_ACCESS( \
        ( \
            CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* no traits to start wtih */ \
        , \
            function_signature \
            CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* terminates and for empty */ \
        ) \
    )))))))))))))))))))))))))

#endif // #include guard

