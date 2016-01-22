
#ifndef BOOST_CONTRACT_AUX_DECL_HPP_
#define BOOST_CONTRACT_AUX_DECL_HPP_

#include <boost/contract/core/config.hpp>
#include <boost/contract/aux_/tvariadic.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#if BOOST_CONTRACT_AUX_TVARIADIC
    #include <boost/preprocessor/repetition/repeat.hpp>
    #include <boost/preprocessor/tuple/elem.hpp>
#endif

/* PUBLIC */

#define BOOST_CONTRACT_AUX_DECL_OVERRIDING_PUBLIC_FUNCTION_Z(z, \
    arity, is_friend, has_result, \
    O, R, F, C, Args, \
    v, r, f, obj, args \
) \
    template< \
        class O \
        BOOST_PP_COMMA_IF(has_result) \
        BOOST_PP_EXPR_IIF(has_result, typename R) \
        , typename F \
        , class C \
        BOOST_CONTRACT_AUX_TVARIADIC_COMMA(arity) \
        BOOST_CONTRACT_AUX_TVARIADIC_TPARAMS_Z(z, arity, Args) \
    > \
    BOOST_PP_EXPR_IIF(is_friend, friend) \
    set_precondition_old_postcondition<BOOST_PP_EXPR_IIF(has_result, R)> \
    public_function( \
        virtual_* v \
        BOOST_PP_COMMA_IF(has_result) \
        BOOST_PP_EXPR_IIF(has_result, R& r) \
        , F f \
        , C* obj \
        BOOST_CONTRACT_AUX_TVARIADIC_COMMA(arity) \
        BOOST_CONTRACT_AUX_TVARIADIC_FPARAMS_Z(z, arity, Args, &, args) \
    )

#if BOOST_CONTRACT_AUX_TVARIADIC
    #define BOOST_CONTRACT_AUX_DECL_FRIEND_OVERRIDING_PUBLIC_FUNCTIONS_Z(z, \
        O, R, F, C, Args, \
        v, r, f, obj, args \
    ) \
        BOOST_CONTRACT_AUX_DECL_OVERRIDING_PUBLIC_FUNCTION_Z(z, \
            ~, /* is_friend = */ 1, /* has_result = */ 0, \
            O, R, F, C, Args, v, r, f, obj, args \
        ); \
        BOOST_CONTRACT_AUX_DECL_OVERRIDING_PUBLIC_FUNCTION_Z(z, \
            ~, /* is_friend = */ 1, /* has_result = */ 1, \
            O, R, F, C, Args, v, r, f, obj, args \
        );
#else
    #define BOOST_CONTRACT_AUX_DECL_FRIEND_OVERRIDING_PUBLIC_FUNCTIONS_Z(z, \
        O, R, F, C, Args, \
        v, r, f, obj, args \
    ) \
        BOOST_PP_REPEAT_ ## z( \
            BOOST_PP_INC(BOOST_CONTRACT_CONFIG_MAX_ARGS), \
            BOOST_CONTRACT_AUX_DECL_FRIEND_OVERRIDING_PUBLIC_FUNCTION_, \
            (/* has_result = */ 0, O, R, F, C, Args, v, r, f, obj, args) \
        ) \
        BOOST_PP_REPEAT_ ## z( \
            BOOST_PP_INC(BOOST_CONTRACT_CONFIG_MAX_ARGS), \
            BOOST_CONTRACT_AUX_DECL_FRIEND_OVERRIDING_PUBLIC_FUNCTION_, \
            (/* has_result = */ 1, O, R, F, C, Args, v, r, f, obj, args) \
        )
#endif

#define BOOST_CONTRACT_AUX_DECL_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_Z( \
        z, is_friend, O, R, F, C, Args) \
    template< \
        class O, typename R, typename F, class C \
        BOOST_CONTRACT_AUX_TVARIADIC_COMMA(BOOST_CONTRACT_CONFIG_MAX_ARGS) \
        BOOST_CONTRACT_AUX_TVARIADIC_TPARAMS_Z(z, \
                BOOST_CONTRACT_CONFIG_MAX_ARGS, Args) \
    > \
    BOOST_PP_IIF(is_friend, \
        friend class boost::contract::aux:: \
    , \
        class \
    ) \
    check_subcontracted_pre_post_inv
    
/* PRIVATE */

#if !BOOST_CONTRACT_AUX_TVARIADIC
    #define BOOST_CONTRACT_AUX_DECL_FRIEND_OVERRIDING_PUBLIC_FUNCTION_( \
            z, n, result_O_R_F_C_Args_v_r_f_obj_args) \
        BOOST_CONTRACT_AUX_DECL_OVERRIDING_PUBLIC_FUNCTION_Z(z, \
            /* arity = */ n, \
            /* is_friend = */ 1, \
            BOOST_PP_TUPLE_ELEM(11, 0, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 1, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 2, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 3, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 4, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 5, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 6, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 7, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 8, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 9, result_O_R_F_C_Args_v_r_f_obj_args), \
            BOOST_PP_TUPLE_ELEM(11, 10, result_O_R_F_C_Args_v_r_f_obj_args) \
        );
#endif

#endif // #include guard

