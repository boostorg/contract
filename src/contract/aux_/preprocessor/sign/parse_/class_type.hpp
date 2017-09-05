// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_CLASS_TYPE_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_CLASS_TYPE_HPP_

#include "utility/optional.hpp"
#include "utility/copyable.hpp"
#include "utility/match_not.hpp"
#include "utility/append_traits.hpp"
#include "utility/returns.hpp"
#include "../../keyword/is_template.hpp"
#include "../../keyword/is_copyable.hpp"
   
#define CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE_CLASS_TYPE( \
        seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE( \
            seq_sign_err, \
            CONTRACT_ERROR_missing_class_type)

#define CONTRACT_AUX_PP_SIGN_PARSE_NONCOPYABLE_CLASS_TYPE( \
        seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE( \
            CONTRACT_AUX_PP_SIGN_PARSE_MATCH_NOT( \
                    CONTRACT_AUX_PP_KEYWORD_IS_COPYABLE, \
                    CONTRACT_ERROR_class_type_cannot_be_tagged_copyable_in_this_context, \
                    seq_sign_err), \
            CONTRACT_ERROR_missing_class_type)
    
#define CONTRACT_AUX_PP_SIGN_PARSE_NO_CLASS_TYPE(seq_sign_err) \
    /* macro */ \
    BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER( \
            BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err)), \
        CONTRACT_AUX_PP_SIGN_PARSE_RETURN_ERR \
    , /* else */ \
        CONTRACT_AUX_PP_SIGN_PARSE_APPEND_TRAITS \
    ) /* endif */ \
    /* params */ \
    BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER( \
            BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err)), \
        ( BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err), \
            ( (BOOST_PP_EMPTY, BOOST_PP_EMPTY) ), \
            CONTRACT_ERROR_class_member_must_specify_class_type ) \
    , /* else */ \
        ( ( (BOOST_PP_EMPTY, BOOST_PP_EMPTY) ), seq_sign_err ) \
    ) /* endif */

#endif // #include guard

