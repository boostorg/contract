/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_FUN_MACRO_TRATIS_HPP_
#define DBC_FUN_MACRO_TRATIS_HPP_

#include "../post.hpp"
#include "pp/fun_traits.hpp"
#include "type_traits.hpp"
#include <boost/preprocessor.hpp>

// Contract kind (mem function, constructor, destructor, etc).

#define DBC_CONTRACT_KIND_MEM_FUN_  0
#define DBC_CONTRACT_KIND_CONSTR_   1
#define DBC_CONTRACT_KIND_DESTR_    2

#define DBC_GET_CONTRACT_TYPE_(kind) \
    BOOST_PP_IF(BOOST_PP_EQUAL(kind, DBC_CONTRACT_KIND_CONSTR_), \
        constr \
    , BOOST_PP_IF(BOOST_PP_EQUAL(kind, DBC_CONTRACT_KIND_DESTR_), \
        destr \
    , /* else */ \
        mem \
    )) /* end if */

// Argument names.

#define DBC_FUN_GET_ARG_NAME_OP_(z, n, f) \
    DBC_PP_FUN_GET_ARG_NAME_(DBC_PP_FUN_GET_ARG_(n, f))

#define DBC_FUN_GET_TRAILING_ARG_NAMES_(f) \
    BOOST_PP_COMMA_IF(DBC_PP_FUN_HAS_ARGS_(f)) \
    BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(DBC_PP_FUN_GET_ARGS_(f)), \
            DBC_FUN_GET_ARG_NAME_OP_, f)

// Argument types.

#define DBC_FUN_GET_ARG_TYPE_OP_(z, n, f) \
    DBC_PP_FUN_GET_ARG_COPYABLE_TYPE_(DBC_PP_FUN_GET_ARG_(n, f))

#define DBC_FUN_GET_ARG_TYPES_(f) \
    BOOST_PP_COMMA_IF(DBC_PP_FUN_HAS_ARGS_(f)) \
    BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(DBC_PP_FUN_GET_ARGS_(f)), \
            DBC_FUN_GET_ARG_TYPE_OP_, f)

// Body's arguments.

#define DBC_FUN_GET_BODY_ARG_OP_(z, n, f) \
    DBC_PP_FUN_GET_ARG_TYPE_(DBC_PP_FUN_GET_ARG_(n, f)) \
    DBC_PP_FUN_GET_ARG_NAME_(DBC_PP_FUN_GET_ARG_(n, f))

#define DBC_FUN_GET_BODY_ARGS_(f) \
    BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(DBC_PP_FUN_GET_ARGS_(f)), \
            DBC_FUN_GET_BODY_ARG_OP_, f)

// Require's arguments.

#define DBC_FUN_GET_MEM_REQUIRE_ARG_OP_(z, n, f) \
    DBC_ADD_CONST_REF_(DBC_PP_FUN_GET_TYPENAME_(f), \
            DBC_PP_FUN_GET_ARG_TYPE_(DBC_PP_FUN_GET_ARG_(n, f))) \
    DBC_PP_FUN_GET_ARG_NAME_(DBC_PP_FUN_GET_ARG_(n, f))

#define DBC_FUN_GET_MEM_REQUIRE_TRAILING_ARGS_(kind, f) \
    BOOST_PP_COMMA_IF(BOOST_PP_NOT_EQUAL(kind, DBC_CONTRACT_KIND_CONSTR_)) \
    BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(DBC_PP_FUN_GET_ARGS_(f)), \
            DBC_FUN_GET_MEM_REQUIRE_ARG_OP_, f)

#define DBC_FUN_GET_MEM_REQUIRE_ARGS_(kind, f) \
    /* self (but not for constructor) */ \
    BOOST_PP_EXPR_IF(BOOST_PP_NOT_EQUAL(kind, DBC_CONTRACT_KIND_CONSTR_), \
        DBC_ADD_CONST_REF_(DBC_PP_FUN_GET_TYPENAME_(f), \
            DBC_PP_FUN_GET_CLASS_TYPE_(f)) \
        self \
    ) /* end if */ \
    /* args (if any) */ \
    BOOST_PP_IF(DBC_PP_FUN_HAS_ARGS_(f), \
        DBC_FUN_GET_MEM_REQUIRE_TRAILING_ARGS_, BOOST_PP_TUPLE_EAT(2) \
    )(kind, f)

// Ensure's arguments.

#define DBC_FUN_GET_MEM_ENSURE_ARG_OP_(z, n, f) \
    DBC_ADD_POST_CONST_REF_(DBC_PP_FUN_GET_TYPENAME_(f), \
            DBC_PP_FUN_GET_ARG_COPYABLE_TYPE_( \
            DBC_PP_FUN_GET_ARG_(n, f))) \
    DBC_PP_FUN_GET_ARG_NAME_(DBC_PP_FUN_GET_ARG_(n, f))
    
#define DBC_FUN_GET_MEM_ENSURE_TRAILING_ARGS_(kind, f) \
    BOOST_PP_COMMA() \
    BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(DBC_PP_FUN_GET_ARGS_(f)), \
            DBC_FUN_GET_MEM_ENSURE_ARG_OP_, f) \

#define DBC_FUN_GET_MEM_ENSURE_ARGS_(kind, f) \
    /* post<> self */ \
    DBC_ADD_POST_CONST_REF_(DBC_PP_FUN_GET_TYPENAME_(f), \
            DBC_PP_FUN_GET_CONST_CLASS_COPYABLE_TYPE_(f)) \
    self \
    /* post<> args (if any) */ \
    BOOST_PP_IF(DBC_PP_FUN_HAS_ARGS_(f), \
        DBC_FUN_GET_MEM_ENSURE_TRAILING_ARGS_, BOOST_PP_TUPLE_EAT(2) \
    )(kind, f) \
    /* result (if non-void) */ \
    BOOST_PP_COMMA_IF(BOOST_PP_NOT(DBC_PP_FUN_IS_VOID_(f))) \
    BOOST_PP_IF(DBC_PP_FUN_IS_VOID_(f), BOOST_PP_EMPTY(), \
            DBC_ADD_CONST_REF_(DBC_PP_FUN_GET_TYPENAME_(f), \
            DBC_PP_FUN_GET_RESULT_TYPE_(f)) result)

// Contract name.

#define DBC_CONTRACT_NAME_FROM_SEQ_OP_(s, state, arg_name) \
    BOOST_PP_IF(BOOST_PP_IS_EMPTY(arg_name), state, \
        BOOST_PP_CAT(state, BOOST_PP_CAT(arg_name, _)))

#define DBC_CONTRACT_NAME_FROM_SEQ_(fun_name_args_const) \
    BOOST_PP_CAT(dbc_contract_, \
        BOOST_PP_IF(BOOST_PP_SEQ_SIZE(fun_name_args_const), \
            BOOST_PP_SEQ_FOLD_LEFT, BOOST_PP_TUPLE_EAT(3) \
        )(DBC_CONTRACT_NAME_FROM_SEQ_OP_, , fun_name_args_const) \
    )

#define DBC_FUN_GET_CONTRACT_NAME_ARG_OP_(z, state, arg) \
    state ( DBC_PP_FUN_GET_ARG_NAME_(arg) ) 

#define DBC_FUN_GET_CONTRACT_NAME_ARG_(f) \
    BOOST_PP_SEQ_FOLD_LEFT(DBC_FUN_GET_CONTRACT_NAME_ARG_OP_, , \
            DBC_PP_FUN_GET_ARGS_(f))

#define DBC_FUN_GET_CONTRACT_NAME_(f) DBC_CONTRACT_NAME_FROM_SEQ_( \
        /* build seq (name) (arg0)(arg1)... (const) */ \
        ( DBC_PP_FUN_GET_NAME_(f) ) \
        BOOST_PP_IF(DBC_PP_FUN_HAS_ARGS_(f), \
            DBC_FUN_GET_CONTRACT_NAME_ARG_, BOOST_PP_TUPLE_EAT(1) \
        )(f) \
        BOOST_PP_EXPR_IF(DBC_PP_FUN_IS_CONST_(f), (const) ) \
    )

// Contract type.

#define DBC_FUN_GET_MEM_CONTRACT_TYPE_(f, inner_contract_type) \
    ::dbc::fun< DBC_PP_FUN_GET_RESULT_TYPE_(f) \
    DBC_FUN_GET_ARG_TYPES_(f) >:: DBC_PP_FUN_GET_TEMPLATE_(f) \
    inner_contract_type< DBC_PP_FUN_GET_CONST_CLASS_COPYABLE_TYPE_(f) \
            /* base contract (if any) */ \
            BOOST_PP_COMMA_IF(DBC_PP_FUN_IS_DERIVED_(f)) \
            BOOST_PP_IF(DBC_PP_FUN_IS_DERIVED_(f), \
                DBC_PP_FUN_GET_TYPENAME_(f) \
                DBC_PP_FUN_GET_BASE_TYPE_(f) \
                :: DBC_FUN_GET_CONTRACT_NAME_(f) \
            , /* else (no base contract) */ \
                BOOST_PP_EMPTY()) \
    > \
    BOOST_PP_IF(DBC_PP_FUN_IS_TEMPLATE_(f), ::this_type, BOOST_PP_EMPTY())

// Base contract type.

#define DBC_FUN_GET_MEM_BASE_CONTRACT_TYPE_(f) \
    BOOST_PP_IF(DBC_PP_FUN_IS_DERIVED_(f), \
        DBC_PP_FUN_GET_TYPENAME_(f) DBC_PP_FUN_GET_BASE_TYPE_(f) \
        :: DBC_FUN_GET_CONTRACT_NAME_(f) ::class_type \
    , BOOST_PP_EMPTY())

#endif // DBC_FUN_MACRO_TRATIS_HPP_

