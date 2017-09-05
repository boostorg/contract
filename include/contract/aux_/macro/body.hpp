
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_BODY_HPP_
#define CONTRACT_AUX_BODY_HPP_

#include <contract/detail/preprocessor/traits/body.hpp>

// PRIVATE //

#define CONTRACT_AUX_BODY_FUNCTION_(body_traits) \
    CONTRACT_AUX_CODE_NAME( \
            CONTRACT_DETAIL_PP_BODY_TRAITS_OPERATOR(body_traits), \
            CONTRACT_DETAIL_PP_BODY_TRAITS_NAME(body_traits))

#define CONTRACT_AUX_BODY_FUNCTION_CONTRACTED_(body_traits) \
    CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            0, /* not constructor */ \
            0, /* not destructor */ \
            CONTRACT_DETAIL_PP_BODY_TRAITS_OPERATOR(body_traits), \
            CONTRACT_DETAIL_PP_BODY_TRAITS_NAME(body_traits), \
            (body))

// PUBLIC //

#define CONTRACT_AUX_BODY_CLASS_TYPE(class_type) \
    /* handle possible extra parenthesis to wrap commas within class_type */ \
    BOOST_PP_ARRAY_ENUM(CONTRACT_DETAIL_PP_BODY_TRAITS_CLASS_TYPE(class_type))

#define CONTRACT_AUX_BODY_FUNCTION(name) \
    CONTRACT_AUX_BODY_FUNCTION_(CONTRACT_DETAIL_PP_BODY_TRAITS( \
            0 /* not constructor */, 0 /* not destructor */, name))

#define CONTRACT_AUX_BODY_FUNCTION_CONTRACTED(name) \
    CONTRACT_AUX_BODY_FUNCTION_CONTRACTED_(CONTRACT_DETAIL_PP_BODY_TRAITS( \
            0 /* not constructor */, 0 /* not destructor */, name))

#define CONTRACT_AUX_BODY_CONSTRUCTOR_CONTRACTED(body_traits) \
    CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            1, /* constructor */ \
            0, /* not destructor */ \
            (0, ()), /* no operator traits */ \
            BOOST_PP_EMPTY, /* no name traits */ \
            (body))

#define CONTRACT_AUX_BODY_DESTRUCTOR_CONTRACTED(body_traits) \
    CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            0, /* constructor */ \
            1, /* not destructor */ \
            (0, ()), /* no operator traits */ \
            BOOST_PP_EMPTY, /* no name traits */ \
            (body))

// Only body of functions with named parameters can be deferred (because
// constructor body cannot be deferred without delegating constructors, and
// destructors have no parameter so no named parameter). The class type is
// pulled out so the same macro can be used for both free and member functions.
#define CONTRACT_AUX_BODY_PARAMETER_FUNCTION_CONTRACTED(func_name) \
    CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            0, /* not constructor */ \
            0, /* not destructor */ \
            (0, ()), /* not operator (named params n/a for operators now) */ \
            func_name, \
            (body))

#endif // #include guard

