
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_HPP_
#define CONTRACT_HPP_

#include <contract/limits.hpp>
#include <contract/config.hpp>

#include <contract/broken.hpp>

#include <contract/oldof.hpp>
#include <contract/copy.hpp>

#include <contract/class.hpp>
#include <contract/class_invariant.hpp>

#include <contract/constructor.hpp>
#include <contract/destructor.hpp>
#include <contract/function.hpp>
#include <contract/body.hpp>

#include <contract/block_invariant.hpp>
#include <contract/loop_variant.hpp>

#include <contract/parameter.hpp>

// NOTE: This header allows to use the alternative operator spelling `not`, etc
// so user code can write assertions starting with alphanumeric symbols as
// `not ...` instead of `! ...`. This header is NOT used by the library
// implementation, it is included here only to allow the operator keywords in
// the user contract code. This header is required on MSVC but it has no effect
// on C++ compliant compilers like GCC that correctly define `not`, etc.
#include <ciso646>

#endif // #include guard

