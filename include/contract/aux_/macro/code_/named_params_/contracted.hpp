
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_HPP_
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_HPP_

// PRIVATE //

// Contracted function traits.

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_DECL_TYPE_(p) \
    /* IMPORTANT: always by ref (also to support for in-out and out) */ \
    /* however never add const because const is automatically added */ \
    /* by Boost.Parameter overloads in order to distinguish in and out */ \
    BOOST_PP_EXPR_IIF( \
            CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_IS_OUT_OR_INOUT(p), \
        typename ::boost::add_reference< \
    ) \
        CONTRACT_AUX_PARAMETER_BOOST_TYPE( \
                CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)) \
    BOOST_PP_EXPR_IIF( \
            CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_IS_OUT_OR_INOUT(p), \
        >::type \
    )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_TPARAM_DECL_PAREN_( \
        r, unused, p) \
    ( typename CONTRACT_AUX_PARAMETER_BOOST_TYPE( \
            CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)) )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_PAREN_(r, unused, elem) \
    ( elem )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_PARAM_DECL_PAREN_( \
        r, unused, p) \
    ( ( CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_DECL_TYPE_(p) ) \
      CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p) )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_CONCEPTS_REPLACE_(f, \
        concepts_sign) \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS( \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAM_CONCEPTS(f)), \
        CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_REPLACE \
    , \
        f BOOST_PP_TUPLE_EAT(2) \
    )(f, concepts_sign)
    
// Generate contracted func signature (which only uses positional params).
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_F_( \
        k, f, named_and_deduced_params) \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS_REPLACE( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME_REPLACE( \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_CONCEPTS_REPLACE_( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_REPLACE( \
    f, /* new template params: Boost.Parameter's <param-name>_type */ \
        template( \
            BOOST_PP_LIST_FOR_EACH( \
                CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_TPARAM_DECL_PAREN_, \
                ~, named_and_deduced_params) \
        ) \
    ), /* new concepts: parameter concepts (if any specified by user) */ \
        requires( \
            BOOST_PP_LIST_FOR_EACH( \
                    CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_PAREN_, \
                    ~, CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAM_CONCEPTS(f)) \
        ) \
    ), /* new name (contracted function) */ \
        ( CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_FUNC(k, f) ) \
    ), /* new func params: (<param-name>_type) <param-name> */ \
        ( \
            BOOST_PP_LIST_FOR_EACH( \
                CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_PARAM_DECL_PAREN_, \
                ~, named_and_deduced_params) \
        ) \
    )

// Contracted body function declaration.

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_BODY_TPARAM_DECL_ENUM_( \
        r, unused, i, p) \
    BOOST_PP_COMMA_IF(i) \
    typename CONTRACT_AUX_PARAMETER_BOOST_TYPE( \
            CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p))

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_BODY_PARAM_DECL_ENUM_( \
        r, unused, i, p) \
    BOOST_PP_COMMA_IF(i) \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_DECL_TYPE_(p) \
    CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_BODY_DECL_( \
        id, tpl, k, f, body_func, named_and_deduced_params) \
    template< \
        BOOST_PP_LIST_FOR_EACH_I( \
            CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_BODY_TPARAM_DECL_ENUM_, \
            ~, named_and_deduced_params) \
    > \
    CONTRACT_AUX_CODE_RESULT_TYPE(f, 1) /* allows empty result type */ \
    /* keep original body func name (not contractedXnameXbody) so user can */ \
    /* separate definition with usual BODY macro */ \
    body_func ( \
        BOOST_PP_LIST_FOR_EACH_I( \
            CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_BODY_PARAM_DECL_ENUM_, \
            ~, named_and_deduced_params) \
    ) \
    /* POLICY: Exception spec only apply to exceptions thrown by the body */ \
    /* and not to exceptions thrown by contract handlers (if they are */ \
    /* redefined to throw) or by this library implementation code */ \
    CONTRACT_AUX_CODE_EXCEPTION_SPEC(id, tpl, k, f)

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_FUNC_(k, f) \
    CONTRACT_AUX_SYMBOL( (contracted)(CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(f)) )

// PUBLIC //

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_FUNC(k, f) \
    /* constructor, non-static member, static member with enabled */ \
    /* contracts (destructors have no param so no named params) */ \
    BOOST_PP_IIF( \
            BOOST_PP_BITAND( \
                  CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f) \
                , BOOST_PP_BITOR( \
                      CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
                    , BOOST_PP_BITOR( \
                          CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
                        , CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
                    ) \
                ) \
            ), \
        CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_FUNC_ \
    , BOOST_PP_IIF( /* free function with enabled contracts */ \
            BOOST_PP_BITAND( \
                  CONTRACT_AUX_PP_FUNC_KIND_IS_FREE_FUNCTION(k, f) \
                , BOOST_PP_BITOR( \
                      CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
                    , CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
                ) \
            ), \
        CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_FUNC_ \
    , \
        /* use body name here so contracted function impl by body func */ \
        /* when no contracts but still BODY can be used to defer func def */ \
        CONTRACT_AUX_FUNCTION_BODY_FUNC \
    ))(k, f)
            
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_F(k, f) \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_F_(k, f, \
            BOOST_PP_LIST_APPEND( \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED( \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f)), \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_DEDUCED( \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))))

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_BODY_DECL( \
        id, tpl, k, f, body_func) \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_BODY_DECL_( \
            id, tpl, k, f, body_func, \
            BOOST_PP_LIST_APPEND( \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED( \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f)), \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_DEDUCED( \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))))

#endif // #include guard

