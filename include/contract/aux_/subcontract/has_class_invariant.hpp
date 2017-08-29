
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_SUBCONTRACT_HAS_CLASS_INVARIANT_HPP_
#define CONTRACT_AUX_SUBCONTRACT_HAS_CLASS_INVARIANT_HPP_

#include <contract/aux_/has_xxx_member_function.hpp>

// NOTE: This symbol must be used to name the subcontract class invariant meber
// function in order for this introspection check to work.
#define CONTRACT_AUX_CODE_SUBCONTRACT_HAS_CLASS_INVARIANT_FUNC \
    CONTRACT_AUX_SYMBOL( (subcontracted_class_invariant) )

namespace contract { namespace aux {

// Decl has_subcontracted_class_invariant< void (Base::*) ( ) const> metafunc.
// NOTE: This can be done here because all class invariant functions have the
// same name and signature. Unfortunately, that is not true instead of user
// defined member functions for which the introspecting metafunction must be
// defined within the user class decl itself by the expansion of the FUNCTION
// macro (and similarly for the virtual specifier introspection tag functions
// and check metafunctions that also depend by the func names and signature).
CONTRACT_AUX_HAS_XXX_MEMBER_FUNCTION(has_subcontracted_class_invariant,
        CONTRACT_AUX_CODE_SUBCONTRACT_HAS_CLASS_INVARIANT_FUNC)

}} // namespace contract::aux

#endif // #include guard

