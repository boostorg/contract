/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_PP_FUN_PARSE_ARGS_HPP_
#define DBC_PP_FUN_PARSE_ARGS_HPP_

#include "util/required.hpp"
#include <boost/preprocessor.hpp>

#define DBC_PP_FUN_PARSE_ARGS_INFINITY_ BOOST_PP_LIMIT_MAG

// [LC] The arg traits is represented as 1 sequence element containing a
// sequence of 3-tuples (this requires a lot of parenthesis...):
//  /* 1 seq elem */( /*seq inside the 1 seq*/( /*tuple*/( arg-copyalbe 
//  BOOST_PP_EMPTY, arg-type BOOST_PP_EMPTY, arg-name BOOST_PP_EMPTY)
//  ( (c, t, n) )  ( (c, t, n) )  ... 
//  ( (BOOST_PP_EMPTY, BOOST_PP_EMPTY, BOOST_PP_EMPTY) ) /*trailing typle*/
//  )/*seq inside 1 seq*/ )/*1 seq elem*/
// The trailing 3-tuple with all BOOST_PP_EMPTY is used to handle no-arguments
// (or "void-arguments" as in "(f)( (void) )" ). Because the arg-name is used
// to identify void-arguments, the arg-name of all arguments must end with
// BOOST_PP_EMPTY also. (This is very difficult to follow... _maybe_ PP_ARRAY
// could be used to simply this?? array size 0 means no arguments, size 1
// there is one array element that is the 3-tuple, etc??)

// Non-Copyable Arg //

#define DBC_PP_FUN_PARSE_NONCOPYABLE_ARG_OP_(sign_traits_err_for_args) \
    /* got here only is args seq size >= 2 */ \
    BOOST_PP_IF(BOOST_PP_IS_EMPTY(BOOST_PP_SEQ_ELEM(0, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args))), \
        ( (BOOST_PP_EMPTY), (BOOST_PP_EMPTY), (1, DBC_ERROR_given_empty_function_argument_type_ /* in BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args)) */) ) \
    , BOOST_PP_IF(BOOST_PP_IS_EMPTY(BOOST_PP_SEQ_ELEM(1, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args))), \
        ( (BOOST_PP_EMPTY), (DBC_PP_EMPTY), (1, DBC_ERROR_given_empty_function_argument_name_ /* in BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args)) */) ) \
    , /* else */ \
        (   /* remove first 2 (type)(name) and continue */ \
            BOOST_PP_SEQ_REST_N(2, BOOST_PP_TUPLE_ELEM(3, 0, \
                    sign_traits_err_for_args)) \
        ,   BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err_for_args) /*seq concat*/\
            ( BOOST_PP_SEQ_TO_TUPLE( \
                ( BOOST_PP_EMPTY ) /* ',' */ \
                ( BOOST_PP_SEQ_ELEM(0, BOOST_PP_TUPLE_ELEM(3, 0, /* type */ \
                        sign_traits_err_for_args)) BOOST_PP_EMPTY ) \
                ( BOOST_PP_SEQ_ELEM(1, BOOST_PP_TUPLE_ELEM(3, 0, /* name */ \
                        sign_traits_err_for_args)) BOOST_PP_EMPTY ) \
            ) /*tuple (,type,name)*/ ) /*seq ( (,type,name) )*/ \
        ,   (0, "") /* no error */ ) \
    )) /* end if */

#define DBC_PP_FUN_PARSE_NONCOPYABLE_ARG_(sign_traits_err_for_args) \
    BOOST_PP_IF(BOOST_PP_LESS(BOOST_PP_SEQ_SIZE( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args)), 2), \
        ( (BOOST_PP_EMPTY), (BOOST_PP_EMPTY), (1, DBC_ERROR_missing_function_argument_type_or_name_ /* but only these given BOOST_PP_STRINGIZE(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args))) "given as" BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args))*/) ) \
        BOOST_PP_TUPLE_EAT(1) \
    , /* else */ \
        DBC_PP_FUN_PARSE_NONCOPYABLE_ARG_OP_ \
    )(sign_traits_err_for_args) /* end if */

// Copyable Arg //

#define DBC_PP_FUN_PARSE_COPYABLE_ARG_OP_(sign_traits_err_for_args) \
    /* got here only is args seq size >= 3 (elem 0 is (copyable) tag) */ \
    /* SEQ_TAIL used below to hide copyable tag from use error msg */ \
    BOOST_PP_IF(BOOST_PP_IS_EMPTY(BOOST_PP_SEQ_ELEM(1, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args))), \
        ( (BOOST_PP_EMPTY), (BOOST_PP_EMPTY), (1, DBC_ERROR_given_empty_funtion_argument_type_ /* in BOOST_PP_STRINGIZE(BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args)))*/) ) \
    , BOOST_PP_IF(BOOST_PP_IS_EMPTY(BOOST_PP_SEQ_ELEM(2, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args))), \
        ( (BOOST_PP_EMPTY), (BOOST_PP_EMPTY), (1, DBC_ERROR_given_empty_funtion_argument_name_ /* in BOOST_PP_STRINGIZE(BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args)))*/) ) \
    , /* else */ \
        (   /* remove first 3 (copyable)(type)(name) and continue */ \
            BOOST_PP_SEQ_REST_N(3, BOOST_PP_TUPLE_ELEM(3, 0, \
                    sign_traits_err_for_args)) \
        ,   BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err_for_args) /*seq concat*/\
            ( BOOST_PP_SEQ_TO_TUPLE( \
                (dbc_copyable_ BOOST_PP_EMPTY) /* copyable */ \
                ( BOOST_PP_SEQ_ELEM(1, BOOST_PP_TUPLE_ELEM(3, 0, /* type */ \
                        sign_traits_err_for_args)) BOOST_PP_EMPTY ) \
                ( BOOST_PP_SEQ_ELEM(2, BOOST_PP_TUPLE_ELEM(3, 0, /* name */ \
                        sign_traits_err_for_args)) BOOST_PP_EMPTY ) \
        ) /*tuple (copyable,type,name)*/ ) /*seq ( (copyable,type,name) )*/ \
        ,   (0, "") /* no error */ ) \
    )) /* end if */

#define DBC_PP_FUN_PARSE_COPYABLE_ARG_(sign_traits_err_for_args) \
    BOOST_PP_IF(BOOST_PP_LESS(BOOST_PP_SEQ_SIZE( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args)), 3), \
        ( (BOOST_PP_EMPTY), (BOOST_PP_EMPTY), (1, DBC_ERROR_missing_function_argument_type_or_name_for_copyable_type_ /* but only these given BOOST_PP_STRINGIZE(BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args)), 1)) "given as" BOOST_PP_STRINGIZE(BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args)))*/) ) \
        BOOST_PP_TUPLE_EAT(1) \
    , /* else */ \
        DBC_PP_FUN_PARSE_COPYABLE_ARG_OP_ \
    )(sign_traits_err_for_args) /* end if */

// Loop //

#define DBC_PP_FUN_PARSE_ARGS_LOOP_PRED_(d, sign_traits_err_for_args) \
    /* Sise > 1 to skip trailing (BOOST_PP_EMPTY) (to avoid empty seq). */ \
    BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3, 0, \
            sign_traits_err_for_args)), 1)

#define DBC_PP_FUN_PARSE_ARGS_LOOP_OP_(d, sign_traits_err_for_args) \
    BOOST_PP_IF(DBC_PP_IS_COPYABLE_(BOOST_PP_SEQ_HEAD( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args))), \
        DBC_PP_FUN_PARSE_COPYABLE_ARG_ \
    , /* else */ \
        DBC_PP_FUN_PARSE_NONCOPYABLE_ARG_ \
    )(sign_traits_err_for_args) /* end if */

// API Helpers //

#define DBC_PP_FUN_PARSE_ARGS_RETURN_(sign_traits_err, \
        sign_traits_err_for_args, max_args) \
    BOOST_PP_IF(BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_TUPLE_ELEM(3, 2, \
            sign_traits_err_for_args)), /* error */ \
        DBC_PP_FUN_PARSE_RETURN_ERR_(sign_traits_err, \
                BOOST_PP_SEQ_TAIL( \
                        BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)), \
                (BOOST_PP_EMPTY) /* empty seq elem on error */, \
                BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_TUPLE_ELEM(3, 2, \
                        sign_traits_err_for_args))) \
    , BOOST_PP_IF(BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE( \
            BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err_for_args)), max_args), \
        DBC_PP_FUN_PARSE_RETURN_ERR_(sign_traits_err, \
                BOOST_PP_SEQ_TAIL( \
                        BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)), \
                /* append args seq that contains too many elems (error) */ \
                ( BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err_for_args) ), \
                (1, DBC_ERRPR_too_many_function_arguments)) \
    , /* else (no error) */ \
        DBC_PP_FUN_PARSE_RETURN_OK_(sign_traits_err, \
                BOOST_PP_SEQ_TAIL( \
                        BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)), \
                ( BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err_for_args) ) \
        ) \
    )) /* end if */

/** Parse some (one or more) arguments. */
#define DBC_PP_FUN_PARSE_ARGS_SOME_(sign_traits_err, max_args) \
    DBC_PP_FUN_PARSE_ARGS_RETURN_(sign_traits_err, \
        BOOST_PP_WHILE(DBC_PP_FUN_PARSE_ARGS_LOOP_PRED_, \
            DBC_PP_FUN_PARSE_ARGS_LOOP_OP_, /* init remaining arg sign */ \
                ( BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_ELEM(3, 0, \
                        sign_traits_err)) (BOOST_PP_EMPTY) \
                , BOOST_PP_EMPTY() /* init parsed arg attrs seq */ \
                , (0, "") /* init no error */ ) \
        ) /* end while */ \
    , max_args)

/** Parse no (none) arguments. */
#define DBC_PP_FUN_PARSE_ARGS_NONE_(sign_traits_err, max_args) \
    DBC_PP_FUN_PARSE_RETURN_OK_(sign_traits_err, \
            BOOST_PP_SEQ_TAIL( \
                    BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)), \
            /* all () needed, this is a 1-seq of seq of 3-typle... */ \
            ( ( (BOOST_PP_EMPTY, BOOST_PP_EMPTY, BOOST_PP_EMPTY) ) ) \
    )

/** Handle "(f)( (void) )" as no arguments. This syntax to specify no arguments
 * is compliant with C++ standard and work on all compilers. */
#define DBC_PP_FUN_PARSE_ARGS_HANDLE_VOID_(sign_traits_err, max_args) \
    BOOST_PP_IF(DBC_PP_IS_VOID_(BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_HEAD( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)))), \
        DBC_PP_FUN_PARSE_ARGS_NONE_ \
    , /* else */ \
        DBC_PP_FUN_PARSE_ARGS_SOME_ \
    )(sign_traits_err, max_args)

/** Handle "(f)( )" as no arguments. This syntax to specify no arguments is
 * NOT compliant with C++ standard but only with C99 standard (as it requires
 * preprocessor to allow for empty sequences "()" which are only supported by
 * C99) and it does not work on all compilers. This library supports this
 * syntax on compilers that accept empty sequences but "(f)( (void) )" is best
 * used to ensure portability. You can disable support for this syntax "(f)( )"
 * simply making DBC_PP_FUN_PARSE_ARGS_ call DBC_PP_FUN_PARSE_ARGS_HANDLE_VOID_
 * directly skipping the call to this macro. */
#define DBC_PP_FUN_PARSE_ARGS_HANDLE_EMPTY_(sign_traits_err, max_args) \
    BOOST_PP_IF(BOOST_PP_NOT(BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_HEAD( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)))), \
        DBC_PP_FUN_PARSE_ARGS_NONE_ \
    , /* else */ \
        DBC_PP_FUN_PARSE_ARGS_HANDLE_VOID_ \
    )(sign_traits_err, max_args)

#define DBC_PP_FUN_PARSE_ARGS_ERR_(sign_traits_err, max_args) \
    DBC_PP_FUN_PARSE_RETURN_ERR_(sign_traits_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err), \
            (/* empty seq elem in case of error */), \
            DBC_ERROR_missing_function_arguments_)

// API //

// Void and non-void args (void args are f(void)).
// [LC] To be standard compliant (f)() cannot be used because "()" is not
// legal. (f)( (void) ) should be used instead. However, this library also
// handels (f)() for these compiler that support passing "()" macro params.
#define DBC_PP_FUN_PARSE_ARGS_(max_args, sign_traits_err) \
    DBC_PP_FUN_PARSE_APPLY_(DBC_PP_FUN_PARSE_ARGS_HANDLE_EMPTY_, \
            DBC_PP_FUN_PARSE_ARGS_ERR_, sign_traits_err, max_args)

#endif // DBC_PP_FUN_PARSE_ARGS_HPP_

