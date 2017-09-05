
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CONSTRUCTOR_INITS_EVAL_HPP_
#define CONTRACT_AUX_CONSTRUCTOR_INITS_EVAL_HPP_

namespace contract { namespace aux {

// Predefined Ids for constructor inits evaluation expressions (defined in one
// place here so to make sure they are different).
static const unsigned constructor_inits_eval_try_block_set = 0;
static const unsigned constructor_inits_eval_named_params_args_set = 1;

// Allows to evaluate an expression within member initializers.
// Need Class and Id tparam to make this a unique base type for each new class.
template< class Class, unsigned Id >
struct constructor_inits_eval {
    // Default constructor for when there is no expression to evaluate.
    constructor_inits_eval ( ) {}

    // Constructor allows to evaluate the specified expr within initializers.
    template< typename ExprResult >
    explicit constructor_inits_eval ( ExprResult const& ) {}
    
    // Only defines constructors so no clash with member func/var names in
    // user-defined derived class.
};

}} // namespace contract::aux

#endif // #include guard

