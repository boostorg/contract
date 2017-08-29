/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_PP_FUN_TRAITS_HPP_
#define DBC_PP_FUN_TRAITS_HPP_

#include "keywords.hpp"
#include <boost/preprocessor.hpp>

/** 
 * Inspect specified function traits as parsed from preprocessor function 
 * signature.
 * In this context function can be either a member or non member function.
 * For non member function some traits will trivially return BOOST_PP_EMPTY()
 * (like the trait to get the function access DBC_PP_MEM_GET_ACCESS_()).
 * The "f" parameter below is the function traits sequence as the 2nd element 
 * of the tuple returned by the DBC_PP_FUN_() macro.
 */

#define DBC_PP_FUN_TRAITS_COUNT_ 9 // Index in [0, COUNT - 1].

#define DBC_PP_FUN_GET_ACCESS_(f) BOOST_PP_SEQ_ELEM(0, f)
#define DBC_PP_FUN_IS_PRIVATE_(f) DBC_PP_IS_PRIVATE_(DBC_PP_FUN_GET_ACCESS_(f))
#define DBC_PP_FUN_IS_PROTECTED_(f) \
    DBC_PP_IS_PROTECTED_(DBC_PP_FUN_GET_ACCESS_(f))
#define DBC_PP_FUN_IS_PUBLIC_(f) DBC_PP_IS_PUBLIC_(DBC_PP_FUN_GET_ACCESS_(f))

#define DBC_PP_FUN_GET_VIRTUAL_(f) BOOST_PP_SEQ_ELEM(1, f)
#define DBC_PP_FUN_IS_VIRTUAL_(f) \
    BOOST_PP_NOT(BOOST_PP_IS_EMPTY(DBC_PP_FUN_GET_VIRTUAL_(f)))

#define DBC_PP_FUN_GET_RESULT_TYPE_(f) BOOST_PP_SEQ_ELEM(2, f)
#define DBC_PP_FUN_IS_VOID_(f) DBC_PP_IS_VOID_(DBC_PP_FUN_GET_RESULT_TYPE_(f))
#define DBC_PP_FUN_GET_RETURN_(f) \
    BOOST_PP_IF(DBC_PP_FUN_IS_VOID_(f), BOOST_PP_EMPTY(), return)

#define DBC_PP_FUN_GET_TEMPLATE_(f) BOOST_PP_SEQ_ELEM(3, f)
#define DBC_PP_FUN_IS_TEMPLATE_(f) \
    BOOST_PP_NOT(BOOST_PP_IS_EMPTY(DBC_PP_FUN_GET_TEMPLATE_(f)))
#define DBC_PP_FUN_GET_TYPENAME_(f) \
    BOOST_PP_IF(DBC_PP_FUN_IS_TEMPLATE_(f), typename, BOOST_PP_EMPTY())

#define DBC_PP_FUN_IS_CLASS_COPYABLE_(f) \
    BOOST_PP_NOT(BOOST_PP_IS_EMPTY( \
    BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_SEQ_ELEM(4, f))))
#define DBC_PP_FUN_GET_CLASS_TYPE_(f) \
    BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_SEQ_ELEM(4, f))
#define DBC_PP_FUN_GET_CLASS_COPYABLE_TYPE_(f) \
    BOOST_PP_EXPR_IF(DBC_PP_FUN_IS_CLASS_COPYABLE_(f), ::dbc::copyable<) \
    DBC_PP_FUN_GET_CLASS_TYPE_(f) \
    BOOST_PP_EXPR_IF(DBC_PP_FUN_IS_CLASS_COPYABLE_(f), >)

#define DBC_PP_FUN_GET_BASE_TYPE_(f) BOOST_PP_SEQ_ELEM(5, f)
#define DBC_PP_FUN_IS_DERIVED_(f) \
    BOOST_PP_NOT(BOOST_PP_IS_EMPTY(DBC_PP_FUN_GET_BASE_TYPE_(f)))

#define DBC_PP_FUN_GET_NAME_(f) BOOST_PP_SEQ_ELEM(6, f)

#define DBC_PP_FUN_GET_ARGS_(f) BOOST_PP_SEQ_ELEM(7, f)
#define DBC_PP_FUN_HAS_ARGS_(f) BOOST_PP_SEQ_SIZE(DBC_PP_FUN_GET_ARGS_(f))
#define DBC_PP_FUN_GET_ARG_(n, f) BOOST_PP_SEQ_ELEM(n, DBC_PP_FUN_GET_ARGS_(f))

#define DBC_PP_FUN_IS_ARG_COPYABLE_(arg) \
    BOOST_PP_NOT(BOOST_PP_IS_EMPTY(BOOST_PP_TUPLE_ELEM(3, 0, arg)))
#define DBC_PP_FUN_GET_ARG_TYPE_(arg) BOOST_PP_TUPLE_ELEM(3, 1, arg)
#define DBC_PP_FUN_GET_ARG_COPYABLE_TYPE_(arg) \
    BOOST_PP_EXPR_IF(DBC_PP_FUN_IS_ARG_COPYABLE_(arg), ::dbc::copyable<) \
    DBC_PP_FUN_GET_ARG_TYPE_(arg) \
    BOOST_PP_EXPR_IF(DBC_PP_FUN_IS_ARG_COPYABLE_(arg), >)
#define DBC_PP_FUN_GET_ARG_NAME_(arg) BOOST_PP_TUPLE_ELEM(3, 2, arg)

#define DBC_PP_FUN_GET_CONST_(f) BOOST_PP_SEQ_ELEM(8, f)
#define DBC_PP_FUN_IS_CONST_(f) \
    BOOST_PP_NOT(BOOST_PP_IS_EMPTY(DBC_PP_FUN_GET_CONST_(f)))

#define DBC_PP_FUN_GET_CONST_CLASS_COPYABLE_TYPE_(f) \
    /* const qualifier must be within copyable<> */ \
    BOOST_PP_EXPR_IF(DBC_PP_FUN_IS_CLASS_COPYABLE_(f), ::dbc::copyable<) \
    DBC_PP_FUN_GET_CONST_(f) \
    DBC_PP_FUN_GET_CLASS_TYPE_(f) \
    BOOST_PP_EXPR_IF(DBC_PP_FUN_IS_CLASS_COPYABLE_(f), >)

#endif // DBC_PP_FUN_TRAITS_HPP_

