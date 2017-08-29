// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_TEMPLATE_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_TEMPLATE_HPP_

#include "args.hpp"
#include "../../keyword/is_template.hpp"
#include "../../seq.hpp"
#include "utility/next.hpp"
#include "utility/match_not.hpp"
#include "utility/returns.hpp"

// This code allows also for empty template args () or ( (void) ).
// This might be usefull for some template specializations...

#define CONTRACT_AUX_PP_SIGN_PARSE_TEMPLATE_ARGS_(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_NONCOPYABLE_ARGS( \
        /* skip leading (template) keyword */ \
        CONTRACT_AUX_PP_SIGN_PARSE_NEXT_SKIP(seq_sign_err))

#define CONTRACT_AUX_PP_SIGN_PARSE_TEMPLATE_NO_(seq_sign_err) \
    /* not a template, return unchanged (seq, sign, err) */ \
    CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK(seq_sign_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err), \
            ( ( (BOOST_PP_EMPTY, BOOST_PP_EMPTY, BOOST_PP_EMPTY) ) ) \
            )

#define CONTRACT_AUX_PP_SIGN_PARSE_TEMPLATE_ARGS(seq_sign_err) \
    BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_PARSE_NEXT_IS_NOT( \
            seq_sign_err, CONTRACT_AUX_PP_KEYWORD_IS_TEMPLATE), \
        CONTRACT_AUX_PP_SIGN_PARSE_TEMPLATE_NO_ \
    , /* else */ \
        CONTRACT_AUX_PP_SIGN_PARSE_TEMPLATE_ARGS_ \
    )(seq_sign_err)

#define CONTRACT_AUX_PP_SIGN_PARSE_NO_TEMPLATE_ARGS(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPEND_TRAITS( \
            ( ( (BOOST_PP_EMPTY, BOOST_PP_EMPTY, BOOST_PP_EMPTY) ) ), \
            CONTRACT_AUX_PP_SIGN_PARSE_MATCH_NOT( \
                    CONTRACT_AUX_PP_KEYWORD_IS_TEMPLATE, \
                    CONTRACT_ERROR_cannot_specify_template_arguments_in_this_context, \
                    seq_sign_err))

#endif // #include guard

