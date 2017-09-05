
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_COPY_RESULT_HPP_
#define CONTRACT_AUX_COPY_RESULT_HPP_

#include <contract/config.hpp>
#include <contract/copy.hpp>
#include <contract/aux_/result_const.hpp> // For void_result.
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/type_traits/add_reference.hpp>

#define CONTRACT_comma_typename_Arg(z, n, unused) \
    , typename BOOST_PP_CAT(Arg, n)
#define CONTRACT_comma_arg_param(z, n, unused) \
    /* NOTE: this param type must be a ref to avoid copying the arg (which */ \
    /* might not have a copy cons, ref is OK because caller always uses a */ \
    /* var to hold this param) plus add_reference can't be used otherwise */ \
    /* Arg type cannot be deduced (and cons cannot specify tparams) */ \
    , BOOST_PP_CAT(Arg, n) & \
    BOOST_PP_CAT(arg, n)
#define CONTRACT_arg(z, n, unused) \
    BOOST_PP_CAT(arg, n)

#define CONTRACT_call_func(z, n, is_member) \
    BOOST_PP_IIF(is_member, \
        (obj->*func) \
    , \
        (*func) \
    )( \
        BOOST_PP_ENUM_ ## z(n, CONTRACT_arg, ~) \
    )

#define CONTRACT_cons_decl(z, n, is_member) \
    template< typename Func \
        BOOST_PP_REPEAT_ ## z(n, CONTRACT_comma_typename_Arg, ~) \
    > \
    explicit copy_result(Func const func \
        BOOST_PP_COMMA_IF(is_member) \
        BOOST_PP_EXPR_IIF(is_member, CVQualifiedObj const obj) \
        BOOST_PP_REPEAT_ ## z(n, CONTRACT_comma_arg_param, ~) \
    )
#define CONTRACT_cons(z, n, is_member) \
    CONTRACT_cons_decl(z, n, is_member) \
        : result_(CONTRACT_call_func(z, n, is_member)) {}
#define CONTRACT_void_cons(z, n, is_member) \
    CONTRACT_cons_decl(z, n, is_member) \
        { CONTRACT_call_func(z, n, is_member) ; }

namespace contract { namespace aux {

// Copy result of non-void non-static mem func.
template< typename Result, class CVQualifiedObj = void >
struct copy_result {
    BOOST_PP_REPEAT(BOOST_PP_INC(CONTRACT_CONFIG_FUNCTION_ARITY_MAX),
            CONTRACT_cons, 1 /* member */) // INC(ARITY) for no arg.

    typename copy<Result>::const_reference_type value() const
        { return result_.value(); }
    typename copy<Result>::const_reference_type param() const
        { return result_.value(); }
private:
    copy<Result> const result_; // Use copy<> so user can customize.
};

// Copy result of non-void free func and static member func.
template< typename Result >
struct copy_result< Result, void > {
    BOOST_PP_REPEAT(BOOST_PP_INC(CONTRACT_CONFIG_FUNCTION_ARITY_MAX),
            CONTRACT_cons, 0 /* not member */) // INC(ARITY) for no arg.

    typename copy<Result>::const_reference_type value() const
        { return result_.value(); }
    typename copy<Result>::const_reference_type param() const
        { return result_.value(); }
private:
    copy<Result> const result_; // Use copy<> so user can customize.
};

// Handle Void Result //

// Copy result of void non-static member func.
template< class CVQualifiedObj >
struct copy_result< void, CVQualifiedObj > {
    BOOST_PP_REPEAT(BOOST_PP_INC(CONTRACT_CONFIG_FUNCTION_ARITY_MAX),
            CONTRACT_void_cons, 1 /* member */) // INC(ARITY) for no arg.

    void value() const {} // There is no result to return (return void).
    void_result param() const { return void_result(); }
};

// Copy result of void non-static member func.
template< >
struct copy_result< void, void > {
    BOOST_PP_REPEAT(BOOST_PP_INC(CONTRACT_CONFIG_FUNCTION_ARITY_MAX), 
            CONTRACT_void_cons, 0 /* not member */) // INC(ARITY) for no arg.

    void value() const {} // There is no result to return (return void).
    void_result param() const { return void_result(); }
};

}} // namespace contract::aux

#undef CONTRACT_comma_typename_Arg
#undef CONTRACT_comma_arg_param
#undef CONTRACT_arg
#undef CONTRACT_call_func
#undef CONTRACT_cons_decl
#undef CONTRACT_cons
#undef CONTRACT_void_cons

#endif // #include guard

