
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_OVERRIDE_HPP_
#define CONTRACT_AUX_CODE_OVERRIDE_HPP_

#include <contract/aux_/mpl_assert.hpp>
#include <contract/aux_/macro/code_/virtual.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>
#include <boost/preprocessor/control/expr_if.hpp>

// PRIVATE //

#define CONTRACT_AUX_CODE_OVERRIDE_CONDITION_OR_BASE_(r, n, id_f) \
    /* (base != class && has_virtual_function_tag<base::func>) || ... */ \
    BOOST_PP_EXPR_IF(n, ||) \
    (::boost::mpl::and_< \
          ::boost::mpl::not_< ::boost::is_same< \
              CONTRACT_AUX_CODE_BASE_TYPE(n) \
            , CONTRACT_AUX_CODE_CLASS_TYPE \
          > > \
        , CONTRACT_AUX_CODE_HAS_VIRTUAL(BOOST_PP_TUPLE_ELEM(2, 0, id_f), \
                BOOST_PP_TUPLE_ELEM(2, 1, id_f), \
                CONTRACT_AUX_CODE_BASE_TYPE(n)) \
    >::value)

#define CONTRACT_AUX_CODE_OVERRIDE_CHECK_(id, tpl, k, f) \
    CONTRACT_AUX_MPL_ASSERT_MSG( \
          CONTRACT_AUX_CODE_OVERRIDE_CONDITION(id, tpl, k, f) \
        , BOOST_PP_SEQ_CAT( \
  (ERROR_no_base_class_declares_matching_virtual_function_to_override_at_line_)\
                (id)) \
        , ( /* can't print bases here because they can be more than 4 */ ) \
    ); /* MPL assert requires trailing `;` */

// PUBLIC //

#define CONTRACT_AUX_CODE_OVERRIDE_CONDITION(id, tpl, k, f) \
    ( BOOST_PP_REPEAT(CONTRACT_CONFIG_INHERITANCE_MAX, \
            CONTRACT_AUX_CODE_OVERRIDE_CONDITION_OR_BASE_, (id, f)) ) \

#define CONTRACT_AUX_CODE_OVERRIDE_CHECK(id, tpl, k, f) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(CONTRACT_DETAIL_PP_FUNC_TRAITS_OVERRIDE(f)),\
        BOOST_PP_TUPLE_EAT(4) \
    , \
        CONTRACT_AUX_CODE_OVERRIDE_CHECK_ \
    )(id, tpl, k, f)

#endif // #include guard

