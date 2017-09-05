
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_HPP_
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_HPP_

#include <boost/preprocessor/comparison/greater_equal.hpp>
#include <boost/parameter.hpp>

// PRIVATE //

// Arg template param.

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARG_( \
        unused0, n, unused1) /* unused so it can be used with ENUM, etc */ \
    CONTRACT_AUX_SYMBOL( (NamedTParamsArg)(n) )
    
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARG_DECL_ENUM_( \
        r, arity_minus_defaults, i, t) \
    BOOST_PP_COMMA_IF(i) \
    typename CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARG_(~, i, ~) \
    BOOST_PP_EXPR_IIF(BOOST_PP_GREATER_EQUAL(i, arity_minus_defaults), \
        = ::boost::parameter::void_ \
    )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARG_DECL_PAREN_( \
        z, unused, i, t) \
    ( typename CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARG_(~, i, ~) )

// Args template param.

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARGS_ \
    CONTRACT_AUX_SYMBOL( (NamedTParamsArgs) )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_PARAM_ENUM_( \
        r, tparams, i, t) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
            CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_DEFAULT(t)), \
        ::boost::parameter::optional< \
    , \
        ::boost::parameter::required< \
    ) \
        /* tag (possibly deduced) */ \
        BOOST_PP_EXPR_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT( \
                CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND(t)), \
            ::boost::parameter::deduced< \
        ) \
        CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TEMPLATE_TAG(tparams, t) \
        BOOST_PP_EXPR_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT( \
                CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND(t)), \
            > \
        ) \
        /* NOTE: type requirement (if there is any type requirement then it */ \
        /* must be a matching type requirement for a type template */ \
        /* parameter because no exact type requirement applies to a type */ \
        /* template parameter and only template parameters are supported so */ \
        /* no need to check if KIND ends in `requires` in this case) */ \
        BOOST_PP_COMMA_IF(BOOST_PP_ARRAY_SIZE( \
                CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_REQUIREMENT(t))) \
        BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
                CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_REQUIREMENT(t)), \
            BOOST_PP_ARRAY_ENUM \
        , \
            BOOST_PP_TUPLE_EAT(1) \
        )(CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_REQUIREMENT(t)) \
    >   

// Original template params.

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_COMMA_TPARAM_DECL_( \
        r, tparams, t) \
    , typename CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_NAME(t) = typename \
            ::boost::parameter::value_type< \
          CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARGS_ \
        , CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TEMPLATE_TAG(tparams, t) \
        BOOST_PP_COMMA_IF(BOOST_PP_ARRAY_SIZE( \
                CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_DEFAULT(t))) \
        BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
                CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_DEFAULT(t)), \
            BOOST_PP_ARRAY_ENUM \
        , \
            BOOST_PP_TUPLE_EAT(1) \
        )(CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_DEFAULT(t)) \
      >::type

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_COMMA_TPARAM_DECL_PAREN_(\
        r, unused, t) \
    ( typename CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_NAME(t) )
    
// Template declaration.

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_HAS_DEFAULT_( \
        d, unused, t) \
    BOOST_PP_BOOL(BOOST_PP_ARRAY_SIZE( \
            CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_DEFAULT(t)))

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_DEFAULT_COUNT_( \
        named_and_deduced_tparams) \
    BOOST_PP_LIST_SIZE(BOOST_PP_LIST_FILTER( \
            CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_HAS_DEFAULT_,\
            ~, named_and_deduced_tparams))

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_DECL_( \
        template01, tparams, named_and_deduced_tparams) \
    /* open template<...> (even if no tparams for specializations) */ \
    BOOST_PP_EXPR_IIF(template01, template< ) \
    /* Arg */ \
    BOOST_PP_LIST_FOR_EACH_I( \
            CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARG_DECL_ENUM_, \
            BOOST_PP_SUB(BOOST_PP_LIST_SIZE(named_and_deduced_tparams), \
                CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_DEFAULT_COUNT_( \
                        named_and_deduced_tparams)), \
            named_and_deduced_tparams) \
    /* Args */ \
    , typename CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARGS_ = \
            typename ::boost::parameter::parameters< \
        BOOST_PP_LIST_FOR_EACH_I( \
                CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_PARAM_ENUM_, \
                tparams, named_and_deduced_tparams) \
      >::bind< \
        BOOST_PP_ENUM(BOOST_PP_LIST_SIZE(named_and_deduced_tparams), \
                CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARG_, ~) \
      >::type \
    /* original template params */ \
    BOOST_PP_LIST_FOR_EACH( \
            CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_COMMA_TPARAM_DECL_, \
            tparams, named_and_deduced_tparams) \
    /* close template<...> */ \
    BOOST_PP_EXPR_IIF(template01, > )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_POSITIONAL_C_(c, \
        named_and_deduced_tparams) \
    CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_REPLACE( \
    c, /* new template params: without named/deduced syntax */ \
        template( \
            BOOST_PP_LIST_FOR_EACH_I( \
  CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARG_DECL_PAREN_, \
                    ~, named_and_deduced_tparams) \
            ( typename CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_ARGS_ ) \
            BOOST_PP_LIST_FOR_EACH( \
  CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_COMMA_TPARAM_DECL_PAREN_, \
                    ~, named_and_deduced_tparams) \
            ) \
    )

// PUBLIC //

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_DECL( \
        template01, tparams) \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_DECL_(template01, tparams, \
            BOOST_PP_LIST_APPEND( \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED(tparams), \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_DEDUCED(tparams)))

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_POSITIONAL_C(c) \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_POSITIONAL_C_(c, \
            BOOST_PP_LIST_APPEND( \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED( \
                        CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_PARAMS(c)), \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_DEDUCED( \
                        CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_PARAMS(c))))

#endif // #include guard

