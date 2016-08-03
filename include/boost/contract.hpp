
#ifndef BOOST_CONTRACT_HPP_
#define BOOST_CONTRACT_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Include all header files required by this library at once (for convenience).
All headers file <c>boost/contract/\*.hpp</c> are independent from one another
and can be included one-by-one to reduce the amount of the code of this library
being compiled in user code (but that should not make a significant difference).
Instead the headers <c>boost/contract/core/\*.hpp</c> are not independent from
other library headers and they are automatically included by the
<c>boost/contract/\*.hpp</c> headers (so the <c>boost/contract/core/\*.hpp</c>
headers are usually not directly included by programmers).

All files under the <c>boost/contract/detail/</c> directory, names within the
@c boost::contract::detail namespace, names prefixed with
@c boost_contract_detail... and @c BOOST_CONTRACT_DETAIL... (in any namesapce,
including user's code) are reserved for internal use of this library and should
never be used directly by programmers.
@see @RefSect{getting_started, Getting Started}
*/

// TODO: Document that boost::contract::function() can be used to program contracts for lambda functions. And also "abused" a bit to program pre/postconditions for any arbitrary scope of code in function body.

// TODO: Document that friends do not in general check invariants so their contracts are usually programmed using function(). But if a function friend of an object takes an instance of that object as a parameter and therefore is essentially part of the object's public API, then programmers can make that explicit by using public_function(obj) after function() to program the friend function contract (but note that in general friends functions can take instances of multiple different objects because the same function can be friend of different classes).

// TODO: Document that noexcept (and exception throw(...)) specifications of the enclosing function apply to contracts. So if a contract handler is set so contract failures throw, noexcept function will still not throw, they will always terminate (because that's what users of such functions except, even if the function fails in any way, including the function contract fails).

// TODO: Document that if installing contract failure handlers that throw, it might be a good idea to check invariants at exit. That way the destructor entry invariant should *in theory* never fail (unless not all public functions, ctors are contracted, or because of non-contracted friends, or because of public data members... all those can still break the invariant before the dtor is called and before this lib will detect the invariants have failed so the dtor entry inv will fail... and what will dtor do in that case? terminate?).

// TODO: Document (in Getting Started) that some example source code has `//[...` and `//]` tags used to import example code in Quickbook docs (so doc's examples always up to date with code).

// TODO: Add a macro ALL_DISABLE_NOTHING to turn-off disabling assertions within assertions for all contracts, not just preconditions (do I still need PRECONDITIONS_DISABLE_NOTHING then?).

// TODO: Consider a better name for contract::detail::check_guard (it's confusing with old contract::guard and with current check_base::guard)... maybe I can call it contract::detail::disable?

// TODO: Consider using a trait like boost::contract::is_copy_constructible<T> (or has_old<T>) instead of boost::is_copy_constructible<T> directly (so programmers can specialize it to avoid old copies of specify types T without affecting other parts of the program that might be using boost::is_copy_constructible). Then maybe I should also introduce a trait to make the copy instead of directly using the copy constructor... so to allow for maximum customization..

// TODO: Add .except(...) that is checked at function exit when body throws (in contrast to postconditions). result is NOT accessible in .except's functor because function threw. Old values are accessible in both post and except so OLDOF copies disabled on if both except and post checking disabled (NO_EXCEPTS && NO_POSTCONDITIONS). except will have its own failure handler except_failure, check disabling macro NO_EXCEPTS, etc.

#include <boost/contract/detail/all_core_headers.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/call_if.hpp>
#include <boost/contract/constructor.hpp>
#include <boost/contract/destructor.hpp>
#include <boost/contract/function.hpp>
#include <boost/contract/check.hpp>
#include <boost/contract/old.hpp>
#include <boost/contract/override.hpp>
#include <boost/contract/public_function.hpp>

#endif // #include guard

