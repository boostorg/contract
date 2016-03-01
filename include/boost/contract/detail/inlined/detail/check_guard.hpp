
#ifndef BOOST_CONTRACT_DETAIL_INLINED_DETAIL_CHECK_GUARD_HPP_
#define BOOST_CONTRACT_DETAIL_INLINED_DETAIL_CHECK_GUARD_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/check_guard.hpp>
#ifndef BOOST_CONTRACT_DISABLE_THREADS
    #include <boost/thread/lock_guard.hpp>
#endif

namespace boost { namespace contract { namespace detail {

check_guard::check_guard() {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        boost::lock_guard<boost::mutex> lock(mutex_);
    #endif
    checking_ = true;
}

check_guard::~check_guard() {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        boost::lock_guard<boost::mutex> lock(mutex_);
    #endif
    checking_ = false;
}

bool check_guard::checking() {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        boost::lock_guard<boost::mutex> lock(mutex_);
    #endif
    return checking_;
}

bool check_guard::checking_ = false;
#ifndef BOOST_CONTRACT_DISABLE_THREADS
    boost::mutex check_guard::mutex_;
#endif

} } } // namespace

#endif

