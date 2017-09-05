// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_HPP_
#define CONTRACT_HPP_

// GETTING STARTED
//
// See the library documentation in the "doc/" for more information.
//
// It is recommended to include the library simply by including
// this file ``#include <contract.hpp>'' (instead of separately
// including files from the "contract/" directory).
// The library is composed of header files only so the #include above
// is all it is needed to use the library and compile (there is no
// pre-compiled library object file to link).
//
// Contract compilation must be explicitly turned on at compile time
// #defining the following macro symbols:
//   CONTRACT_CHECK_BLOCK_INVARIANT  Compile and check block invariants.
//   CONTRACT_CHECK_CLASS_INVARIANT  Compile and check class invariants.
//   CONTRACT_CHECK_PRECONDITION     Compile and check preconditions.
//   CONTRACT_CHECK_POSTCONDITION    Compile and check postconditions.
// By default, all these macro symbols are #undefined and contract
// compilation is turned off. For example, the following turns on
// invariant and preconditions (but not postconditions) using g++:
//   $ g++ -DCONTRACT_CHECK_CLASS INVARIANT
//       -DCONTRACT_CHECK_PRECONDITION
//       -UCONTRACT_CHECK_POSTCONDITION ...
// 
// All library files in the "contract/aux_/" directory, all names in
// the 'contract::aux' namespace, all symbols starting with
// 'CONTRACT_AUX', all names and symbols starting with 'contract' or
// 'CONTRACT' and ending with an underscore '_' are library
// implementation specific and must NOT be used directly in user code.

// Tools.
#include "contract/config.hpp"
#include "contract/from.hpp"
#include "contract/assert.hpp"
#include "contract/old.hpp"
#include "contract/body.hpp"
#include "contract/state.hpp"
#include "contract/wrap.hpp"

// Contracts without macros.
#include "contract/nonmember_function.hpp"
#include "contract/nonstatic_member_function.hpp"
#include "contract/static_member_function.hpp"
#include "contract/constructor.hpp"
#include "contract/destructor.hpp"

// Contract macros.
#include "contract/macros.hpp"
#include "contract/block.hpp"

#endif // #include guard

