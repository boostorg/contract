
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_HPP_
#define CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_HPP_

// Default value already processed, header included for user to access traits.
#include <contract/detail/preprocessor/traits/func_param/default.hpp>

#include <contract/detail/preprocessor/traits/func_param/classifier.hpp>
#include <contract/detail/preprocessor/traits/func_param/type.hpp>
#include <contract/detail/preprocessor/traits/func_param/name.hpp>
#include <contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand to template parameter traits (inspect with FUNC_PARAM_TRAITS).
#define CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS(fparam_sign) \
    BOOST_PP_TUPLE_ELEM(2, 0, \
    CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_AUX_NAME( \
    CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_AUX_TYPE( \
    CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_AUX_CLASSIFIER( \
        ( \
            CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* no traits to start with */ \
        , \
            fparam_sign \
            /* no trailing NIL because always name at end */ \
        ) \
    ))))

#endif // #include guard

