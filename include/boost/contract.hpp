
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

// TODO: Document that friends do not in general check invariants so their contracts are usually programmed using function(). But if a function friend of an object takes an instance of that object as a parameter and therefore is essentially part of the object's public API, then programmers can make that explicit by using public_function(obj) after function() to program the friend function contract (but note that in general friends functions can take instances of multiple different objects because the same function can be friend of different classes). Also add a test (under test/public_function/...) and an example for friend.

// TODO: Document that noexcept (and exception throw(...)) specifications of the enclosing function apply to contracts. So if a contract handler is set so contract failures throw, noexcept function will still not throw, they will always terminate (because that's what users of such functions except, even if the function fails in any way, including the function contract fails).

// TODO: Document that if installing contract failure handlers that throw, it might be a good idea to check invariants at exit. That way the destructor entry invariant should *in theory* never fail (unless not all public functions, ctors are contracted, or because of non-contracted friends, or because of public data members... all those can still break the invariant before the dtor is called and before this lib will detect the invariants have failed so the dtor entry inv will fail... and what will dtor do in that case? terminate?).

// TODO: Document (in Getting Started) that some example source code has `//[...` and `//]` tags used to import example code in Quickbook docs (so doc's examples always up to date with code).

// TODO: Document that result is NOT accessible in .except's functor because function threw. Old values are accessible in both post and except so OLDOF copies disabled on if both except and post checking disabled (NO_EXCEPTS && NO_POSTCONDITIONS). except will have its own failure handler except_failure, check disabling macro NO_EXCEPTS, etc.

// TODO: Document that contract for constexpr functions cannot be supported at the moment because constexpr functions cannot: (1) declare local variables of (literal) types with non-trivial constexpr destructors (needed by this lib to check inv, post, and except at exit), (2) call other (constexpr) functions with try-catch statements (used by this lib to report assertion failure and catch any other exception that might be thrown by the evaluation of the asserted conditions), (3) use lambda functions (use by this for convenience to program functors that check per and post). Also note that even if supported, contracts for constexpr probably will not use old values (because constexpr prevent the function from having any side effect visible to the caller, variables around such side-effects are usually the candidates for old value copies) and subcontracting (because constexpr functions cannot be virtual).

// TODO: Documentation updates based on all emails to Boost (review all emails).

// TODO: Documentation updates based on all n-papers that I read recently (review notes I wrote on all papers), add those n-papers to the Bibliography section, and add P0380 (the most recent proposal) to the feature comparison table.

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

