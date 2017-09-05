
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT_HPP_
#define CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT_HPP_

#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand to `(comma_n, (default_value_token1, ...))` (array for unwrapped
// commas, 0-size array if no default value).
#define CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT(fparam) \
    BOOST_PP_TUPLE_ELEM(2, 1, fparam)

#endif // #include guard

