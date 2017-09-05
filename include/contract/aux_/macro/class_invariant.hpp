
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CLASS_INVARIANT_HPP_
#define CONTRACT_AUX_CLASS_INVARIANT_HPP_

#include <contract/aux_/macro/code_/class_invariant_const.hpp>
#include <contract/aux_/macro/code_/class_invariant_const_volatile.hpp>
#include <contract/aux_/macro/code_/class_invariant_static.hpp>
#include <contract/detail/preprocessor/traits/class_invariant.hpp> // v

// PRIVATE //

#define CONTRACT_AUX_CLASS_INVARIANT_(id, tpl, v) \
    /* NOTE: subcontracted invariants must be decl by CLASS macro because */ \
    /* they always need to be public while this macro expand in private */ \
    /* context for class (and in public for struct) so it cannot always */ \
    /* decl subcontracted invariants public (following non-subcontracted */ \
    /* inv can instead be decl here because they do not need to be public) */ \
    CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC(id, tpl, v) \
    CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE(id, tpl, v) \
    CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST(id, tpl, v)

#define CONTRACT_AUX_CLASS_INVARIANT_SEQ_(id, tpl, assertion_seq) \
    CONTRACT_AUX_CLASS_INVARIANT_(id, tpl, \
            CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS(assertion_seq))

// PUBLIC //

#define CONTRACT_AUX_CLASS_INVARIANT(id, tpl, assertion_seq) \
    }; /* close `{` entered by the user after CONTRACT_CLASS macro */ \
    BOOST_PP_IIF(CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01, \
        CONTRACT_AUX_CLASS_INVARIANT_SEQ_ \
    , \
        BOOST_PP_TUPLE_EAT(3) \
    )(id, tpl, assertion_seq)

#endif // #include guard

