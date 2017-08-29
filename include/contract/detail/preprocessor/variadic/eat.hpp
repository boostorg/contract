
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_VARIADIC_EAT_HPP_
#define CONTRACT_DETAIL_PP_VARIADIC_EAT_HPP_

// Do not use Boost.PP variadic because they use a different config macro.
#include <boost/config.hpp>
#ifndef BOOST_NO_VARIADIC_MACROS

// PUBLIC //

#define CONTRACT_DETAIL_PP_VARIADIC_EAT(...) /* must expand to nothing */

#endif

#endif // #include guard

