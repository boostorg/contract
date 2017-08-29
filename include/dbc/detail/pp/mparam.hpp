/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_PP_MPARAM_HPP_
#define DBC_PP_MPARAM_HPP_

#include <boost/preprocessor.hpp>

#define DBC_PP_MPARAM_GET_TOKEN_(z, n, tokens_array) \
    BOOST_PP_ARRAY_ELEM(n, tokens_array)

#define DBC_PP_MPARAM_(count, tokens) \
    BOOST_PP_ENUM(count, DBC_PP_MPARAM_GET_TOKEN_, (count, tokens) /* array */)

#endif // DBC_PP_MPARAM_HPP_

