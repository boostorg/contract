// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_CHECKING_HPP_
#define CONTRACT_AUX_CHECKING_HPP_

#include "sync.hpp"

namespace contract { namespace aux {

static sync<bool, false> globally_checking_contract;

}} // namespace

#endif // #include guard

