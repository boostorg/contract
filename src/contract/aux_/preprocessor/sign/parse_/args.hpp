// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SIGN_PARSE_ARGS_HPP_
#define CONTRACT_AUX_PP_SIGN_PARSE_ARGS_HPP_

#include "utility/required.hpp"
#include "../../keyword/is_void.hpp"
#include "../../keyword/is_copyable.hpp"
#include <boost/preprocessor.hpp>

// The arg traits is represented as 1 sequence element containing a
// sequence of 3-tuples (this requires a lot of parenthesis...):
//  /* 1 seq elem */ ( /*seq inside the 1 seq*/ (
//  /* tuple */ ( arg-copyalbe 
//  BOOST_PP_EMPTY, arg-type BOOST_PP_EMPTY, arg-name BOOST_PP_EMPTY)
//  ( (c, t, n) )  ( (c, t, n) )  ... 
//  ( (BOOST_PP_EMPTY, BOOST_PP_EMPTY, BOOST_PP_EMPTY) )
//  /* trailing tuple */ ) /* seq inside 1 seq */ ) /* 1 seq elem */
// The trailing 3-tuple with all BOOST_PP_EMPTY is used to handle
// no-arguments (or "void-arguments" as in "(f)( (void) )" ). Because
// the arg-name is used to identify void-arguments, the arg-name of
// all arguments must end with BOOST_PP_EMPTY also.
// (This is very difficult to follow... _maybe_ PP_ARRAY could be 
// used to simply this?? array size 0 means no arguments, size 1 
// there is one array element that is the 3-tuple, etc??)

// Non-Copyable Argument //

#define CONTRACT_AUX_PP_SIGN_PARSE_NONCOPYABLE_ARG_OP_( \
        seq_sign_err_for_args) \
    /* got here only is args seq size >= 2 */ \
    BOOST_PP_IF(BOOST_PP_IS_EMPTY(BOOST_PP_SEQ_ELEM(0, \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err_for_args))), \
        ( (BOOST_PP_EMPTY), (BOOST_PP_EMPTY), \
        (1, CONTRACT_ERROR_given_empty_function_argument_type)) /* in BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err_for_args)) */ \
    , BOOST_PP_IF(BOOST_PP_IS_EMPTY(BOOST_PP_SEQ_ELEM(1, \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err_for_args))), \
        ( (BOOST_PP_EMPTY), (BOOST_PP_EMPTY), \
        (1, CONTRACT_ERROR_given_empty_function_argument_name)) /* in BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err_for_args)) */\
    , /* else */ \
        (   /* remove first 2 (type)(name) and continue */ \
            BOOST_PP_SEQ_REST_N(2, BOOST_PP_TUPLE_ELEM(3, 0, \
                    seq_sign_err_for_args)) \
        ,   BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err_for_args) \
            /* seq concat */ \
            ( BOOST_PP_SEQ_TO_TUPLE( \
                ( BOOST_PP_EMPTY ) /* ',' */ \
                ( BOOST_PP_SEQ_ELEM(0, BOOST_PP_TUPLE_ELEM(3, 0, \
                        /* type */ \
                        seq_sign_err_for_args)) BOOST_PP_EMPTY ) \
                ( BOOST_PP_SEQ_ELEM(1, BOOST_PP_TUPLE_ELEM(3, 0, \
                        /* name */ \
                        seq_sign_err_for_args)) BOOST_PP_EMPTY ) \
            ) /* tuple (EMPTY, type, name) */ \
            ) /* seq ( (EMPTY, type, name) ) */ \
        ,   (0, "") /* no error */ ) \
    )) /* end if */

#define CONTRACT_AUX_PP_SIGN_PARSE_NONCOPYABLE_ARG_( \
        seq_sign_err_for_args) \
    BOOST_PP_IF(BOOST_PP_LESS(BOOST_PP_SEQ_SIZE( \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err_for_args)), \
            2), \
        ( (BOOST_PP_EMPTY), (BOOST_PP_EMPTY), \
        (1, CONTRACT_ERROR_missing_function_argument_type_or_name)) /* but only these given BOOST_PP_STRINGIZE(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err_for_args))) "given as" BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err_for_args)) */ \
        BOOST_PP_TUPLE_EAT(1) \
    , /* else */ \
        CONTRACT_AUX_PP_SIGN_PARSE_NONCOPYABLE_ARG_OP_ \
    )(seq_sign_err_for_args) /* end if */

// Copyable Argumnet //

#define CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE_ARG_OP_( \
        seq_sign_err_for_args) \
    /* got here only is args seq size >= 3 */ \
    /* and elem 0 is (copyable) tag */ \
    /* SEQ_TAIL used below to hide copyable tag from err msg */ \
    BOOST_PP_IF(BOOST_PP_IS_EMPTY(BOOST_PP_SEQ_ELEM(1, \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err_for_args))), \
        ( (BOOST_PP_EMPTY), (BOOST_PP_EMPTY), \
        (1, CONTRACT_ERROR_given_empty_funtion_argument_type)) /* in BOOST_PP_STRINGIZE(BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err_for_args))) */ \
    , BOOST_PP_IF(BOOST_PP_IS_EMPTY(BOOST_PP_SEQ_ELEM(2, \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err_for_args))), \
        ( (BOOST_PP_EMPTY), (BOOST_PP_EMPTY), \
        (1, CONTRACT_ERROR_given_empty_funtion_argument_name)) /* in BOOST_PP_STRINGIZE(BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err_for_args)))*/ \
    , /* else */ \
        (   /* remove first 3 (copyable)(type)(name) and cont */ \
            BOOST_PP_SEQ_REST_N(3, BOOST_PP_TUPLE_ELEM(3, 0, \
                    seq_sign_err_for_args)) \
        ,   BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err_for_args) \
            /* seq concat */ \
            ( BOOST_PP_SEQ_TO_TUPLE( \
                (copyable BOOST_PP_EMPTY) /* copyable */ \
                ( BOOST_PP_SEQ_ELEM(1, BOOST_PP_TUPLE_ELEM(3, 0, \
                        /* type */ \
                        seq_sign_err_for_args)) BOOST_PP_EMPTY ) \
                ( BOOST_PP_SEQ_ELEM(2, BOOST_PP_TUPLE_ELEM(3, 0, \
                        /* name */ \
                        seq_sign_err_for_args)) BOOST_PP_EMPTY ) \
        ) /* tuple (copyable, type, name) */ \
        ) /* seq ( (copyable, type, name) ) */ \
        ,   (0, "") /* no error */ ) \
    )) /* end if */

#define CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE_ARG_( \
        seq_sign_err_for_args) \
    BOOST_PP_IF(BOOST_PP_LESS(BOOST_PP_SEQ_SIZE( \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err_for_args)), \
            3), \
        ( (BOOST_PP_EMPTY), (BOOST_PP_EMPTY), \
        (1, CONTRACT_ERROR_missing_function_argument_type_or_name_for_copyable_type)) /* but only these given BOOST_PP_STRINGIZE(BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err_for_args)), 1)) "given as" BOOST_PP_STRINGIZE(BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err_for_args))) */ \
        BOOST_PP_TUPLE_EAT(1) \
    , /* else */ \
        CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE_ARG_OP_ \
    )(seq_sign_err_for_args) /* end if */

// Arguments Loop //

#define CONTRACT_AUX_PP_SIGN_PARSE_ARGS_LOOP_PRED_( \
        d, seq_sign_err_for_args) \
    /* size > 1, skip trailing (PP_EMPTY) (to avoid empty seq) */ \
    BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3, 0, \
            seq_sign_err_for_args)), 1)

#define CONTRACT_AUX_PP_SIGN_PARSE_ARGS_COPYABLE_LOOP_OP_( \
        d, seq_sign_err_for_args) \
    BOOST_PP_IF(CONTRACT_AUX_PP_KEYWORD_IS_COPYABLE( \
            BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_ELEM(3, 0, \
            seq_sign_err_for_args))), \
        CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE_ARG_ \
    , /* else */ \
        CONTRACT_AUX_PP_SIGN_PARSE_NONCOPYABLE_ARG_ \
    )(seq_sign_err_for_args) /* end if */

#define CONTRACT_AUX_PP_SIGN_PARSE_ARGS_NONCOPYABLE_LOOP_OP_( \
        d, seq_sign_err_for_args) \
    BOOST_PP_IF(CONTRACT_AUX_PP_KEYWORD_IS_COPYABLE( \
            BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_ELEM(3, 0, \
            seq_sign_err_for_args))), \
        ( (BOOST_PP_EMPTY), (BOOST_PP_EMPTY), \
        (1, CONTRACT_ERROR_argument_cannot_be_tagged_copyable_in_this_context)) \
        BOOST_PP_TUPLE_EAT(1) \
    , /* else */ \
        CONTRACT_AUX_PP_SIGN_PARSE_NONCOPYABLE_ARG_ \
    )(seq_sign_err_for_args) /* end if */

// Helpers //

#define CONTRACT_AUX_PP_SIGN_PARSE_ARGS_RETURN_(seq_sign_err, \
        seq_sign_err_for_args, max_args) \
    BOOST_PP_IF(BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_TUPLE_ELEM(3, 2, \
            seq_sign_err_for_args)), /* error */ \
        CONTRACT_AUX_PP_SIGN_PARSE_RETURN_ERR(seq_sign_err, \
                BOOST_PP_SEQ_TAIL( \
                        BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err)), \
                (BOOST_PP_EMPTY) /* empty seq elem on error */, \
                BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_TUPLE_ELEM(3, 2, \
                        seq_sign_err_for_args))) \
    , BOOST_PP_IF(BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE( \
            BOOST_PP_TUPLE_ELEM(3, 1, seq_sign_err_for_args)), \
            max_args), \
        CONTRACT_AUX_PP_SIGN_PARSE_RETURN_ERR(seq_sign_err, \
                BOOST_PP_SEQ_TAIL( \
                        BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err)), \
                /* args seq that contains too many elems (error) */ \
                ( BOOST_PP_TUPLE_ELEM(3, 1, \
                seq_sign_err_for_args) ), \
                (1, CONTRACT_ERRPR_too_many_function_arguments)) \
    , /* else (no error) */ \
        CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK(seq_sign_err, \
                BOOST_PP_SEQ_TAIL( \
                        BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err)), \
                ( BOOST_PP_TUPLE_ELEM(3, 1, \
                seq_sign_err_for_args) ) \
        ) \
    )) /* end if */

// Parse some (one or more) arguments.
#define CONTRACT_AUX_PP_SIGN_PARSE_ARGS_SOME_( \
        seq_sign_err, max_args, allow_copyable) \
    CONTRACT_AUX_PP_SIGN_PARSE_ARGS_RETURN_(seq_sign_err, \
        BOOST_PP_WHILE(CONTRACT_AUX_PP_SIGN_PARSE_ARGS_LOOP_PRED_, \
            BOOST_PP_IF(allow_copyable, \
                CONTRACT_AUX_PP_SIGN_PARSE_ARGS_COPYABLE_LOOP_OP_ \
            , /* else */ \
                CONTRACT_AUX_PP_SIGN_PARSE_ARGS_NONCOPYABLE_LOOP_OP_ \
            ), /* endif */ \
                /* init remaining arg sign */ \
                ( BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_ELEM(3, 0, \
                        seq_sign_err)) (BOOST_PP_EMPTY) \
                , BOOST_PP_EMPTY() /* init parsed arg attrs seq */ \
                , (0, "") /* init no error */ ) \
        ) /* end while */ \
    , max_args)

// Parse no (none) arguments.
#define CONTRACT_AUX_PP_SIGN_PARSE_ARGS_NONE_( \
        seq_sign_err, max_args, allow_copyable) \
    CONTRACT_AUX_PP_SIGN_PARSE_RETURN_OK(seq_sign_err, \
            BOOST_PP_SEQ_TAIL( \
                    BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err)), \
            /* all () needed, this is a 1-seq of seq of 3-typle */ \
            ( ( (BOOST_PP_EMPTY, BOOST_PP_EMPTY, BOOST_PP_EMPTY) ) ) \
    )

// Handle "(f)( (void) )" as no arguments. This syntax to specify no 
// arguments is compliant with C++ standard and works on all 
// compilers.
#define CONTRACT_AUX_PP_SIGN_PARSE_ARGS_HANDLE_VOID_( \
        seq_sign_err, max_args, allow_copyable) \
    BOOST_PP_IF(CONTRACT_AUX_PP_KEYWORD_IS_VOID( \
            BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_HEAD( \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err)))), \
        CONTRACT_AUX_PP_SIGN_PARSE_ARGS_NONE_ \
    , /* else */ \
        CONTRACT_AUX_PP_SIGN_PARSE_ARGS_SOME_ \
    )(seq_sign_err, max_args, allow_copyable)

// Handle "(f)( )" as no arguments. This syntax to specify no 
// arguments is NOT compliant with C++ standard and only with C99 
// standard (because it requires preprocessor to allow for empty 
// sequences "()" and therefore for empty macro parameters).
// This library supports this syntax on compilers that accept empty 
// sequences but "(f)( (void) )" is best used to ensure portability.
// You can disable support for this syntax "(f)( )" simply making
// PP_SIGN_PARSE_ARGS_ call PP_SIGN_PARSE_ARGS_HANDLE_VOID_
// directly skipping the call to this macro.
#define CONTRACT_AUX_PP_SIGN_PARSE_ARGS_HANDLE_EMPTY_( \
        seq_sign_err, max_n_copyable) \
    BOOST_PP_IF(BOOST_PP_NOT(BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_HEAD( \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err)))), \
        CONTRACT_AUX_PP_SIGN_PARSE_ARGS_NONE_ \
    , /* else */ \
        CONTRACT_AUX_PP_SIGN_PARSE_ARGS_HANDLE_VOID_ \
    )( \
        seq_sign_err \
        , BOOST_PP_TUPLE_ELEM(2, 0, max_n_copyable) /* max_args */ \
        , BOOST_PP_TUPLE_ELEM(2, 1, max_n_copyable) /* allow cop. */ \
    )

#define CONTRACT_AUX_PP_SIGN_PARSE_ARGS_NO_( \
        seq_sign_err, max_n_copyable) \
    CONTRACT_AUX_PP_SIGN_PARSE_RETURN_ERR(seq_sign_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, seq_sign_err), \
            (/* empty seq elem in case of error */), \
            CONTRACT_ERROR_missing_function_arguments)

// API //

// Void and non-void args (void args are f(void)).
// To be standard compliant (f)() cannot be used because "()" is not
// legal. (f)( (void) ) should be used instead. However, this library
// also handels (f)() for these compilers (C99, etc) that support
// passing "()" macro params.
#define CONTRACT_AUX_PP_SIGN_PARSE_ARGS_(allow_copyable, max_args, \
        seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_APPLY( \
            CONTRACT_AUX_PP_SIGN_PARSE_ARGS_HANDLE_EMPTY_, \
            CONTRACT_AUX_PP_SIGN_PARSE_ARGS_NO_, \
            seq_sign_err, (max_args, allow_copyable) )

// Parse all arguments (could be empty, 1, 2, etc) allowing copyable.
#define CONTRACT_AUX_PP_SIGN_PARSE_COPYABLE_ARGS(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_ARGS_( \
            1, /* allow copyable (it's empty anyway...) */ \
            BOOST_PP_LIMIT_MAG, /* infinity (all args) */ \
            seq_sign_err)

// Parse all arguments (could be empty, 1, 2, etc) none copyable.
#define CONTRACT_AUX_PP_SIGN_PARSE_NONCOPYABLE_ARGS(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_ARGS_( \
            0, /* copyable not allowed (it's empty anyway...) */ \
            BOOST_PP_LIMIT_MAG, /* infinity (all args) */ \
            seq_sign_err)

// Parse empty argumnets (must be f(void)).
#define CONTRACT_AUX_PP_SIGN_PARSE_NO_ARGS(seq_sign_err) \
    CONTRACT_AUX_PP_SIGN_PARSE_ARGS_( \
            1, /* allow copyable (it's empty anyway...) */ \
            0, /* no arg, must be (f)( (void) ) or (f)( ) */ \
            seq_sign_err)

#endif // #include guard

