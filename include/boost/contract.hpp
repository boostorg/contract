
#ifndef BOOST_CONTRACT_HPP_
#define BOOST_CONTRACT_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file */

// Include all and only public headers as users would (not core headers, etc.).
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

// TODO: Document compile and run time performances (after creating specific tests to measure them).

// TODO: Document that default generated functions (generated default constructors, copy constructors, copy operators, destructors, move constructors, move operators, etc.) will not check contracts. Programmer have to program them in order to check contracts.

// TODO: Add all copyright and licencing info (to all files, etc.).

// TODO: Should C++11 move preserve class invariants at exit and/or on throw? Maybe not because after move no other public member can be called (but dtor can... so dtor should not check inv at that time...). If so, users could use an internal moved_ data member to guard class invariant checking and set that after the move operation... How can I program C++11 move operations with this lib? Should I used boost::contract::function instead of public_function? (But probably not because that does not subcontract and does not check inv at entry...)

// TODO: Document that there is a MSVC 2010 bug for which lambdas cannot be used in template constructor intialization list (this was fixed in MSVC 2013). Therefore, an external (static member) function must be used (possibly with bind and cref) to program constructor preconditions on MSVC 2010 instead of using lambdas.

// TODO: Document that users could program (scoped) locks at top of function definitions and before the contract code so to deal with contracts in multi-threaded situations. Would these locks need to be recursive for virtual calls? Test that...

// TODO: Document pre > old > post are all optional but when they are specified they must be specified in this order (rationale: this is the logical order in which to specify them, other contract programming framework allow to mix this order, that could have been implemented in this lib too but it would complicated a bit the implementation to then allow for mixed orders that will be less clear logically).

#endif // #include guard

