
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#if !BOOST_PP_IS_ITERATING
#   ifndef CONTRACT_AUX_CALL_CONSTRUCTOR_ENTRY_HPP_
#       define CONTRACT_AUX_CALL_CONSTRUCTOR_ENTRY_HPP_
#       include <contract/aux_/call/impl_/include.hpp>
#       include <contract/aux_/preprocessor/iteration/params.hpp>
#       include <boost/preprocessor/iteration/iterate.hpp>
#       include <contract/aux_/call/impl_/define.hpp>

namespace contract { namespace aux {

// NOTE: The Class tparam is necessary to make this a new type to inherit from
// for each new class (to avoid inheritance ambiguity errors-- virtual
// inheritance cannot be used to resolve ambiguity because it will create only
// one call_constructor_entry base object and therefore check constructor entry
// contracts only for one of the base classes).
template< class Class >
struct call_constructor_entry {
    // NOTE: This default constructor is necessary to allow for eventual user
    // constructors without a contract (i.e., not wrapped by this lib macros).
    call_constructor_entry() {}

    // Only defines additional constructors so it does not clash with member
    // func/var names defined by user deriving from this class.

#       define BOOST_PP_ITERATION_PARAMS_1 \
                CONTRACT_AUX_PP_ITERATION_PARAMS_ARITY( \
                        "contract/aux_/call/constructor_entry.hpp")
#       include BOOST_PP_ITERATE()

};

}} // namespace contract::aux

#       include <contract/aux_/call/impl_/undef.hpp>
#   endif // #include guard
#elif BOOST_PP_ITERATION_DEPTH() == 1
// Define CONTRACT_AUX_PP_ITERATION_ARITY (from iteration frame 1).
#   include <contract/aux_/preprocessor/iteration/arity_1.hpp>
#   define CONTRACT_AUX_CALL_ARITY CONTRACT_AUX_PP_ITERATION_ARITY
#   define CONTRACT_AUX_CALL_IS_MEMBER 1
#   define CONTRACT_AUX_CALL_IS_STATIC 0
#   define CONTRACT_AUX_CALL_IS_DESTRUCTOR 0
#   define CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY 1
#   define CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT 0
#   include <contract/aux_/call/impl_/function.hpp> // Generate func code.
#else // iteration
#   error "INTERNAL ERROR: iteration index out-of-range"
#endif // iteration

