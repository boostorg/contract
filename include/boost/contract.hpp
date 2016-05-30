
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

#include <boost/contract/detail/all_core_headers.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/call_if.hpp>
#include <boost/contract/constructor.hpp>
#include <boost/contract/destructor.hpp>
#include <boost/contract/function.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/old.hpp>
#include <boost/contract/override.hpp>
#include <boost/contract/public_function.hpp>

// TODO: Add a test for all operators (member and non-member ones). In theory nothing special should be needed for operators... but test it. For member operators, test them with public_function virtual overrides.

// TODO: Document compile and run time performances (after creating specific tests to measure them).

// TODO: Add all copyright and licencing info (to all files, etc.).

// TODO: Document that default generated functions (generated default constructors, copy constructors, copy operators, destructors, move constructors, move operators, etc.) will not check contracts. Programmer have to program them in order to check contracts. Also default special operations might not be able to establish class invariants (default ctor, etc.) and/or might break it (default move operations).

// TODO: Document an example that uses moved() to fully specify move semantics using contracts (similar to "test/move/contracts.cpp").

// TODO: Document that there is a MSVC 2010 bug for which lambdas cannot be used in template constructor intialization list (this was fixed in MSVC 2013). Therefore, an external (static member) function must be used (possibly with bind and cref) to program constructor preconditions on MSVC 2010 instead of using lambdas.

// TODO: Document that users could program (scoped) locks at top of function definitions and before the contract code so to deal with contracts in multi-threaded situations. Would these locks need to be recursive for virtual calls? Test that...

// TODO: Document pre > old > post are all optional but when they are specified they must be specified in this order (rationale: this is the logical order in which to specify them, other contract programming framework allow to mix this order, that could have been implemented in this lib too but it would complicated a bit the implementation to then allow for mixed orders that will be less clear logically).

#endif // #include guard

