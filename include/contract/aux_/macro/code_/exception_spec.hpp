
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_EXCEPTION_SPEC_HPP_
#define CONTRACT_AUX_CODE_EXCEPTION_SPEC_HPP_

// PRIVATE //

#define CONTRACT_AUX_CODE_EXCEPTION_SPEC_COMMA_(r, unused, i, exception) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_ARRAY_ENUM(exception)

#define CONTRACT_AUX_CODE_EXCEPTION_SPEC_(id, tpl, k, f) \
    throw( \
        /* exception list will be empty for no-throw specification */ \
        BOOST_PP_LIST_FOR_EACH_I(CONTRACT_AUX_CODE_EXCEPTION_SPEC_COMMA_, ~, \
                CONTRACT_DETAIL_PP_FUNC_TRAITS_EXCEPTIONS(f)) \
    )

// PUBLIC //

#define CONTRACT_AUX_CODE_EXCEPTION_SPEC(id, tpl, k, f) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_FUNC_TRAITS_HAS_EXCEPTION_SPEC(f), \
        CONTRACT_AUX_CODE_EXCEPTION_SPEC_ \
    , \
        BOOST_PP_TUPLE_EAT(4) /* nothing if no specification */ \
    )(id, tpl, k, f)

#endif // #include guard

