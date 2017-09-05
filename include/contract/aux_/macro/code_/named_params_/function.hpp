
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_HPP_
#define CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_HPP_

#include <contract/aux_/macro/code_/named_params_/boost_.hpp>
#include <boost/parameter.hpp>

// PRIVATE //
            
#define CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_TPARAM_NAME_ENUM_( \
        r, unused, i, p) \
    BOOST_PP_COMMA_IF(i) \
    /* here (but only here) we must use Boost.Parameter convention that */ \
    /* postfix ..._type (even if that would generate a reserved symbol */ \
    /* for a param name ending with _) */ \
    BOOST_PP_CAT(CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p), _type)

#define CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_PARAM_NAME_ENUM_( \
        r, unused, i, p) \
    BOOST_PP_COMMA_IF(i) \
    CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)

#define CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_DEF_( \
        id, tpl, k, f, named_and_deduced_params) \
    { \
        return CONTRACT_AUX_CODE_NAMED_PARAMS_CONTRACTED_FUNC(k, f)< \
            BOOST_PP_LIST_FOR_EACH_I( \
                    CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_TPARAM_NAME_ENUM_, \
                    ~, named_and_deduced_params) \
        >( \
            BOOST_PP_LIST_FOR_EACH_I( \
                    CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_PARAM_NAME_ENUM_, \
                    ~, named_and_deduced_params) \
        ); \
    }

#define CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_ELEM_(r, unused, elem) \
    elem
                    
#define CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_(id, tpl, k, f, \
        named_required_boost_params, named_optional_boost_params, \
        deduced_required_boost_params, deduced_optional_boost_params) \
    BOOST_PP_IIF(BOOST_PP_COMPL(CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f)), \
        BOOST_PARAMETER_FUNCTION \
    , BOOST_PP_IIF(BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_CONST(f))), \
        BOOST_PARAMETER_CONST_MEMBER_FUNCTION \
    , \
        BOOST_PARAMETER_MEMBER_FUNCTION \
    ))( \
        ( /* paren wrap result type commas in Boost.Parameter */ \
            /* this should always have result type but still checking size */ \
            CONTRACT_AUX_CODE_RESULT_TYPE(f, 1 /* allows empty result type */) \
        ), \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_STATIC(f) \
            /* `func`, `operator==`, etc */ \
            CONTRACT_AUX_CODE_NAME(CONTRACT_DETAIL_PP_FUNC_TRAITS_OPERATOR(f), \
                    CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(f)) \
        , \
        BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
                CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE( \
                CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))), \
            CONTRACT_AUX_CONFIG_NAMED_PARAMETER_TAG_NAMESPACE_DEFAULT \
            BOOST_PP_TUPLE_EAT(1) \
        , \
            CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE \
        )(CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f)) \
        , \
        /* (induced) named params `(required ...) (optinal ...)` */ \
        BOOST_PP_EXPR_IIF(BOOST_PP_LIST_IS_CONS(named_required_boost_params), \
            (required \
                BOOST_PP_LIST_FOR_EACH( \
                        CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_ELEM_, \
                        ~, named_required_boost_params) \
            ) \
        ) \
        BOOST_PP_EXPR_IIF(BOOST_PP_LIST_IS_CONS(named_optional_boost_params), \
            (optional \
                BOOST_PP_LIST_FOR_EACH( \
                        CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_ELEM_, \
                        ~, named_optional_boost_params) \
            ) \
        ) \
        /* deduced named params `(deduced (required ...) (optional ...) )` */ \
        BOOST_PP_LPAREN_IF(BOOST_PP_LIST_IS_CONS(BOOST_PP_LIST_APPEND( \
                deduced_required_boost_params, \
                deduced_optional_boost_params))) \
        BOOST_PP_EXPR_IIF(BOOST_PP_LIST_IS_CONS(BOOST_PP_LIST_APPEND( \
                deduced_required_boost_params, \
                deduced_optional_boost_params)), \
            deduced \
        ) \
            BOOST_PP_EXPR_IIF(BOOST_PP_LIST_IS_CONS( \
                    deduced_required_boost_params), \
                (required \
                    BOOST_PP_LIST_FOR_EACH( \
                            CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_ELEM_, \
                            ~, deduced_required_boost_params) \
                ) \
            ) \
            BOOST_PP_EXPR_IIF(BOOST_PP_LIST_IS_CONS( \
                    deduced_optional_boost_params), \
                (optional \
                    BOOST_PP_LIST_FOR_EACH( \
                            CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_ELEM_, \
                            ~, deduced_optional_boost_params) \
                ) \
            ) \
        BOOST_PP_RPAREN_IF(BOOST_PP_LIST_IS_CONS(BOOST_PP_LIST_APPEND( \
                deduced_required_boost_params, \
                deduced_optional_boost_params))) \
    ) \
    CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_DEF_(id, tpl, k, f, \
            /* these are all named-and-deduced params in their original */ \
            /* param traits format (while the other ..._boost_params in */ \
            /* this function are in Boost.Parameter format) */ \
            BOOST_PP_LIST_APPEND( \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED( \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f)), \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_DEDUCED( \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))))

#define CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_TUPLE_(id, tpl, k, f, \
        namedreq_namedopt, deducedreq_deducedopt) \
    CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_(id, tpl, k, f, \
            BOOST_PP_TUPLE_ELEM(2, 0, namedreq_namedopt), \
            BOOST_PP_TUPLE_ELEM(2, 1, namedreq_namedopt), \
            BOOST_PP_TUPLE_ELEM(2, 0, deducedreq_deducedopt), \
            BOOST_PP_TUPLE_ELEM(2, 1, deducedreq_deducedopt))

// PUBLIC //

#define CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION(id, tpl, k, f) \
    CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION_TUPLE_(id, tpl, k, f, \
            CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_REQOPT( \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED( \
                    CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))), \
            CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_REQOPT( \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_DEDUCED( \
                    CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))))

#endif // #include guard

