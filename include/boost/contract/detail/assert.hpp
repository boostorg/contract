
#ifndef BOOST_CONTRACT_DETAIL_ASSERT_HPP_
#define BOOST_CONTRACT_DETAIL_ASSERT_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/preprocessor/stringize.hpp>

#define BOOST_CONTRACT_DETAIL_ASSERT(condition) \
    { \
        if(!(condition)) { \
            throw boost::contract::assertion_failure(__FILE__, __LINE__, \
                    BOOST_PP_STRINGIZE(condition)); \
        } \
    }

#endif // #include guard

