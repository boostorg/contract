
#ifndef DBC_PP_FUN_PARSE_ARGS_HPP_
#define DBC_PP_FUN_PARSE_ARGS_HPP_

#include "util/required.hpp"
#include <boost/preprocessor.hpp>

#define DBC_PP_FUN_PARSE_ARGS_INFINITY_ BOOST_PP_LIMIT_MAG

// Non-Copyable Arg //

#define DBC_PP_FUN_PARSE_NONCOPYABLE_ARG_OP_(sign_traits_err_for_args) /**/ \
    /* got here only is argsign seq size >= 2 */ \
    BOOST_PP_IF(BOOST_PP_IS_EMPTY(BOOST_PP_SEQ_ELEM(0, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args))), \
        ( , , (1, DBC_ERROR_given_empty_function_argument_type_ /* in BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args)) */) ) \
    , BOOST_PP_IF(BOOST_PP_IS_EMPTY(BOOST_PP_SEQ_ELEM(1, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args))), \
        ( , , (1, DBC_ERROR_given_empty_function_argument_name_ /* in BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args)) */) ) \
    , /* else */ \
        (   /* remove first 2 (type)(name) and continue */ \
            BOOST_PP_SEQ_REST_N(2, BOOST_PP_TUPLE_ELEM(3, 0, \
                    sign_traits_err_for_args)) \
        ,   BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err_for_args) /*seq concat*/\
            ( BOOST_PP_SEQ_TO_TUPLE( /* return (, type, name) */ \
                (/* empty seq elem for non-copyable */) \
                BOOST_PP_SEQ_SUBSEQ(BOOST_PP_TUPLE_ELEM(3, 0, \
                        sign_traits_err_for_args), 0, 2)) ) /* (type)(name) */\
        ,   (0, "") /* no error */ ) \
    )) /* end if */ \
    /**/

#define DBC_PP_FUN_PARSE_NONCOPYABLE_ARG_(sign_traits_err_for_args) /**/ \
    BOOST_PP_IF(BOOST_PP_LESS(BOOST_PP_SEQ_SIZE( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args)), 2), \
        ( , , (1, DBC_ERROR_missing_function_argument_type_or_name_ /* but only these given BOOST_PP_STRINGIZE(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args))) "given as" BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args))*/) ) \
        BOOST_PP_TUPLE_EAT(1) \
    , /* else */ \
        DBC_PP_FUN_PARSE_NONCOPYABLE_ARG_OP_ \
    )(sign_traits_err_for_args) /* end if */

// Copyable Arg //

#define DBC_PP_FUN_PARSE_COPYABLE_ARG_OP_(sign_traits_err_for_args) /**/ \
    /* got here only is argsign seq size >= 3 (elem 0 is (dbc_copyable_) */ \
    /* SEQ_TAIL used below to hide dbc_copyable_ from use error msg */ \
    BOOST_PP_IF(BOOST_PP_IS_EMPTY(BOOST_PP_SEQ_ELEM(1, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args))), \
        ( , , (1, DBC_ERROR_given_empty_funtion_argument_type_ /* in BOOST_PP_STRINGIZE(BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args)))*/) ) \
    , BOOST_PP_IF(BOOST_PP_IS_EMPTY(BOOST_PP_SEQ_ELEM(2, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args))), \
        ( , , (1, DBC_ERROR_given_empty_funtion_argument_name_ /* in BOOST_PP_STRINGIZE(BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args)))*/) ) \
    , /* else */ \
        (   /* remove first 3 (copyable)(type)(name) and continue */ \
            BOOST_PP_SEQ_REST_N(3, BOOST_PP_TUPLE_ELEM(3, 0, \
                    sign_traits_err_for_args)) \
        ,   BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err_for_args) /*seq concat*/ \
            ( BOOST_PP_SEQ_TO_TUPLE( /* return (copyable, type, name) */ \
                (dbc_copyable_) /* copyable */ \
                BOOST_PP_SEQ_SUBSEQ(BOOST_PP_TUPLE_ELEM(3, 0, \
                        sign_traits_err_for_args), 1, 2)) ) /* (type)(name) */ \
        ,   (0, "") /* no error */ ) \
    )) /* end if */ \
    /**/

#define DBC_PP_FUN_PARSE_COPYABLE_ARG_(sign_traits_err_for_args) /**/ \
    BOOST_PP_IF(BOOST_PP_LESS(BOOST_PP_SEQ_SIZE( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args)), 3), \
        ( , , (1, DBC_ERROR_missing_function_argument_type_or_name_for_copyable_type_ /* but only these given BOOST_PP_STRINGIZE(BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args)), 1)) "given as" BOOST_PP_STRINGIZE(BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args)))*/) ) \
        BOOST_PP_TUPLE_EAT(1) \
    , /* else */ \
        DBC_PP_FUN_PARSE_COPYABLE_ARG_OP_ \
    )(sign_traits_err_for_args) /* end if */

// Loop //

#define DBC_PP_FUN_PARSE_ARGS_LOOP_PRED_(d, sign_traits_err_for_args) \
    BOOST_PP_SEQ_SIZE(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args))

#define DBC_PP_FUN_PARSE_ARGS_LOOP_OP_(d, sign_traits_err_for_args) \
    BOOST_PP_IF(DBC_PP_IS_COPYABLE_(BOOST_PP_SEQ_HEAD( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err_for_args))), \
        DBC_PP_FUN_PARSE_COPYABLE_ARG_ \
    , /* else */ \
        DBC_PP_FUN_PARSE_NONCOPYABLE_ARG_ \
    )(sign_traits_err_for_args) /* end if */

// Error Handling //

#define DBC_PP_FUN_PARSE_ARGS_RETURN_(sign_traits_err, \
        sign_traits_err_for_args, max_args) \
    BOOST_PP_IF(BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_TUPLE_ELEM(3, 2, \
            sign_traits_err_for_args)), /* error */ \
        DBC_PP_FUN_PARSE_RETURN_ERR_(sign_traits_err, \
                BOOST_PP_SEQ_TAIL( \
                        BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)), \
                (/* empty seq elem on error */), \
                BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_TUPLE_ELEM(3, 2, \
                        sign_traits_err_for_args))) \
    , BOOST_PP_IF(BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE( \
            BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err_for_args)), max_args), \
        DBC_PP_FUN_PARSE_RETURN_ERR_(sign_traits_err, \
                BOOST_PP_SEQ_TAIL( \
                        BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)), \
                /* append args seq that contains too many elems */ \
                ( BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err_for_args) ), \
                (1, DBC_ERRPR_too_many_function_arguments)) \
    , /* else (no error) */ \
        DBC_PP_FUN_PARSE_RETURN_OK_(sign_traits_err, \
                BOOST_PP_SEQ_TAIL( \
                        BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err)), \
                ( BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err_for_args) ) ) \
    )) /* end if */
                
#define DBC_PP_FUN_PARSE_ARGS_OP_(sign_traits_err, max_args) \
    DBC_PP_FUN_PARSE_ARGS_RETURN_(sign_traits_err, \
        BOOST_PP_WHILE(DBC_PP_FUN_PARSE_ARGS_LOOP_PRED_, \
            DBC_PP_FUN_PARSE_ARGS_LOOP_OP_, /* init remaining arg sign */ \
                ( BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err))\
                , BOOST_PP_EMPTY() /* init parsed arg attrs seq */ \
                , (0, "") /* init no error */ ) \
        ) /* end while */ \
    , max_args)

#define DBC_PP_FUN_PARSE_ARGS_NO_(sign_traits_err, max_args) \
    DBC_PP_FUN_PARSE_RETURN_ERR_(sign_traits_err, \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_traits_err), \
            (/* empty seq elem in case of error */), \
            DBC_ERROR_missing_function_arguments_)

// API //

#define DBC_PP_FUN_PARSE_ARGS_(max_args, sign_traits_err) \
    DBC_PP_FUN_PARSE_APPLY_(DBC_PP_FUN_PARSE_ARGS_OP_, \
            DBC_PP_FUN_PARSE_ARGS_NO_, sign_traits_err, max_args)

#endif // DBC_PP_FUN_PARSE_ARGS_HPP_

