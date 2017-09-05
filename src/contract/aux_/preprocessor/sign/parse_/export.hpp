// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_EXPORT_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_EXPORT_HPP_

#include "utility/optional.hpp"
#include "utility/append_traits.hpp"
#include "utility/match_not.hpp"
#include "../../keyword/is_export.hpp"

#define CONTRACT_AUX_PP_SIGN_PARSE_EXPORT(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_OPTIONAL( \
            seq_sign_err, CONTRACT_AUX_PP_KEYWORD_IS_EXPORT)

#define CONTRACT_AUX_PP_SIGN_PARSE_NO_EXPORT(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPEND_TRAITS( (BOOST_PP_EMPTY), \
            CONTRACT_AUX_PP_SIGN_PARSE_MATCH_NOT( \
                    CONTRACT_AUX_PP_KEYWORD_IS_EXPORT, \
                    CONTRACT_ERROR_cannot_specify_export_within_this_context, \
                    seq_sign_err))

#endif // #include guard

