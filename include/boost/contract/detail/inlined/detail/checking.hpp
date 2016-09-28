
#ifndef BOOST_CONTRACT_DETAIL_INLINED_DETAIL_CHECKING_HPP_
#define BOOST_CONTRACT_DETAIL_INLINED_DETAIL_CHECKING_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/checking.hpp>
#ifndef BOOST_CONTRACT_DISABLE_THREADS
    #include <boost/thread/lock_guard.hpp>
#endif

namespace boost { namespace contract { namespace detail {

checking::checking() {
    #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
        #ifndef BOOST_CONTRACT_DISABLE_THREADS
            boost::lock_guard<boost::mutex> lock(mutex_);
        #endif
        checking_ = true;
    #endif // Else, do nothing.
}

checking::~checking() {
    #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
        #ifndef BOOST_CONTRACT_DISABLE_THREADS
            boost::lock_guard<boost::mutex> lock(mutex_);
        #endif
        checking_ = false;
    #endif // Else, do nothing.
}

bool checking::already() {
    #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
        #ifndef BOOST_CONTRACT_DISABLE_THREADS
            boost::lock_guard<boost::mutex> lock(mutex_);
        #endif
        return checking_;
    #else
        return false; // Never already checking (so no assertion ever disabled).
    #endif
}

bool checking::checking_ = false;
#ifndef BOOST_CONTRACT_DISABLE_THREADS
    boost::mutex checking::mutex_;
#endif

} } } // namespace

#endif

