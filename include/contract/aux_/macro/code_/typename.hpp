
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_TYPENAME_HPP_
#define CONTRACT_AUX_CODE_TYPENAME_HPP_

#include <contract/detail/preprocessor/traits/class.hpp> // c
#include <contract/detail/preprocessor/traits/func.hpp> // f
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/logical/bitor.hpp>

// PRIVATE //

#define CONTRACT_AUX_CODE_TYPENAME01_(tpl, params) \
    /* the typename keyword should be used to resolve nested type */ \
    /* expressions if the enclosing scope is a template (tpl is 1) or */ \
    /* the declared class or function has non-empty template parameters */ \
    /* (template specializations with empty template parameters will still */ \
    /* be templates (...TRAITS_IS_TEMPLATE is 1) but they do not make for */ \
    /* a type-dependent scope so the actual template parameters are used) */ \
    BOOST_PP_BITOR( \
          tpl \
        , BOOST_PP_BITOR( \
              BOOST_PP_LIST_IS_CONS( \
                    CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL(params)) \
            , BOOST_PP_BITOR( \
                  BOOST_PP_LIST_IS_CONS( \
                        CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED(params)) \
                , BOOST_PP_LIST_IS_CONS( \
                        CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED(params)) \
            ) \
        ) \
    ) \

// PUBLIC //

#define CONTRACT_AUX_CODE_CLASS_TYPENAME01(tpl, c) \
    CONTRACT_AUX_CODE_TYPENAME01_(tpl, \
            CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_PARAMS(c))

#define CONTRACT_AUX_CODE_CLASS_TYPENAME(tpl, c) \
    BOOST_PP_EXPR_IIF(CONTRACT_AUX_CODE_CLASS_TYPENAME01(tpl, c), typename)

#define CONTRACT_AUX_CODE_FUNC_TYPENAME01(tpl, f) \
    CONTRACT_AUX_CODE_TYPENAME01_(tpl, \
            CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))

#define CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
    BOOST_PP_EXPR_IIF(CONTRACT_AUX_CODE_FUNC_TYPENAME01(tpl, f), typename)

#endif // #include guard

