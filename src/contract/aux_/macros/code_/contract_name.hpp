// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_CODE_CONTRACT_NAME_HPP_
#define CONTRACT_AUX_CODE_CONTRACT_NAME_HPP_

#include "function_sign.hpp"
#include "../../preprocessor/sign/args.hpp"
#include "../../preprocessor/sign/const.hpp"
#include "../../symbol.hpp"
#include <boost/preprocessor.hpp>

#define CONTRACT_AUX_CODE_CONTRACT_NAME_FROM_SEQ_OP_( \
        s, state, arg_name) \
    BOOST_PP_IF(BOOST_PP_IS_EMPTY(arg_name), state, \
            BOOST_PP_CAT(state, BOOST_PP_CAT(arg_name, _)))

#define CONTRACT_AUX_CODE_CONTRACT_NAME_FROM_SEQ_( \
        name_args_const_seq) \
    CONTRACT_AUX_SYMBOL( \
            BOOST_PP_IF(BOOST_PP_SEQ_SIZE(name_args_const_seq), \
                BOOST_PP_SEQ_FOLD_LEFT, BOOST_PP_TUPLE_EAT(3) \
            )(CONTRACT_AUX_CODE_CONTRACT_NAME_FROM_SEQ_OP_, , \
                    name_args_const_seq) \
    )

#define CONTRACT_AUX_CODE_CONTRACT_NAME_ARGS_OP_(z, state, arg) \
    state ( CONTRACT_AUX_PP_SIGN_ARG_NAME(arg) )

#define CONTRACT_AUX_CODE_CONTRACT_NAME_ARGS_(sign) \
    BOOST_PP_SEQ_FOLD_LEFT(CONTRACT_AUX_CODE_CONTRACT_NAME_ARGS_OP_, \
            , CONTRACT_AUX_PP_SIGN_ARGS(sign))

#define CONTRACT_AUX_CODE_CONTRACT_NAME_PREFIXED(kind, sign, \
        prefix_seq) \
    CONTRACT_AUX_CODE_CONTRACT_NAME_FROM_SEQ_( \
            prefix_seq \
            /* build seq (name) (arg0) ... (const) */ \
            ( CONTRACT_AUX_CODE_FUNCTION_NAME(kind, sign) ) \
            BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_HAS_ARGS(sign), \
                CONTRACT_AUX_CODE_CONTRACT_NAME_ARGS_ \
            , \
                BOOST_PP_TUPLE_EAT(1) \
            )(sign) \
            BOOST_PP_EXPR_IF(CONTRACT_AUX_PP_SIGN_IS_CONST(sign), \
                ( const ) \
            ) /* cannot just concat empty seq elem () if not const */ \
    )

// Cannot just call macro above with prefix () because some compiler
// do not support empty seq elements -- must repeat the code...
#define CONTRACT_AUX_CODE_CONTRACT_NAME(kind, sign) \
    CONTRACT_AUX_CODE_CONTRACT_NAME_FROM_SEQ_( \
            /* build seq (name) (arg0) ... (const) */ \
            ( CONTRACT_AUX_CODE_FUNCTION_NAME(kind, sign) ) \
            BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_HAS_ARGS(sign), \
                CONTRACT_AUX_CODE_CONTRACT_NAME_ARGS_ \
            , \
                BOOST_PP_TUPLE_EAT(1) \
            )(sign) \
            BOOST_PP_EXPR_IF(CONTRACT_AUX_PP_SIGN_IS_CONST(sign), \
                ( const ) \
            ) /* cannot just concat empty seq elem () if not const */ \
    )


#endif // #include guard

