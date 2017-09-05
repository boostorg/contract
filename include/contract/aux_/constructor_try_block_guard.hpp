
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CONSTRUCTOR_TRY_BLOCK_GUARD_HPP_
#define CONTRACT_AUX_CONSTRUCTOR_TRY_BLOCK_GUARD_HPP_

#include <contract/aux_/symbol.hpp>

namespace contract { namespace aux {

// Need Class tparam to make this a unique base type for each new class.
template< class Class >
struct constructor_try_block_guard {
    // Default constructor also handles constructor with no try-block.
    constructor_try_block_guard ( ) : enabled_(false) {}

    // These need to be named with library reserved symbols to not clash
    // with member func/var names in user-defined derived class.

    bool CONTRACT_AUX_SYMBOL( (enabled) ) ( ) const { return enabled_; }
    
    // NOTE: These need to return a value to be used within member inits set.
    bool CONTRACT_AUX_SYMBOL( (enable) ) ( ) { return enabled_ = true; }
    bool CONTRACT_AUX_SYMBOL( (disable) ) ( ) { return enabled_ = false; }

private:
    // Constructors never const or volatile so no need to make this mutable,
    // provide volatile access members, etc.
    bool enabled_;
};

}} // namespace contract::aux

#endif // #include guard

