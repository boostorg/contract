
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_OLDOF_HPP_
#define CONTRACT_AUX_CODE_OLDOF_HPP_

#include <contract/aux_/bind_old.hpp>
#include <contract/aux_/subcontract/oldof.hpp>
#include <contract/aux_/macro/code_/oldof_type.hpp>
#include <contract/aux_/macro/code_/postcondition.hpp>
#include <contract/detail/preprocessor/traits/func.hpp> // f
#include <contract/detail/preprocessor/traits/func_param.hpp> // p
#include <contract/detail/preprocessor/traits/oldof.hpp> // o
#include <boost/function.hpp>
#include <list>

// PRIVATE //

#define CONTRACT_AUX_CODE_OLDOF_COMMA_PARAM_DECL_(r, tpl_f, p) \
    , \
    CONTRACT_AUX_CODE_FUNC_TYPENAME(BOOST_PP_TUPLE_ELEM(2, 0, tpl_f), \
            BOOST_PP_TUPLE_ELEM(2, 1, tpl_f)) \
    ::contract::aux::arg_const< \
        BOOST_PP_ARRAY_ENUM(CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE(p)) \
    >::type \
    CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)

#define CONTRACT_AUX_CODE_OLDOF_COMMA_PARAM_NAME_(r, unused, p) \
    , \
    CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)

#define CONTRACT_AUX_CODE_OLDOF_COMMA_TYPE_(r, tpl_f, i, o) \
    , \
    CONTRACT_AUX_CODE_OLDOF_TYPE(CONTRACT_AUX_CODE_FUNC_TYPENAME01 tpl_f, o, i)

#define CONTRACT_AUX_CODE_NOOLD_COMMA_TYPE_(z, n, unused) \
    , \
    ::contract::aux::void_old

#define CONTRACT_AUX_CODE_OLDOF_COMMA_EXPR_(r, unused, o) \
    , \
    CONTRACT_DETAIL_PP_OLDOF_TRAITS_EXPR(o)

#define CONTRACT_AUX_CODE_OLDOF_AUTO_TYPEOF_TYPEDEFS_YES_(r, tpl_f, i, o) \
    typedef \
        CONTRACT_AUX_CODE_OLDOF_DEDUCE_AUTO_TYPE( \
                CONTRACT_AUX_CODE_FUNC_TYPENAME01 tpl_f, o, i) \
        CONTRACT_AUX_CODE_OLDOF_TYPE(CONTRACT_AUX_CODE_FUNC_TYPENAME01 tpl_f, \
                o, i) \
    ;

#define CONTRACT_AUX_CODE_OLDOF_AUTO_TYPEOF_TYPEDEFS_(r, tpl_f, i, o) \
    BOOST_PP_IF(BOOST_PP_ARRAY_SIZE(CONTRACT_DETAIL_PP_OLDOF_TRAITS_TYPE(o)), \
        BOOST_PP_TUPLE_EAT(4) /* explicit old-of type (no `auto`) */ \
    , \
        CONTRACT_AUX_CODE_OLDOF_AUTO_TYPEOF_TYPEDEFS_YES_ \
    )(r, tpl_f, i, o)

// Expand to nothing if old-of type is not `auto`, otherwise deduce types.
#define CONTRACT_AUX_CODE_OLDOF_AUTO_TYPEOF_(id, tpl, k, f) \
    BOOST_PP_LIST_FOR_EACH_I(CONTRACT_AUX_CODE_OLDOF_AUTO_TYPEOF_TYPEDEFS_, \
            (tpl, f), CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_OLDOFS(f))

#define CONTRACT_AUX_CODE_OLDOF_PARAM_OBJ_ \
    CONTRACT_AUX_SYMBOL( (obj) )

#define CONTRACT_AUX_CODE_OLDOF_PARAMS_DECL_(id, tpl, k, f, oldof_auto_types) \
    ( \
        /* function_type for a dummy param used to resolve overloading */ \
        /* (because pre add const to args and obj so it might have same */ \
        /* signature as of overloaded func with const arg and obj) */ \
        /* not named so it cannot be used by mistake */ \
        CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
        CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f)::body_type \
        /* constructor have static old-of but non-static post so this is */ \
        /* not accessible from static old-of but obj needs to be passed */ \
        /* as a func param so it can be bound to post func */ \
        BOOST_PP_COMMA_IF(CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k)) \
        BOOST_PP_EXPR_IIF(CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k), \
            CONTRACT_AUX_CODE_CLASS_TYPE const* const \
            CONTRACT_AUX_CODE_OLDOF_PARAM_OBJ_ \
        ) \
        /* params and objects are provided because some of the old-of */ \
        /* expr can depend on them (but they must be used as const) */ \
        /* all params are const (and ref) for const-correctness */ \
        BOOST_PP_LIST_FOR_EACH( \
                CONTRACT_AUX_CODE_OLDOF_COMMA_PARAM_DECL_, (tpl, f), \
                CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                        CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
    ) \
    BOOST_PP_EXPR_IIF(CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION( \
            k, f), \
        const /* const obj for const-correctness (unless static) */ \
    ) \
    CONTRACT_DETAIL_PP_FUNC_TRAITS_VOLATILE(f)

#define CONTRACT_AUX_CODE_OLDOF_(id, tpl, k, f, oldof_auto_types) \
    BOOST_PP_EXPR_IIF(CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f), private:) \
    CONTRACT_AUX_CODE_TEMPLATE_DECL( \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f), \
            CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                    CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
    BOOST_PP_EXPR_IIF(BOOST_PP_COMPL( \
            CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION(k, f)), \
        /* POLICY: static also for constructor because no obj yet exists */ \
        /* when evaluating old-of expr becore ctor body execution */ \
        static \
    ) \
    CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
            CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) :: \
            bound_postcondition_type \
    CONTRACT_AUX_CODE_OLDOF_FUNC(id, tpl, k, f) \
    CONTRACT_AUX_CODE_OLDOF_PARAMS_DECL_(id, tpl, k, f, oldof_auto_types) \
    { \
        CONTRACT_AUX_CODE_OLDOF_AUTO_TYPEOF_(id, tpl, k, f) \
        return ::contract::aux::bind_old< \
            CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
                    CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) :: \
                    body_type \
            BOOST_PP_LIST_FOR_EACH_I(CONTRACT_AUX_CODE_OLDOF_COMMA_TYPE_, \
                    (tpl, f), \
                    CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_OLDOFS(f)) \
            BOOST_PP_REPEAT(BOOST_PP_SUB(CONTRACT_CONFIG_OLDOF_MAX, \
                    BOOST_PP_LIST_SIZE( \
                        CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_OLDOFS( \
                        f))), \
                    CONTRACT_AUX_CODE_NOOLD_COMMA_TYPE_, ~) \
        >( \
            /* post function to bind */ \
            & /* func ptr */ \
            BOOST_PP_EXPR_IIF(CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f), \
                CONTRACT_AUX_CODE_CLASS_TYPE :: \
            ) \
            BOOST_PP_EXPR_IIF( \
                    /* post is a func tpl ptr iif oldof_auto_types != nil */ \
                    /* or func template then use template prefix only */ \
                    /* for members in type-dependent context */ \
                    BOOST_PP_BITAND( \
                          tpl \
                        , BOOST_PP_BITAND( \
                              CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f) \
                            , BOOST_PP_BITOR( \
                                  BOOST_PP_LIST_IS_CONS(oldof_auto_types) \
                                , CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f)\
                            ) \
                        ) \
                    ), \
                template \
            ) \
            CONTRACT_AUX_CODE_POSTCONDITION_FUNC(id, tpl, k, f) \
            BOOST_PP_EXPR_IIF(BOOST_PP_BITOR( \
                    BOOST_PP_LIST_IS_CONS(oldof_auto_types), \
                    BOOST_PP_LIST_IS_CONS( \
                            CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS( \
                            f)))), \
                < \
            ) \
                BOOST_PP_LIST_ENUM(oldof_auto_types) \
                BOOST_PP_COMMA_IF(BOOST_PP_BITAND( \
                        BOOST_PP_LIST_IS_CONS(oldof_auto_types), \
                        BOOST_PP_LIST_IS_CONS( \
                                CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                                CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(\
                                f))))) \
                CONTRACT_AUX_CODE_TEMPLATE_PARAM_NAME_ENUM( \
                        CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                        CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
            BOOST_PP_EXPR_IIF(BOOST_PP_BITOR( \
                    BOOST_PP_LIST_IS_CONS(oldof_auto_types), \
                    BOOST_PP_LIST_IS_CONS( \
                            CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS( \
                            f)))), \
                > \
            ) \
            /* object (only for non-static member and ctor) */ \
            BOOST_PP_COMMA_IF( \
                    CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION( \
                            k, f)) \
            BOOST_PP_EXPR_IIF( \
                    CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION( \
                            k, f), \
                this \
            ) \
            BOOST_PP_COMMA_IF(CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k)) \
            BOOST_PP_EXPR_IIF(CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k), \
                /* constructor old-of are static (because no obj exist yet) */ \
                /* but constructor post are not static (because obj exist) */ \
                /* so special param (not this) is used to bind obj to post */ \
                CONTRACT_AUX_CODE_OLDOF_PARAM_OBJ_ \
            ) \
            /* old values */ \
            BOOST_PP_LIST_FOR_EACH(CONTRACT_AUX_CODE_OLDOF_COMMA_EXPR_, ~, \
                    CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_OLDOFS(f)) \
        ); \
    }

#define CONTRACT_AUX_CODE_SUBCONTRACTED_OLDOF_COMMA_BASE_( \
        z, n, id_tpl_k_f) \
    , dynamic_cast< \
        CONTRACT_AUX_CODE_SUBCONTRACTED_BASE_TYPE( \
                BOOST_PP_TUPLE_ELEM(4, 0, id_tpl_k_f), n) \
        const \
        CONTRACT_DETAIL_PP_FUNC_TRAITS_VOLATILE( \
                BOOST_PP_TUPLE_ELEM(4, 3, id_tpl_k_f)) \
        * const \
      >(this) \
    /* call function to bind all (base, base's base, etc) oldofs */ \
    , CONTRACT_AUX_CODE_FUNC_PTR( \
          BOOST_PP_TUPLE_ELEM(4, 0, id_tpl_k_f) \
        , BOOST_PP_TUPLE_ELEM(4, 1, id_tpl_k_f) \
        , BOOST_PP_TUPLE_ELEM(4, 2, id_tpl_k_f) \
        , BOOST_PP_TUPLE_ELEM(4, 3, id_tpl_k_f) \
        , BOOST_PP_EXPAND(CONTRACT_AUX_CODE_SUBCONTRACTED_OLDOF_FUNC \
                id_tpl_k_f) \
        , CONTRACT_AUX_CODE_SUBCONTRACTED_BASE_TYPE( \
                BOOST_PP_TUPLE_ELEM(4, 0, id_tpl_k_f), n) \
    )

#define CONTRACT_AUX_CODE_SUBCONTRACTED_OLDOF_RESULT_TYPE_(id, tpl, k, f) \
    ::std::list< \
        CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
        CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) :: \
                bound_postcondition_type \
    >

#define CONTRACT_AUX_CODE_SUBCONTRACTED_OLDOF_(id, tpl, k, f) \
    public: /* must be public for subcontracting */ \
    CONTRACT_AUX_CODE_TEMPLATE_DECL( \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f), \
            CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                    CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
    CONTRACT_AUX_CODE_SUBCONTRACTED_OLDOF_RESULT_TYPE_(id, tpl, k, f) \
    CONTRACT_AUX_CODE_SUBCONTRACTED_OLDOF_FUNC(id, tpl, k, f) \
    CONTRACT_AUX_CODE_OLDOF_PARAMS_DECL_(id, tpl, k, f, oldof_auto_types) \
    { \
        return ::contract::aux::subcontract_oldof< \
            CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
            CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) \
        >( \
              this \
            , CONTRACT_AUX_CODE_FUNC_PTR(id, tpl, k, f, \
                    CONTRACT_AUX_CODE_OLDOF_FUNC(id, tpl, k, f), \
                    CONTRACT_AUX_CODE_CLASS_TYPE) \
            BOOST_PP_REPEAT(CONTRACT_CONFIG_INHERITANCE_MAX, \
                    CONTRACT_AUX_CODE_SUBCONTRACTED_OLDOF_COMMA_BASE_, \
                    (id, tpl, k, f)) \
            BOOST_PP_LIST_FOR_EACH( \
                    CONTRACT_AUX_CODE_OLDOF_COMMA_PARAM_NAME_, ~, \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                            CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
        ); \
    }

// PUBLIC //

#define CONTRACT_AUX_CODE_OLDOF_FUNC(id, tpl, k, f) \
    CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k), \
            CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k), \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_OPERATOR(f), \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(f), \
            (oldof))

#define CONTRACT_AUX_CODE_SUBCONTRACTED_OLDOF_FUNC(id, tpl, k, f) \
    CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k), \
            CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k), \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_OPERATOR(f), \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(f), \
            (subcontracted_oldof))

#define CONTRACT_AUX_CODE_OLDOF(id, tpl, k, f) \
    BOOST_PP_IIF(CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k), \
        BOOST_PP_TUPLE_EAT(5) \
    , \
        CONTRACT_AUX_CODE_OLDOF_ \
    )(id, tpl, k, f, CONTRACT_AUX_CODE_OLDOF_AUTO_TYPES( \
            CONTRACT_AUX_CODE_FUNC_TYPENAME01(tpl, f), \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_OLDOFS(f))) \
    BOOST_PP_IIF(CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION(k, f), \
        CONTRACT_AUX_CODE_SUBCONTRACTED_OLDOF_ \
    , \
        /* ctor and dtor subcontract via base-class creation rules */ \
        BOOST_PP_TUPLE_EAT(4) \
    )(id, tpl, k, f)

#endif // #include guard

