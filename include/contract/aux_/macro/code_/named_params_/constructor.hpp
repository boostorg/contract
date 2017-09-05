
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_HPP_
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_HPP_

#include <contract/aux_/macro/parameter.hpp>
#include <boost/parameter.hpp>

// WARNING: Unfortunately, this file must use internal implementation details
// (aux) of Boost.Parameter. This is done to work around Boost.Parameter
// limitations in supporting constructors that (1) only allow to specify a 
// single base class taking all named parameters at once in the member
// initializers, (2) it does not allow to specify the body (so making it not 
// possible to invoke the contracted function to implement contracts), and (3)
// force the use of default values in the base constructor implementation away
// from the actual constructor definition. All these issue are solved here
// even if at the cost of having to use a macro to access the named parameters
// within the member initializers (this is because of lack of delegating
// constructors so parameters must be defined as pointers so they can have
// null default values in the constructor declaration) but named parameters
// are accessed as usual in preconditions, postconditions, and body.

// PRIVATE //
        
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARGS_ \
    /* NOTE: no ID here because it needs to be used by CONSTRUCTOR_ARG */ \
    /* macro at different lines (this is OK because this is a func param */ \
    /* so it is unique to the func scope) */ \
    CONTRACT_AUX_SYMBOL( (named_params_args) )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_(name) \
    /* NOTE: no ID here because it needs to be used by CONSTRUCTOR_ARG */ \
    /* macro at different lines (this is OK because this is a func param */ \
    /* so it is unique to the func scope) */ \
    CONTRACT_AUX_SYMBOL( (named_params_arg)(name) )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_DEFAULT_(name) \
    /* NOTE: no ID here because it needs to be used by CONSTRUCTOR_ARG */ \
    /* macro at different lines (this is OK because this is a func param */ \
    /* so it is unique to the func scope) */ \
    CONTRACT_AUX_SYMBOL( (named_params_default)(name) )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAM_PRED_(p) \
    typename ::boost::parameter::aux::unwrap_predicate< \
        void CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TYPE_REQUIREMENT(p) \
    >::type

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAM_( \
        params, p, predicate01) \
    ::boost::parameter:: \
    BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
            CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT(p)), \
        optional \
    , \
        required \
    ) < \
        /* param tag (possibly deduced) */ \
        BOOST_PP_EXPR_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT( \
                CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(p)), \
            ::boost::parameter::deduced< \
        ) \
            CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TAG(params, p) \
        BOOST_PP_EXPR_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT( \
                CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(p)), \
            > \
        ) \
        /* param type predicate */ \
        BOOST_PP_COMMA_IF(predicate01) \
        BOOST_PP_IIF(predicate01, \
            CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAM_PRED_ \
        , \
            BOOST_PP_TUPLE_EAT(1) \
        )(p) \
    >

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAM_ENUM_( \
        r, params, i, p) \
    BOOST_PP_COMMA_IF(i) \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAM_(params, p, \
            1 /* with type predicate */)

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_TPARAM_( \
        unused0, n, unused1) /* unused so it can be used with ENUM, etc */ \
    CONTRACT_AUX_SYMBOL( (NamedParamsArg)(n) )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_QUALIFIED_TPARAM_( \
        unused, n, arg_types) /* unused so it can be used with ENUM, etc */ \
    BOOST_PP_EXPR_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_PP_SEQ_ELEM(n, arg_types)), \
        const \
    ) \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_TPARAM_(~, n, ~) \
    /* don't qualify with reference here */
    
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_PARAM_( \
        unused0, n, unused1) /* unused so it can be used with ENUM, etc */ \
    CONTRACT_AUX_SYMBOL( (named_params_arg)(n) )
    
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_TPARAM_DECL_( \
        z, n, default01) \
    typename CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_TPARAM_(~, n, ~) \
    BOOST_PP_EXPR_IIF(default01, = void)

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_PARAM_DECL_( \
        z, n, arg_types) \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_QUALIFIED_TPARAM_(~, n, \
            arg_types) \
    & /* always by ref (plus const for in-only params) */ \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_PARAM_(~, n, ~)

// Precondition: ARRAY_SIZE(DEFAULT(p)) > 0
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_DEFAULT_TYPE_(p) \
    /* NOTE: the default parameter type must be deduced because it is not */ \
    /* specified anywhere (the parameter type is generic and it is not */ \
    /* matched to the default value type by Boost.Parameter unless the */ \
    /* default value is actually needed so the parameter type cannot be */ \
    /* used because it would force matching between default value and */ \
    /* parameter type in cases where Boost.Parameter does not require it) */ \
    BOOST_TYPEOF(BOOST_PP_ARRAY_ENUM( \
            CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT(p)))

// Precondition: ARRAY_SIZE(DEFAULT(p)) > 0
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_DEFAULT_PARAM_(p) \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_DEFAULT_TYPE_(p) \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_DEFAULT_( \
            CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)) \
    = BOOST_PP_ARRAY_ENUM(CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT(p))

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_NODEFAULT_PARAM_(p) \
    ::contract::aux::named_params::no_default \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_DEFAULT_( \
            CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)) \
    = 0

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_COMMA_NAMED_PARAM_DECL_( \
        r, params, p) \
    /* NOTE: keywords and defaults are defined here so the CONSTRUCTOR_ARG */ \
    /* macro can access them with a fixed name (can't use the user-defined */ \
    /* ones because the tag namespace might not be default in which case */ \
    /* the CONSTRUCTOR_ARG macro won't know what the tag namespace is */ \
    /* plus the CONTRACT_ARG macro has no access to defaults with are */ \
    /* in the function declaration traits) */ \
    , ::boost::parameter::keyword< \
        CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TAG(params, p) \
      > const& \
      CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_( \
            CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)) \
      = ::boost::parameter::keyword< \
        CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TAG(params, p) \
      >::instance \
    , BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
            CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT(p)), \
        CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_DEFAULT_PARAM_ \
      , \
        CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_NODEFAULT_PARAM_ \
      )(p)

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_OPEN_ELEM_ENUM_( \
        r, params, i, p) \
    BOOST_PP_COMMA_IF(i) \
    ::boost::parameter::aux::item< \
          CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAM_(params, p, \
                0 /* no type predicate */) \
        , CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_TPARAM_(~, i, ~) \
    /* don't close `>` here (that's why this is called OPEN_ELEM)... */
  
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_CLOSE_ELEM_(z, n, unused) \
    > /* ... `item<` are closed here (so they are nested into each other) */

// Named parameter structs.
    
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAMS_TPL_(id) \
    CONTRACT_AUX_SYMBOL( (named_params_constructor_tpl)(id) ) \

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAMS_TYPE_(id) \
    CONTRACT_AUX_SYMBOL( (named_params_constructor)(id) )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAMS_BASE_( \
        f, named_and_deduced_params) \
    ::boost::parameter::parameters< \
        BOOST_PP_LIST_FOR_EACH_I( \
                CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAM_ENUM_, \
                CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f), \
                named_and_deduced_params) \
    >

// Define Boost.Parameter structs to deduce and match params.
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAMS_( \
        id, tpl, k, f, named_and_deduced_params) \
    template< \
        /* make this dummy template so its def can always use typename */ \
        typename CONTRACT_AUX_SYMBOL( (NamedParamsConstructorUnused)(id) ) \
    > \
    struct CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAMS_TPL_(id) \
        : CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAMS_BASE_( \
                f, named_and_deduced_params) \
    { \
        template< \
            BOOST_PP_ENUM(BOOST_PP_LIST_SIZE(named_and_deduced_params), \
  CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_TPARAM_DECL_,\
                    1 /* with default */) \
        > \
        struct arg_list { \
            typedef typename ::boost::mpl::first< \
                typename ::boost::parameter::aux::make_arg_list< \
                      BOOST_PP_LIST_FOR_EACH_I( \
  CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_OPEN_ELEM_ENUM_, \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f), \
                            named_and_deduced_params) \
                      BOOST_PP_REPEAT( \
                            BOOST_PP_LIST_SIZE(named_and_deduced_params), \
  CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_CLOSE_ELEM_, \
                            ~) \
                    /* if named params, at leas one param so alway , below */ \
                    , typename \
                      CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAMS_BASE_( \
                        f, named_and_deduced_params)::deduced_list \
                    , ::boost::parameter::aux::tag_keyword_arg \
                >::type \
            >::type type; \
        }; \
    }; \
    typedef CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAMS_TPL_(id)<int> \
            CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAMS_TYPE_(id);

// Constructor overloads (in the future to make this header shorter, some of
// this code could be moved into the boost_.hpp because it depends on macros
// from boost_.hpp).

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_TPARAM_DECL_PAREN_( \
        r, id_params_args, p) \
    /* NOTE: tparam type trait in pp-seq `(typename tparam)` used to pass */ \
    /* param type via a metafunction instead of tparam name (can't use */ \
    /* `class` instead of `typename` because it would remove typename */ \
    /* prefixing IDENTITY_TYPE, double typenames are not removed instead */ \
    ( typename \
        /* IDENTITY_TYPE wraps all tparam commas for metafunc below */ \
        typename BOOST_IDENTITY_TYPE(( \
            /* metafunc that finds param type in arg-list from its tag */ \
            typename ::contract::aux::named_params::arg_type< \
                /* argument list type */ \
                  typename \
                  CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAMS_TYPE_( \
                        BOOST_PP_TUPLE_ELEM(3, 0, id_params_args)):: \
                  template arg_list< \
                    BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE( \
                            BOOST_PP_TUPLE_ELEM(3, 2, id_params_args)), \
  CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_QUALIFIED_TPARAM_, \
                            BOOST_PP_TUPLE_ELEM(3, 2, id_params_args)) \
                  >::type \
                /* param tag type */ \
                , CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TAG( \
                        BOOST_PP_TUPLE_ELEM(3, 1, id_params_args), p) \
                /* param default value type (only if optional) */ \
                BOOST_PP_COMMA_IF(BOOST_PP_ARRAY_SIZE( \
                        CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT(p))) \
                BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
                        CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT(p)), \
                    CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_DEFAULT_TYPE_ \
                , \
                    BOOST_PP_TUPLE_EAT(1) \
                )(p) \
            >::type \
        )) \
    )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAM_DECL_PAREN_( \
        r, unused, p) \
    ( /* pp-seq parenthesis for func param name trait */ \
        int /* param type not used in ctor def expansion so just use int */ \
        /* use param value expr instead of just param name here (usually */ \
        /* param name carries its value but for named params this expr */ \
        /* carries the param value-- cannot use CONTRACT_CONSTRUCTOR_ARG */ \
        /* macro because it has extra wrapping parenthesis around the */ \
        /* expr that will confuse the pp-parser here) */ \
        CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG( \
                CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)) \
    )

// Generate constructor definition func traits (which uses ARG).
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_DEF_F_( \
        id, f, named_and_deduced_params, arg_types) \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS_REPLACE( \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_REPLACE( \
    f, \
        template( \
            BOOST_PP_LIST_FOR_EACH( \
                CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_TPARAM_DECL_PAREN_, \
                (id, CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f), arg_types), \
                named_and_deduced_params) \
        ) \
    ), /* new func params: (<param-name>_type) <param-name> */ \
        ( \
            BOOST_PP_LIST_FOR_EACH( \
                CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAM_DECL_PAREN_, \
                ~, named_and_deduced_params) \
        ) \
    )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_(r, z, id, tpl, k, f, \
        body_func, named_and_deduced_params, arg_types) \
    /* NOTE: always use typename here because this is a func template */ \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_ACCESS(f) \
    : /* construct is member so access never empty and `:` always present */ \
    template< \
        BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(arg_types), \
                CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_TPARAM_DECL_, \
                0 /* without default */) \
    > \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(f) ( \
        BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(arg_types), \
                CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_PARAM_DECL_, \
                arg_types) \
        /* no named params if no arguments so , always follows here */ \
        , typename ::boost::parameter::aux::match< \
              CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAMS_TYPE_(id) \
            , BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(arg_types), \
                    CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_TPARAM_, ~) \
          >::type /* no actual param name (just used to resolve ctor call */ \
          = CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAMS_TYPE_(id)( \
                /* default constructor */) \
        , ::contract::aux::named_params::args< \
            typename CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAMS_TYPE_( \
                    id)::template arg_list< \
                BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(arg_types), \
  CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_QUALIFIED_TPARAM_, \
                        arg_types) \
            >::type \
          > CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARGS_ = 0 \
        BOOST_PP_LIST_FOR_EACH( \
            CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_COMMA_NAMED_PARAM_DECL_,\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f), \
            named_and_deduced_params) \
    ) \
    CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_DEF_FORCE( \
          id \
        , 1 /* always in a template */ \
        , k \
        , CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_DEF_F_(id, f, \
                named_and_deduced_params, arg_types) \
        , body_func \
        , ( \
            BOOST_IDENTITY_TYPE(( \
                ::contract::aux::constructor_inits_eval< \
                      CONTRACT_AUX_CODE_CLASS_TYPE \
                    , ::contract::aux:: \
                            constructor_inits_eval_named_params_args_set \
                > \
            ))( \
                CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARGS_.set( \
                    CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAMS_TYPE_(id)\
                    (/* default constructor*/)( \
                        BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(arg_types), \
  CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_PARAM_, \
                                ~) \
                    ) \
                ) \
            ) \
          , \
            BOOST_PP_NIL \
          ) \
        , 1 /* always force body (even if no contracts) for named args */ \
    )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_TUPLE_(r, \
        z_arity_id_tpl_k_f_body_params_args, arg_types) \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_(r \
        , BOOST_PP_TUPLE_ELEM(9, 0, z_arity_id_tpl_k_f_body_params_args) \
        /* do not pass arity */ \
        , BOOST_PP_TUPLE_ELEM(9, 2, z_arity_id_tpl_k_f_body_params_args) \
        , BOOST_PP_TUPLE_ELEM(9, 3, z_arity_id_tpl_k_f_body_params_args) \
        , BOOST_PP_TUPLE_ELEM(9, 4, z_arity_id_tpl_k_f_body_params_args) \
        , BOOST_PP_TUPLE_ELEM(9, 5, z_arity_id_tpl_k_f_body_params_args) \
        , BOOST_PP_TUPLE_ELEM(9, 6, z_arity_id_tpl_k_f_body_params_args) \
        , BOOST_PP_TUPLE_ELEM(9, 7, z_arity_id_tpl_k_f_body_params_args) \
        /* do not pass args (i.e., arg_types_combinations) */ \
        , arg_types \
    )
            
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_TYPES_(r, arg_types) \
    /* wraps arg types within pp-seq parenthesis so to make */ \
    /* FOR_EACH_PRODUCT expand into another pp-seq */ \
    ( arg_types )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARITY_(z, arity, \
        id_tpl_k_f_body_params_args) \
    /* need outer FOR_EACH to pass data (because FOR_EACH_PRODUCT does not */ \
    /* relay any data) */ \
    BOOST_PP_SEQ_FOR_EACH( \
            CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_TUPLE_, \
            (z, arity, BOOST_PP_TUPLE_REM(7) id_tpl_k_f_body_params_args),\
            BOOST_PP_SEQ_FOR_EACH_PRODUCT( \
                    CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_TYPES_, \
                    BOOST_PP_SEQ_FIRST_N(arity, BOOST_PP_TUPLE_ELEM(7, 6, \
                            id_tpl_k_f_body_params_args))))

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAM_HAS_DEFAULT_( \
        d, unused, p) \
    BOOST_PP_BOOL(BOOST_PP_ARRAY_SIZE( \
            CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT(p)))

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_OVERLOADS_(id, tpl, k, f, \
        body_func, named_and_deduced_params, arg_types_combinations) \
    BOOST_PP_REPEAT_FROM_TO( \
            BOOST_PP_SUB(BOOST_PP_LIST_SIZE(named_and_deduced_params), \
                    /* count defaults (it could be 0) */ \
                    BOOST_PP_LIST_SIZE(BOOST_PP_LIST_FILTER( \
  CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAM_HAS_DEFAULT_, \
                            ~, named_and_deduced_params))), \
            /* INC to always include all params case in iterator */ \
            BOOST_PP_INC(BOOST_PP_LIST_SIZE(named_and_deduced_params)), \
            CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARITY_, \
            (id, tpl, k, f, body_func, named_and_deduced_params, \
                    arg_types_combinations))

// All combinations of constructor template parameters to handle the generic
// named parameters (there combine the const/no-const to handle in/out/in-out).

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_COMBINATIONS_ARG_( \
        r, unused, p) \
    ( ( /* tuple seq w/ special format used by Boost.Parameter combinations */ \
        /* Boost.Parameter uses [deduced_]required, [deduced_]optional here */ \
        BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
                CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT(p)), \
            BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT( \
                    CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(p)), \
                deduced_optional \
            , \
                optional \
            ) \
        , \
            BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT( \
                    CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(p)), \
                deduced_required \
            , \
                required \
            ) \
        ) \
    , \
        /* named qualified with optional out() or in_out() */ \
        CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_CLASSIFIED_NAME(p) \
    , \
        CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TYPE_REQUIREMENT(p) \
    , \
        ~ /* Boost.Parameter uses no default value for constructor */ \
    ) )

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_TYPES_COMBINATIONS_( \
        named_and_deduced_params) \
    /* re-use Boost.Parameter algorithm to cal seq of tparam combinations */ \
    BOOST_PARAMETER_FUNCTION_FWD_COMBINATIONS( \
            BOOST_PP_LIST_FOR_EACH( \
                CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_COMBINATIONS_ARG_, \
                ~, named_and_deduced_params))

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ALL_PARAMS_( \
        id, tpl, k, f, body_func, named_and_deduced_params) \
    /* structs to deduce and match params */ \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_PARAMS_(id, tpl, k, f, \
            named_and_deduced_params) \
    /* actual constructor function definitions */ \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_OVERLOADS_(id, tpl, k, f, \
            body_func, named_and_deduced_params, \
            CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_TYPES_COMBINATIONS_(\
                    named_and_deduced_params))

// PUBLIC //

// Public because used to implement the CONSTRUCTOR_ARG macro.
#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG(name) \
    /* don't wrap this expr within parenthesis at this level because it is */ \
    /* used by other internal macros (you can program another ARG macro to */ \
    /* wrap this in extra parenthesis) */ \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARGS_.get()[ \
          CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ARG_(name) \
        | CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_DEFAULT_(name) \
    ]

#define CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR(id, tpl, k, f, body_func) \
    CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR_ALL_PARAMS_( \
            id, tpl, k, f, body_func, \
            BOOST_PP_LIST_APPEND( \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED( \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f)), \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_DEDUCED( \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))))

#endif // #include guard

