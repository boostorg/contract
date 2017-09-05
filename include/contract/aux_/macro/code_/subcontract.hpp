
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_SUBCONTRACT_HPP_
#define CONTRACT_AUX_CODE_SUBCONTRACT_HPP_

#include <contract/aux_/subcontract/from.hpp>
#include <contract/aux_/subcontract/has_class_invariant.hpp>

// PRIVATE //

#define CONTRACT_AUX_CODE_SUBCONTRACT_FUNC_BASE_TYPEDEF_(z, n, id_tpl_f) \
    typedef \
        /* here typename only if enclosing scope is template (tpl = 1) but */ \
        /* not also if f is template (because if f is template no */ \
        /* subcontracting using mpl::false_ which is not type-dependent) */ \
        BOOST_PP_EXPR_IIF(BOOST_PP_TUPLE_ELEM(3, 1, id_tpl_f), \
            typename \
        ) \
        ::contract::aux::subcontract_from< \
              CONTRACT_AUX_CODE_CLASS_TYPE \
            , CONTRACT_AUX_CODE_BASE_TYPE(n) \
            , BOOST_PP_IIF(CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE( \
                    BOOST_PP_TUPLE_ELEM(3, 2, id_tpl_f)), \
                /* NOTE: member func tpl cannot be virtual so no subcontract */\
                ::boost::mpl::false_ \
                BOOST_PP_TUPLE_EAT(3) \
              , \
                CONTRACT_AUX_CODE_HAS_VIRTUAL \
              )(BOOST_PP_TUPLE_ELEM(3, 0, id_tpl_f), \
                    BOOST_PP_TUPLE_ELEM(3, 2, id_tpl_f), \
                    CONTRACT_AUX_CODE_BASE_TYPE(n)) \
        >::type \
        CONTRACT_AUX_CODE_SUBCONTRACTED_BASE_TYPE(BOOST_PP_TUPLE_ELEM( \
                3, 0, id_tpl_f), n) \
    ;

#define CONTRACT_AUX_CODE_SUBCONTRACT_INVARIANT_BASE_TYPEDEF_(z, n, id_tpl_c) \
    typedef \
        CONTRACT_AUX_CODE_CLASS_TYPENAME(BOOST_PP_TUPLE_ELEM(3, 1, id_tpl_c), \
                BOOST_PP_TUPLE_ELEM(3, 2, id_tpl_c)) \
        ::contract::aux::subcontract_from< \
              CONTRACT_AUX_CODE_CLASS_TYPE \
            , CONTRACT_AUX_CODE_BASE_TYPE(n) \
            , ::contract::aux::has_subcontracted_class_invariant< \
                void (CONTRACT_AUX_CODE_BASE_TYPE(n)::*) ( ) const \
              > \
        >::type \
        CONTRACT_AUX_CODE_SUBCONTRACTED_BASE_TYPE(BOOST_PP_TUPLE_ELEM(3, 0, \
                id_tpl_c), n) \
    ;

// PUBLIC //

#define CONTRACT_AUX_CODE_SUBCONTRACTED_BASE_TYPE(id, n) \
    CONTRACT_AUX_SYMBOL( (subcontracted_base)(n)(id) )

// Subcontract overriding function pre and post from all bases.
#define CONTRACT_AUX_CODE_SUBCONTRACT_PREPOSTCONDITION_FROM_BASES( \
        id, tpl, k, f) \
    BOOST_PP_REPEAT(CONTRACT_CONFIG_INHERITANCE_MAX, \
            CONTRACT_AUX_CODE_SUBCONTRACT_FUNC_BASE_TYPEDEF_, \
            (id, tpl, f))

// Subcontract (dynamic, volatile, and static) class inv from all bases.
#define CONTRACT_AUX_CODE_SUBCONTRACT_CLASS_INVARIANT_FROM_BASES(id, tpl, c) \
    BOOST_PP_REPEAT(CONTRACT_CONFIG_INHERITANCE_MAX, \
            CONTRACT_AUX_CODE_SUBCONTRACT_INVARIANT_BASE_TYPEDEF_, \
                    (id, tpl, c))

#endif // #include guard

