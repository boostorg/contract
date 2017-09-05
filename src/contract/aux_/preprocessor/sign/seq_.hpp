// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_SEQ_HPP_
#define CONTRACT_AUX_PP_SIGN_SEQ_HPP_

// IMPORTNAT: These are for internal use only. This file contents
// should NOT be used from files outside this directory.

// Signature tokens.
#define CONTRACT_AUX_PP_SIGN_SEQ_CLASS_INDEX                     0
#define CONTRACT_AUX_PP_SIGN_SEQ_CLASS_TYPE_INDEX                1
#define CONTRACT_AUX_PP_SIGN_SEQ_BASE_TYPES_INDEX                2
#define CONTRACT_AUX_PP_SIGN_SEQ_ACCESS_INDEX                    3
#define CONTRACT_AUX_PP_SIGN_SEQ_EXPORT_INDEX                    4
#define CONTRACT_AUX_PP_SIGN_SEQ_FUNCTION_TEMPLATE_ARGS_INDEX    5
#define CONTRACT_AUX_PP_SIGN_SEQ_EXPLICIT_INDEX                  6
#define CONTRACT_AUX_PP_SIGN_SEQ_INLINE_INDEX                    7
#define CONTRACT_AUX_PP_SIGN_SEQ_EXTERN_INDEX                    8
#define CONTRACT_AUX_PP_SIGN_SEQ_STATIC_INDEX                    9
#define CONTRACT_AUX_PP_SIGN_SEQ_VIRTUAL_INDEX                  10
#define CONTRACT_AUX_PP_SIGN_SEQ_RESULT_TYPE_INDEX              11
#define CONTRACT_AUX_PP_SIGN_SEQ_FUNCTION_NAME_INDEX            12
#define CONTRACT_AUX_PP_SIGN_SEQ_ARGS_INDEX                     13
#define CONTRACT_AUX_PP_SIGN_SEQ_CONST_INDEX                    14
#define CONTRACT_AUX_PP_SIGN_SEQ_VOLATILE_INDEX                 15
// Contract tokens.
#define CONTRACT_AUX_PP_SIGN_SEQ_PRECONDITION_INDEX             16
#define CONTRACT_AUX_PP_SIGN_SEQ_POSTCONDITION_RESULT_INDEX     17
#define CONTRACT_AUX_PP_SIGN_SEQ_POSTCONDITION_INDEX            18
#define CONTRACT_AUX_PP_SIGN_SEQ_BODY_INDEX                     19

#define CONTRACT_AUX_PP_SIGN_SEQ_SIZE_NO_CONTRACT               16
#define CONTRACT_AUX_PP_SIGN_SEQ_SIZE_WITH_CONTRACT             20

// Signature Sequences
//
// A signature_sequence is first parsed using one of the
// PP_SIGN_PARSE_XYZ() macros. The parse macros return a 3-tuple
// (seq, sign, err):
// 0)   Element 0 (seq) is the remaining signature_sequence elements
//      (nothing if successfully parsed).
// 1)   Element 1 (sign) is the parsed signature sequence which can
//      be inspected using one of the PP_SIGN_XYZ macros (if the was
//      no parsing error).
// 2)   Element 2 (err) is the parsing error. This is a 2-tuple
//      (error_code, error_message) and there was a parsing error iff
//      error_code != 0, in which case error_message is a token
//      describing the error.
//
// In this context function can be either a member or non-member 
// function. For non member function some traits will trivially
// return BOOST_PP_EMPTY() (like the PP_SIGN_ACCESS() macro).
//
// Some of these elements can be empty (e.g., virtual) then these 
// macro return nothing, the related trait in sign ends with
// BOOST_PP_EMPTY so it is expanded here applying a trailing () to 
// the trait. This does not apply for non optional elements (e.g., 
// access) which are always present so their traits do not end with 
// BOOST_PP_EMPTY.
// For example, virtual is optional, the related trait in f will be 
// (virtual BOOST_PP_EMPTY) if virtual was specified or just
// (BOOST_PP_EMPTY) if virtual was not specified, in eihter case the 
// trait is expanded by the GET_VIRTUAL_ macro below applying a 
// terminating () so to get either 'virtual' or nothing ''. Instead, 
// access is not optional so its trait is either (public), (private),
// or (protected) (but never (BOOST_PP_EMPTY) ), the trait does not 
// end in BOOST_PP_EMPTY and it does not have to be expanded.
// Using simply () for an optional trait instead of (BOOST_PP_EMPTY)
// is not supported by the C++ standard (and it is allowed by GCC but
// not by MSVC) because empty macro parameters are not supported by
// C++ (they are instead by C99). Therefore, the complication of
// using BOOST_PP_EMPTY for traits that are optinal and can be empty
// is necessary to ensure standard compliance.

#endif // #include guard

