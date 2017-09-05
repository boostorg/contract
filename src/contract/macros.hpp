// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_MACROS_HPP_
#define CONTRACT_MACROS_HPP_

#include "aux_/macros/invariant.hpp"
#include "aux_/macros/function.hpp"
// For the code of the macro expansion.
#include "nonmember_function.hpp"
#include "nonstatic_member_function.hpp"
#include "static_member_function.hpp"
#include "constructor.hpp"
#include "destructor.hpp"

#define CONTRACT_INVARIANT(sequence) \
    CONTRACT_AUX_INVARIANT(sequence)

#define CONTRACT_CONSTRUCTOR(sequence) \
    CONTRACT_AUX_CONSTRUCTOR(sequence)

#define CONTRACT_DESTRUCTOR(sequence) \
    CONTRACT_AUX_DESTRUCTOR(sequence)

#define CONTRACT_FUNCTION(sequence) \
    CONTRACT_AUX_FUNCTION(sequence)

#endif // #include guard

