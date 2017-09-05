
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_RESULT_TYPE_HPP_
#define CONTRACT_AUX_CODE_RESULT_TYPE_HPP_

#include <contract/detail/preprocessor/traits/func/result_type.hpp>
#include <contract/detail/preprocessor/traits/func/name.hpp>
#include <contract/detail/preprocessor/keyword/operator.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <boost/preprocessor/array/enum.hpp>

// PRIVATE //

#define CONTRACT_AUX_CODE_RESULT_TYPE_HANDLE_EMPTY_(f) \
    BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_OPERATOR(f)),\
        /* implicit type conversion operators `operator int* ( void )` have */ \
        /* empty result type and their result type is made to match the */ \
        /* operator symbolic type `int*` */ \
        BOOST_PP_ARRAY_ENUM \
    , \
        /* constructors and destructors have empty result type and their */ \
        /* result type is made to be void */ \
        void BOOST_PP_TUPLE_EAT(1) \
    )(CONTRACT_DETAIL_PP_FUNC_TRAITS_OPERATOR(f))

#define CONTRACT_AUX_CODE_RESULT_TYPE_NOT_EMPTY_(f) \
    BOOST_PP_ARRAY_ENUM(CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE(f))

// PUBLIC //

#define CONTRACT_AUX_CODE_RESULT_TYPE(f, allow_empty) \
    BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_RESULT_TYPE(f)), \
        CONTRACT_AUX_CODE_RESULT_TYPE_NOT_EMPTY_ \
    , BOOST_PP_IIF(allow_empty, \
        BOOST_PP_TUPLE_EAT(1) /* expand to empty */ \
    , \
        CONTRACT_AUX_CODE_RESULT_TYPE_HANDLE_EMPTY_ \
    ))(f)

#endif // #include guard

