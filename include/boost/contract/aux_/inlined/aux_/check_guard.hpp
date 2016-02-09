
#ifndef BOOST_CONTRACT_AUX_INLINED_AUX_CHECK_GUARD_HPP_
#define BOOST_CONTRACT_AUX_INLINED_AUX_CHECK_GUARD_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/aux_/check_guard.hpp>
#ifndef BOOST_CONTRACT_THREAD_DISABLED
    #include <boost/thread/lock_guard.hpp>
#endif

namespace boost { namespace contract { namespace aux {

check_guard::check_guard() {
    #ifndef BOOST_CONTRACT_THREAD_DISABLED
        boost::lock_guard<boost::mutex> lock(mutex_);
    #endif
    checking_ = true;
}

check_guard::~check_guard() {
    #ifndef BOOST_CONTRACT_THREAD_DISABLED
        boost::lock_guard<boost::mutex> lock(mutex_);
    #endif
    checking_ = false;
}

bool check_guard::checking() {
    #ifndef BOOST_CONTRACT_THREAD_DISABLED
        boost::lock_guard<boost::mutex> lock(mutex_);
    #endif
    return checking_;
}

bool check_guard::checking_ = false;
#ifndef BOOST_CONTRACT_THREAD_DISABLED
    boost::mutex check_guard::mutex_;
#endif

} } } // namespace

#endif

