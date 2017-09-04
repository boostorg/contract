/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_PP_FUN_PARSE_CLASS_TYPE_HPP_
#define DBC_PP_FUN_PARSE_CLASS_TYPE_HPP_

#include "../keywords.hpp"
#include "util/optional.hpp"
#include "util/copyable.hpp"
#include "util/match_not.hpp"
   
#define DBC_PP_FUN_PARSE_CLASS_TYPE_(sign_traits_err) \
    DBC_PP_FUN_PARSE_COPYABLE_( \
        DBC_PP_FUN_PARSE_OPTIONAL_(sign_traits_err, DBC_PP_IS_TEMPLATE_), \
        DBC_ERROR_missing_class_type_ \
    )

#define DBC_PP_FUN_PARSE_UNCOPYABLE_CLASS_TYPE_(sign_traits_err) \
    DBC_PP_FUN_PARSE_COPYABLE_( \
        DBC_PP_FUN_PARSE_MATCH_NOT_(DBC_PP_IS_COPYABLE_, \
            DBC_ERROR_class_type_cannot_be_specified_copyable_in_this_context_, \
            DBC_PP_FUN_PARSE_OPTIONAL_(sign_traits_err, DBC_PP_IS_TEMPLATE_) \
        ), \
        DBC_ERROR_missing_class_type_ \
    )

#endif // DBC_PP_FUN_PARSE_CLASS_TYPE_HPP_

