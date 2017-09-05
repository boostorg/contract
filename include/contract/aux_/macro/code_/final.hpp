
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_FINAL_HPP_
#define CONTRACT_AUX_CODE_FINAL_HPP_

#include <contract/aux_/mpl_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>

// PRIVATE //

#define CONTRACT_AUX_CODE_FINAL_CHECK_METAFUNC_(id) \
    CONTRACT_AUX_SYMBOL( (has_final_function_tag)(id) )

#define CONTRACT_AUX_CODE_FINAL_TAG_FUNC_(f) \
    CONTRACT_AUX_SYMBOL( (CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(f)) \
            (final_function_tag) )

#define CONTRACT_AUX_CODE_FINAL_TAG_FUNC_PARAM_TYPE_ENUM_(r, default01, i, p) \
    BOOST_PP_COMMA_IF(i) \
    CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(p) \
    BOOST_PP_ARRAY_ENUM(CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE(p))

#define CONTRACT_AUX_CODE_FINAL_TAG_FUNC_SIGNATURE_(f, name) \
    /* NOTE: final functions decl this member func tag then overriding */ \
    /* functions statically assert (using introspection) that none of their */ \
    /* base functions have the final tag member func (i.e., they were final) */\
    CONTRACT_AUX_CODE_RESULT_TYPE(f, 0 /* no empty result type */) \
    name \
    ( \
        BOOST_PP_LIST_FOR_EACH_I( \
                CONTRACT_AUX_CODE_FINAL_TAG_FUNC_PARAM_TYPE_ENUM_, ~, \
                CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                        CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
    ) \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_CONST(f) \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_VOLATILE(f)

#define CONTRACT_AUX_CODE_FINAL_TAG_DECL_(id, tpl, k, f) \
    CONTRACT_AUX_CODE_TEMPLATE_DECL( \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f), \
            CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                    CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
    CONTRACT_AUX_CODE_FINAL_TAG_FUNC_SIGNATURE_(f, \
            CONTRACT_AUX_CODE_FINAL_TAG_FUNC_(f)) \
    ; /* no tag func definition needed for SFINAE so `;` */

#define CONTRACT_AUX_CODE_FINAL_CHECK_BASE_(r, n, id_f) \
    CONTRACT_AUX_MPL_ASSERT_MSG( \
        /* base == class || !has_final_function_tag<base::func> */ \
          (::boost::mpl::or_< \
              ::boost::is_same< \
                  CONTRACT_AUX_CODE_BASE_TYPE(n) \
                , CONTRACT_AUX_CODE_CLASS_TYPE \
              > \
            , ::boost::mpl::not_< \
                CONTRACT_AUX_CODE_FINAL_CHECK_METAFUNC_( \
                        BOOST_PP_TUPLE_ELEM(2, 0, id_f))< \
                    CONTRACT_AUX_CODE_FINAL_TAG_FUNC_SIGNATURE_( \
                            BOOST_PP_TUPLE_ELEM(2, 1, id_f), \
                            (CONTRACT_AUX_CODE_BASE_TYPE(n)::*) ) \
                > \
              > \
          >::value) \
        , BOOST_PP_SEQ_CAT( \
                (ERROR_cannot_override_final_function_from_base_class_number_) \
                (BOOST_PP_INC(n))(_at_line_)(BOOST_PP_TUPLE_ELEM(2, 0, id_f)) )\
        , (types< CONTRACT_AUX_CODE_BASE_TYPE(n) >) \
    ); /* MPL assert requires trailing `;` */

// PUBLIC //

#define CONTRACT_AUX_CODE_FINAL_TAG(id, tpl, k, f) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(CONTRACT_DETAIL_PP_FUNC_TRAITS_FINAL(f)), \
        BOOST_PP_TUPLE_EAT(4) \
    , \
        public: /* tag must be public to be accessed from intro metafunc */ \
        CONTRACT_AUX_CODE_FINAL_TAG_DECL_ \
    )(id, tpl, k, f) \
    private: /* check introspection metafunc can be private */ \
    CONTRACT_AUX_HAS_XXX_MEMBER_FUNCTION( \
            CONTRACT_AUX_CODE_FINAL_CHECK_METAFUNC_(id), \
            CONTRACT_AUX_CODE_FINAL_TAG_FUNC_(f)) \

#define CONTRACT_AUX_CODE_FINAL_CHECK(id, tpl, k, f) \
    BOOST_PP_REPEAT(CONTRACT_CONFIG_INHERITANCE_MAX, \
            CONTRACT_AUX_CODE_FINAL_CHECK_BASE_, (id, f))

#endif // #include guard

