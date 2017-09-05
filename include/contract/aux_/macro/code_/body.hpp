
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_BODY_HPP_
#define CONTRACT_AUX_CODE_BODY_HPP_

#include <contract/aux_/symbol.hpp>
#include <contract/aux_/macro/code_/func.hpp>
#include <contract/detail/preprocessor/traits/func.hpp> // f

// PUBLIC //

#define CONTRACT_AUX_CODE_BODY_DECL(id, tpl, k, f, body_func) \
    BOOST_PP_IIF(CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f), \
        /* NOTE: virtual func might need (and will need if pure virtual) */ \
        /* override the body so the body must keep func orig access level */ \
        /* furthermore body needs to be called directly when derived class */ \
        /* calls its base class function */ \
        CONTRACT_DETAIL_PP_FUNC_TRAITS_ACCESS(f) : BOOST_PP_EMPTY \
    , /* else, free function */ \
        /* NOTE: it is not possible to decl free func body static here */ \
        /* otherwise body def cannot be separated from its decl */ \
        BOOST_PP_EMPTY /* do nothing */ \
    )() \
    CONTRACT_AUX_CODE_FUNC_NAMED_DECL( \
          id, tpl, k, f, body_func \
          /* body must have same access level as contracted function to */ \
          /* properly allow to define pure virtual functions */ \
        , 0 /* no access level (already handled above) */ \
        , 0 /* body not friend (only contracted func is friend, rest static) */\
        , 0 /* no explicit (body never a constructor) */ \
        , 0 /* don't force inline */ \
        , 1 /* force (void) result type (for constructors) */ \
        , 0 /* no param defaults (only func needs defaults) */ \
    )

#endif // #include guard

