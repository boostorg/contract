
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_OLDOF_TRAITS_TYPE_HPP_
#define CONTRACT_DETAIL_PP_OLDOF_TRAITS_TYPE_HPP_

#include <boost/preprocessor/array/elem.hpp>

// PUBLIC //

// Expand to `(n, (type_token0, ...))` (array for unwrapped commas, 0-size
// array for no old-of type specified).
#define CONTRACT_DETAIL_PP_OLDOF_TRAITS_TYPE(oldof_traits) \
    BOOST_PP_ARRAY_ELEM(0, oldof_traits)

#endif // #include guard

