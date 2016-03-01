
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// WARNING: Following inlined code MUST NOT use any #if BOOST_CONTRACT_NO_...
// because that would require to distribute different pre-compiled versions of
// this lib one for each BOOST_CONTRACT_NO_... combination.
// (Plus, as always in C++, they cannot contain template code because these
// headers will be linked and not #included by user code.)

#define BOOST_CONTRACT_DETAIL_SOURCE
#include <boost/contract/detail/inlined/core/exception.hpp>
#include <boost/contract/detail/inlined/detail/check_guard.hpp>

