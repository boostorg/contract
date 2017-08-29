
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_ARRAY_REM_HPP_
#define CONTRACT_DETAIL_PP_ARRAY_REM_HPP_

#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <boost/preprocessor/array/data.hpp>

// PUBLIC //

#define CONTRACT_DETAIL_PP_ARRAY_REM(array) \
    BOOST_PP_TUPLE_REM_CTOR(BOOST_PP_ARRAY_SIZE(array), \
            BOOST_PP_ARRAY_DATA(array))

#endif // #include guard

