
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CALL_DESTRUCTOR_HPP_
#   define CONTRACT_AUX_CALL_DESTRUCTOR_HPP_
#   include <contract/aux_/call/impl_/include.hpp>
#   include <contract/aux_/call/impl_/define.hpp>

namespace contract { namespace aux {

#   define CONTRACT_AUX_CALL_ARITY 0 // Destructors have no argument.
#   define CONTRACT_AUX_CALL_IS_MEMBER 1
#   define CONTRACT_AUX_CALL_IS_STATIC 0
#   define CONTRACT_AUX_CALL_IS_DESTRUCTOR 1
#   define CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY 0
#   define CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT 0
#   include <contract/aux_/call/impl_/function.hpp> // Generate func code.

}} // namespace contract::aux

#   include <contract/aux_/call/impl_/undef.hpp>
#endif // #include guard

