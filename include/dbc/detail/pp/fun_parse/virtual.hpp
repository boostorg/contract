/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_PP_FUN_PARSE_VIRTUAL_HPP_
#define DBC_PP_FUN_PARSE_VIRTUAL_HPP_

#include "../keywords.hpp"
#include "util/optional.hpp"

#define DBC_PP_FUN_PARSE_VIRTUAL_(sign_traits_err) \
    DBC_PP_FUN_PARSE_OPTIONAL_(sign_traits_err, DBC_PP_IS_VIRTUAL_)

#endif // DBC_PP_FUN_PARSE_VIRTUAL_HPP_

