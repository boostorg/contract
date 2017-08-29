
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_VIRTUAL_HPP_
#define CONTRACT_AUX_CODE_VIRTAUL_HPP_

#include <contract/aux_/mpl_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>

// PRIVATE //

#define CONTRACT_AUX_CODE_VIRTUAL_TAG_FUNC_(f) \
    CONTRACT_AUX_SYMBOL( (CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(f)) \
            (virtual_function_tag) )

#define CONTRACT_AUX_CODE_VIRTUAL_TAG_FUNC_PARAM_TYPE_ENUM_( \
        r, default01, i, p) \
    BOOST_PP_COMMA_IF(i) \
    CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(p) \
    BOOST_PP_ARRAY_ENUM(CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE(p))

#define CONTRACT_AUX_CODE_VIRTUAL_FUNC_SIGNATURE_(f, name) \
    /* NOTE: virtual functions decl this member func tag which existence */ \
    /* can be checked using the introspection metafunction also def here */ \
    CONTRACT_AUX_CODE_RESULT_TYPE(f, 0 /* don't allow empty result type */) \
    name \
    ( \
        BOOST_PP_LIST_FOR_EACH_I( \
                CONTRACT_AUX_CODE_VIRTUAL_TAG_FUNC_PARAM_TYPE_ENUM_, ~, \
                CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                        CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
    ) \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_CONST(f) \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_VOLATILE(f)

#define CONTRACT_AUX_CODE_VIRTUAL_TAG_DECL_(id, tpl, k, f) \
    CONTRACT_AUX_CODE_TEMPLATE_DECL( \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f), \
            CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                    CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
    CONTRACT_AUX_CODE_VIRTUAL_FUNC_SIGNATURE_(f, \
            CONTRACT_AUX_CODE_VIRTUAL_TAG_FUNC_(f)) \
    ; /* no tag func definition needed for SFINAE so `;` */

#define CONTRACT_AUX_CODE_VIRTUAL_CHECK_METAFUNC_(id) \
    CONTRACT_AUX_SYMBOL( (has_virtual_function_tag)(id) )

#define CONTRACT_AUX_CODE_VIRTUAL_CHECK_DEF_(id, tpl, k, f) \
    CONTRACT_AUX_HAS_XXX_MEMBER_FUNCTION( \
            CONTRACT_AUX_CODE_VIRTUAL_CHECK_METAFUNC_(id), \
            CONTRACT_AUX_CODE_VIRTUAL_TAG_FUNC_(f)) \

// PUBLIC //

// Return MPL type true_ or false_.
#define CONTRACT_AUX_CODE_HAS_VIRTUAL(id, f, class_type) \
    CONTRACT_AUX_CODE_VIRTUAL_CHECK_METAFUNC_(id)< \
        CONTRACT_AUX_CODE_VIRTUAL_FUNC_SIGNATURE_(f, (class_type::*)) \
    >

#define CONTRACT_AUX_CODE_VIRTUAL_TAG(id, tpl, k, f) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(CONTRACT_DETAIL_PP_FUNC_TRAITS_VIRTUAL(f)), \
        BOOST_PP_TUPLE_EAT(4) \
    , \
        public: /* must be public to be accessed from intro metafunc */ \
        CONTRACT_AUX_CODE_VIRTUAL_TAG_DECL_ \
    )(id, tpl, k, f) \
    private: /* check introspection metafunc can be private */ \
    CONTRACT_AUX_CODE_VIRTUAL_CHECK_DEF_(id, tpl, k, f)

#endif // #include guard

