// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_HPP_

#include "utility/returns.hpp"
#include "utility/apply.hpp"
#include <boost/preprocessor.hpp>

// Validate parsed signature give more readable errors when possible.
// Also enforce common C++ constraints on signature -- static
// function cannot be virtual, etc.

// NOTE:    Only very basic checks are currently implemented.
//          Validation checks could be improved to provide the
//          user with better error checking and reporting in case of 
//          miss-usage of the preprocessor signature syntax (instead 
//          of often showing Boost.Preprocessor internal errors
//          or C++ unreadable template errors of the code generated
//          by the macro expansions all of which are of little help
//          for the user).
        
#define CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_ERR_(seq_sign_err, \
        error_msg) \
    CONTRACT_AUX_PP_SIGN_PARSE_RETURN_ERR(seq_sign_err, \
            BOOST_PP_EMPTY(), /* empty signature */ \
            BOOST_PP_EMPTY(), /* don't append any traits */ \
            error_msg)

// Internal Validations //

// Validate common signature parts (but no contract code blocks yet).
#define CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_NO_CONTRACT_COMMON_( \
        seq_sign_err, data) \
    /* check: seq size is complete (as before code blocks) */ \
    BOOST_PP_IF(BOOST_PP_NOT_EQUAL( \
            CONTRACT_AUX_PP_SIGN_SEQ_SIZE_NO_CONTRACT, \
            BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3, 1, \
            seq_sign_err))), \
        CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_ERR_(seq_sign_err, \
            CONTRACT_ERROR_missing_one_or_more_signature_token) \
    /* check: cannot be both virtual and static */ \
    , BOOST_PP_IF(BOOST_PP_AND( \
            CONTRACT_AUX_PP_SIGN_IS_VIRTUAL( \
                    BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err)), \
            CONTRACT_AUX_PP_SIGN_IS_STATIC( \
                    BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err))), \
        CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_ERR_(seq_sign_err, \
            CONTRACT_ERROR_static_functions_cannot_be_virtual) \
    /* check: cannot be both virtual and template */ \
    , BOOST_PP_IF(BOOST_PP_AND( \
            CONTRACT_AUX_PP_SIGN_IS_VIRTUAL( \
                    BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err)), \
            CONTRACT_AUX_PP_SIGN_HAS_FUNCTION_TEMPLATE_ARGS( \
                    BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err))), \
        CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_ERR_(seq_sign_err, \
            CONTRACT_ERROR_function_templates_cannot_be_virtual) \
    , /* else (it's valid, no error) */ \
        seq_sign_err /* done */ \
    )))

// Validate member function signature (but no pre, post, body block).
#define CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_MEMBER_( \
        seq_sign_err, data) \
    seq_sign_err /* validate nothing */

// Validate non-member func signature (but no pre, post, body block).
#define CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_NON_MEMBER_( \
        seq_sign_err, data) \
    seq_sign_err /* validate nothing */

// Validate constructor func signature (but no pre, post, body block).
#define CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_CONSTRUCTOR_( \
        seq_sign_err, data) \
    seq_sign_err /* validate nothing */

// Validate destructor func signature (but no pre, post, body block).
#define CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_DESTRUCTOR_( \
        seq_sign_err, data) \
    seq_sign_err /* validate nothing */

// Validation entire contract signature (including code blocks).
#define CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_CONTRACT_( \
        seq_sign_err, data) \
    /* check: inly 1 elem left in seq (BOOST_PP_EMPTY) */ \
    BOOST_PP_IF(BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE( \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err)), 1), \
        CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_ERR_(seq_sign_err, \
            CONTRACT_ERROR_extra_tokens_left_in_signature) \
    /* check: seq size is complete (including code blocks) */ \
    , BOOST_PP_IF(BOOST_PP_NOT_EQUAL( \
            CONTRACT_AUX_PP_SIGN_SEQ_SIZE_WITH_CONTRACT, \
            BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3, 1, \
            seq_sign_err))), \
        CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_ERR_(seq_sign_err, \
            CONTRACT_ERROR_missing_precondition_postcondition_or_body) \
    , /* else (it's valid, no error) */ \
        seq_sign_err /* done */ \
    ))

// API //

// Validate function signature but before parsing contract blocks.

#define CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_NO_CONTRACT_( \
        specific_validate_macro, seq_sign_err, data) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPLY_QUIET( \
            /* second validate specific parts */ \
            specific_validate_macro, \
            CONTRACT_AUX_PP_SIGN_PARSE_APPLY_QUIET( \
                    /* first validate common parts */ \
        CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_NO_CONTRACT_COMMON_, \
                    seq_sign_err, data), data)

#define CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_MEMBER(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_NO_CONTRACT_( \
            CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_MEMBER_, \
            seq_sign_err, ~)

#define CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_NON_MEMBER(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_NO_CONTRACT_( \
            CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_NON_MEMBER_, \
            seq_sign_err, ~)

#define CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_CONSTRUCTOR(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_NO_CONTRACT_( \
            CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_CONSTRUCTOR_, \
            seq_sign_err, ~)

#define CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_DESTRUCTOR(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_NO_CONTRACT_( \
            CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_DESTRUCTOR_, \
            seq_sign_err, ~)

// Validate after parsing entire contract including pre, post, body.

#define CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_CONTRACT(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPLY_QUIET( \
            CONTRACT_AUX_PP_SIGN_PARSE_VALIDATE_CONTRACT_, \
            seq_sign_err, ~)

#endif // #include guard

