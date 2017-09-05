
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_ARG_CONST_HPP_
#define CONTRACT_AUX_ARG_CONST_HPP_

#include <contract/config.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>

namespace contract { namespace aux {

// To ensure CONSTANT-CORRECTNESS:
// 1) Arguments are usually passed by const& -- this makes sure that
//    the referenced object is const and cannot be modified but the
//    reference could be modified. This is the way C++ usually uses 
//    reference for const because eventual modifications to the
//    reference will have local scope plus they are usually not
//    possible because copy operators and constructors operatorate on
//    const&. (The reference could be made const& const to absolutely
//    avoid any modification also to the reference itself...)
// 2) Pointers are passed as const* -- this makes sure that the
//    pointed object is const and cannot be modified but the pointer 
//    itself can still be modified. This is the way C++ usually uses
//    pointers for const because eventual modification to the pointer
//    only have local scope so do not violate const correctness. (The
//    pointer could be passed as const* const to also prevent
//    modification to the pointer itself...)
// 3) noold is passed by value (this does not affect
//    constant-correctness because noold has no member so it cannot 
//    be used to do anything.

template< typename T >
struct arg_const {
    typedef typename boost::add_reference< typename
            boost::add_const< T >::type >::type type; // T const&
};

// Specializations for Pointers //

template< typename T >
struct arg_const< T* > {
    typedef typename boost::add_pointer< typename
            boost::add_const< T >::type >::type type; // T const*
};

// Keep outer const for ptr if specified by user (but do not add it).
template< typename T >
struct arg_const< T* const > {
    typedef typename boost::add_pointer< typename
            boost::add_const< T >::type >::type const type; // T const* const
};

// Specializations for References //

// Avoid adding a reference to a reference (which gives an error).
template< typename T >
struct arg_const< T& > {
    typedef typename boost::add_reference< typename
            boost::add_const< T >::type >::type type; // T const&
};

// Specializations for Functions //

#define CONTRACT_AUX_ARG_CONST_func_A(z, n, typename01) \
    BOOST_PP_EXPR_IIF(typename01, typename) BOOST_PP_CAT(A, n)

// Const qualifier cannot be applied to function types.
//  template< typename R, typename A0, ... >
//  struct arg_const< R [(*|&)](A0, ...) > {
//      typedef R ([*|&] type)(A0, ...); // Just relay type without const.
//  };
#define CONTRACT_AUX_ARG_CONST_func(z, arity, spec_type) \
    template< \
        typename R BOOST_PP_COMMA_IF(arity) \
        BOOST_PP_ENUM_ ## z(arity, CONTRACT_AUX_ARG_CONST_func_A, 1) \
    > \
    struct arg_const< \
        R BOOST_PP_TUPLE_ELEM(2, 0, spec_type)(/* expand EMPTY */) \
        ( BOOST_PP_ENUM_ ## z(arity, CONTRACT_AUX_ARG_CONST_func_A, 0) ) \
    > { \
        typedef \
            R BOOST_PP_TUPLE_ELEM(2, 1, spec_type) \
            ( BOOST_PP_ENUM_ ## z(arity, CONTRACT_AUX_ARG_CONST_func_A, 0) ) \
        ; \
    };
        
// Function types.
BOOST_PP_REPEAT(CONTRACT_CONFIG_FUNCTION_ARITY_MAX,
        CONTRACT_AUX_ARG_CONST_func, (BOOST_PP_EMPTY, (type)) )

// Function pointers.
BOOST_PP_REPEAT(CONTRACT_CONFIG_FUNCTION_ARITY_MAX,
        CONTRACT_AUX_ARG_CONST_func, ((*) BOOST_PP_EMPTY, (* type)) )

// Function references.
BOOST_PP_REPEAT(CONTRACT_CONFIG_FUNCTION_ARITY_MAX,
        CONTRACT_AUX_ARG_CONST_func, ((&) BOOST_PP_EMPTY, (& type)) )

// #Undefine all local macros (mixed capital names).
#undef CONTRACT_AUX_ARG_CONST_func_A
#undef CONTRACT_AUX_ARG_CONST_func

// Specializations for Arrays //

#define CONTRACT_AUX_ARG_CONST_array_I(z, n, unsigned01) \
    BOOST_PP_EXPR_IIF(unsigned01, unsigned) BOOST_PP_CAT(I, n)

#define CONTRACT_AUX_ARG_CONST_array_dim(z, n, unused) \
    [ CONTRACT_AUX_ARG_CONST_array_I(z, n, 0) ]

#define CONTRACT_AUX_ARG_CONST_array(z, dim, const01) \
    template< \
        typename T, \
        BOOST_PP_ENUM_ ## z(dim, CONTRACT_AUX_ARG_CONST_array_I, 1) \
    > \
    struct arg_const< \
        T BOOST_PP_EXPR_IIF(const01, const) \
        BOOST_PP_REPEAT_ ## z(dim, CONTRACT_AUX_ARG_CONST_array_dim, ~) \
    > { \
        typedef \
            typename boost::add_const<T>::type \
            type \
            BOOST_PP_REPEAT_ ## z(dim, CONTRACT_AUX_ARG_CONST_array_dim, ~) \
        ; \
    };

// For non-const array types `T[]...[]`.
BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(CONTRACT_CONFIG_ARRAY_DIMENSION_MAX),
        CONTRACT_AUX_ARG_CONST_array, 0 /* no const */)

// For const array types `T const[]...[]`.
BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(CONTRACT_CONFIG_ARRAY_DIMENSION_MAX),
        CONTRACT_AUX_ARG_CONST_array, 1 /* const */)

#undef CONTRACT_AUX_ARG_CONST_array_I
#undef CONTRACT_AUX_ARG_CONST_array_dim
#undef CONTRACT_AUX_ARG_CONST_array

}} // namespace contract::aux

#endif // #include guard

