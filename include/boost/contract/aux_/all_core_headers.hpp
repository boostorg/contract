
#ifndef BOOST_CONTRACT_AUX_ALL_CORE_HEADERS_HPP_
#define BOOST_CONTRACT_AUX_ALL_CORE_HEADERS_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// NOTE: This header should always be included by all public non-core headers
// so users will always automatically include all core headers (otherwise users
// will be confused not knowing if a core header has been included or not).

// IMPORTANT: In addition, <boost/contract/core/*.hpp> headers can be included
// by any file (in aux_/*, etc.) while non-core public headers
// <boost/contract/*.hpp> must not be included by any lib header file (because
// non-core public headers should be fully independent from one another and
// included only by user code). If a public header needs to be included by
// another header of lib, it should be moved to boost/contract/core/.

// Following should list all <boost/contract/core/*.hpp>.
#include <boost/contract/core/access.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/core/set_old_postcondition.hpp>
#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/core/set_precondition_old_postcondition.hpp>
#include <boost/contract/core/virtual.hpp>

#endif // #include guard

