
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#if !BOOST_PP_IS_ITERATING
#   ifndef CONTRACT_AUX_BIND_OLD_HPP_
#       define CONTRACT_AUX_BIND_OLD_HPP_

#include <contract/copy.hpp>
#include <contract/config.hpp>
#include <contract/aux_/mpl_assert.hpp>
#include <contract/aux_/arg_const.hpp>
#include <contract/aux_/result_const.hpp>
#include <contract/aux_/preprocessor/iteration/params.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

// Old-ofs.
#define CONTRACT_comma_Old(z, n, unused) \
    , BOOST_PP_CAT(Old, n)
#define CONTRACT_comma_typename_Old(z, n, unused) \
    , typename BOOST_PP_CAT(Old, n)
#define CONTRACT_comma_typename_Old_default(z, n, unused) \
    , typename BOOST_PP_CAT(Old, n) = void_old
#define CONTRACT_comma_arg_const_Old(z, n, unused) \
    , typename arg_const< BOOST_PP_CAT(Old, n) >::type
#define CONTRACT_comma_arg_const_Old_old(z, n, unused) \
    CONTRACT_comma_arg_const_Old(z, n, ~) BOOST_PP_CAT(old, n)
#define CONTRACT_comma_old_value(z, n, unused) \
    , BOOST_PP_CAT(_old, n)->value()
// Arguments.
#define CONTRACT_Arg(z, n, unused) \
    BOOST_PP_CAT(Arg, n)
#define CONTRACT_comma_typename_Arg(z, n, unused) \
    , typename BOOST_PP_CAT(Arg, n)
#define CONTRACT_comma_arg_const_Arg(z, n, unused) \
    , typename arg_const< BOOST_PP_CAT(Arg, n) >::type
#define CONTRACT_arg_const_Arg_arg(z, n, unused) \
    typename arg_const< BOOST_PP_CAT(Arg, n) >::type BOOST_PP_CAT(arg, n)
#define CONTRACT_comma_arg(z, n, unused) \
    , BOOST_PP_CAT(arg, n)
// Typedefs.
#define CONTRACT_typedef_postcondition_type(z, n, unused) \
    typedef \
        void \
        ( BOOST_PP_EXPR_IIF(CONTRACT_AUX_PP_ITERATION_IS_MEMBER, Class::) \
          * BOOST_PP_CAT(postcondition_type, n) ) \
        ( \
            function_type \
            BOOST_PP_REPEAT_ ## z(CONTRACT_AUX_PP_ITERATION_ARITY, \
                    CONTRACT_comma_arg_const_Arg, ~) \
            BOOST_PP_REPEAT_ ## z(n, CONTRACT_comma_arg_const_Old, ~) \
            , typename result_const< Result >::type \
        ) \
        /* post func always const for members (for const-correctness) */ \
        BOOST_PP_EXPR_IIF(CONTRACT_AUX_PP_ITERATION_IS_MEMBER, const) \
        CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE \
    ;
// Constructor.
#define CONTRACT_comma_init_old(z, n, current_n) \
    , \
    BOOST_PP_CAT(_old, n)( \
        BOOST_PP_IIF(BOOST_PP_GREATER(current_n, n), \
            BOOST_PP_IDENTITY( \
                new copy< BOOST_PP_CAT(Old, n) >(BOOST_PP_CAT(old, n)) \
            ) \
        , \
            BOOST_PP_EMPTY \
        )() \
    )
#define CONTRACT_init_post_enum(z, n, current_n) \
    BOOST_PP_COMMA_IF(n) \
    BOOST_PP_CAT(_post, n)( \
        BOOST_PP_EXPR_IIF(BOOST_PP_EQUAL(n, current_n), post) \
    )
#define CONTRACT_constructor(z, n, unused) \
    explicit bind_old(BOOST_PP_CAT(postcondition_type, n) post \
        BOOST_PP_COMMA_IF(CONTRACT_AUX_PP_ITERATION_IS_MEMBER) \
        BOOST_PP_EXPR_IIF(CONTRACT_AUX_PP_ITERATION_IS_MEMBER, \
            Class const CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE* const obj \
        ) \
        BOOST_PP_REPEAT_ ## z(n, CONTRACT_comma_arg_const_Old_old, ~) \
    ) : \
        BOOST_PP_REPEAT_ ## z(BOOST_PP_INC(CONTRACT_CONFIG_OLDOF_MAX), \
                CONTRACT_init_post_enum, n) \
        BOOST_PP_COMMA_IF(CONTRACT_AUX_PP_ITERATION_IS_MEMBER) \
        BOOST_PP_EXPR_IIF(CONTRACT_AUX_PP_ITERATION_IS_MEMBER, _obj(obj)) \
        BOOST_PP_REPEAT(CONTRACT_CONFIG_OLDOF_MAX, CONTRACT_comma_init_old, n) \
    {}
// Call operator implementation.
#define CONTRACT_call_post(z, n, unused) \
    if(BOOST_PP_CAT(_post, n)) { \
        ( BOOST_PP_EXPR_IIF(CONTRACT_AUX_PP_ITERATION_IS_MEMBER, _obj->*) \
          BOOST_PP_CAT(_post, n) ) \
        ( \
            function_type() \
            BOOST_PP_REPEAT_ ## z(CONTRACT_AUX_PP_ITERATION_ARITY, \
                    CONTRACT_comma_arg, ~) \
            BOOST_PP_REPEAT_ ## z(n, CONTRACT_comma_old_value, ~) \
            , result \
        ); \
        return; /* call made, exit */ \
    }
// Member variables declarations.
#define CONTRACT_decl_post(z, n, unused) \
    BOOST_PP_CAT(postcondition_type, n) const BOOST_PP_CAT(_post, n) ;
#define CONTRACT_decl_old(z, n, unused) \
    boost::shared_ptr< copy< BOOST_PP_CAT(Old, n) > const > const \
    BOOST_PP_CAT(_old, n) ;

namespace contract { namespace aux {

// Specify tparam Old = void_old if smaller number of olds (all olds always
// given to avoid permutations of all possible args with all possible olds).
// Non-copyable because bind_old should be used so to never copy void_old.
class void_old: private boost::noncopyable {};

template<
    typename F
    BOOST_PP_REPEAT(CONTRACT_CONFIG_OLDOF_MAX,
            CONTRACT_comma_typename_Old_default, ~)
>
class bind_old {
    CONTRACT_AUX_MPL_ASSERT_MSG(sizeof(F) == 0,
            INTERNAL_ERROR_template_instantiated_with_invalid_parameters,
            (types< F, Old0, Old1 >));
};

}} // namespace contract::aux

#       define BOOST_PP_ITERATION_PARAMS_1 \
                CONTRACT_AUX_PP_ITERATION_PARAMS_ARITY( \
                        "contract/aux_/bind_old.hpp")
#       include BOOST_PP_ITERATE()
#       undef CONTRACT_comma_Old
#       undef CONTRACT_comma_typename
#       undef CONTRACT_comma_typename_Old_default
#       undef CONTRACT_comma_arg_const_Old
#       undef CONTRACT_comma_arg_const_Old_old
#       undef CONTRACT_comma_old_value
#       undef CONTRACT_Arg
#       undef CONTRACT_comma_typename_Arg
#       undef CONTRACT_comma_arg_const_Arg
#       undef CONTRACT_arg_const_Arg_arg
#       undef CONTRACT_comma_arg
#       undef CONTRACT_typedef_postcondition_type
#       undef CONTRACT_comma_init_old
#       undef CONTRACT_init_post_enum
#       undef CONTRACT_constructor
#       undef CONTRACT_call_post
#       undef CONTRACT_decl_post
#       undef CONTRACT_decl_old
#   endif // #include guard
#elif BOOST_PP_ITERATION_DEPTH() == 1
#   define BOOST_PP_ITERATION_PARAMS_2 \
            CONTRACT_AUX_PP_ITERATION_PARAMS_CV_MEMBER( \
                    "contract/aux_/bind_old.hpp")
#   include BOOST_PP_ITERATE()
#elif BOOST_PP_ITERATION_DEPTH() == 2
// Define CONTRACT_AUX_PP_ITERATION_ARITY (from iteration frame 1).
#   include <contract/aux_/preprocessor/iteration/arity_1.hpp>
// Define ..._IS_MEMBER, ..._MEMBER_CONST, and ..._MEMBER_VOLATILE (iter 2).
#   include <contract/aux_/preprocessor/iteration/cv_member_2.hpp>

namespace contract { namespace aux {

template<
    typename Result
    BOOST_PP_COMMA_IF(CONTRACT_AUX_PP_ITERATION_IS_MEMBER) 
    BOOST_PP_EXPR_IIF(CONTRACT_AUX_PP_ITERATION_IS_MEMBER, class Class)
    BOOST_PP_REPEAT(CONTRACT_AUX_PP_ITERATION_ARITY, 
            CONTRACT_comma_typename_Arg, ~)
    BOOST_PP_REPEAT(CONTRACT_CONFIG_OLDOF_MAX, CONTRACT_comma_typename_Old, ~)
>
class bind_old<
    Result
            ( BOOST_PP_EXPR_IIF(CONTRACT_AUX_PP_ITERATION_IS_MEMBER,
                    Class::) * )
            ( BOOST_PP_ENUM(CONTRACT_AUX_PP_ITERATION_ARITY, 
                    CONTRACT_Arg, ~) )
            CONTRACT_AUX_PP_ITERATION_MEMBER_CONST
            CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE
    BOOST_PP_REPEAT(CONTRACT_CONFIG_OLDOF_MAX, CONTRACT_comma_Old, ~)
> {
public:
    typedef
        Result
        ( BOOST_PP_EXPR_IIF(CONTRACT_AUX_PP_ITERATION_IS_MEMBER, Class::)
          * function_type )
        ( BOOST_PP_ENUM(CONTRACT_AUX_PP_ITERATION_ARITY, CONTRACT_Arg, ~) )
        CONTRACT_AUX_PP_ITERATION_MEMBER_CONST 
        CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE
    ;
    BOOST_PP_REPEAT(BOOST_PP_INC(CONTRACT_CONFIG_OLDOF_MAX), 
            CONTRACT_typedef_postcondition_type, ~)

    BOOST_PP_REPEAT(BOOST_PP_INC(CONTRACT_CONFIG_OLDOF_MAX),
            CONTRACT_constructor, ~)

    void operator()(
        BOOST_PP_ENUM(CONTRACT_AUX_PP_ITERATION_ARITY,
                CONTRACT_arg_const_Arg_arg, ~)
        BOOST_PP_COMMA_IF(CONTRACT_AUX_PP_ITERATION_ARITY)
        typename result_const< Result >::type result
    ) const {
        BOOST_PP_REPEAT(BOOST_PP_INC(CONTRACT_CONFIG_OLDOF_MAX),
                CONTRACT_call_post, ~)
    }

private:
    BOOST_PP_REPEAT(BOOST_PP_INC(CONTRACT_CONFIG_OLDOF_MAX),
            CONTRACT_decl_post, ~)
    BOOST_PP_EXPR_IIF(CONTRACT_AUX_PP_ITERATION_IS_MEMBER,
        Class const CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE* const _obj;
    )
    BOOST_PP_REPEAT(CONTRACT_CONFIG_OLDOF_MAX, CONTRACT_decl_old, ~)
};

}} // namespace contract::aux

#else // iteration
#   error "INTERNAL ERROR: iteration index out-of-range"
#endif // iteration

