
#ifndef BOOST_CONTRACT_DETAIL_INLINED_DETAIL_CHECKING_HPP_
#define BOOST_CONTRACT_DETAIL_INLINED_DETAIL_CHECKING_HPP_

// Copyright (C) 2008-2017 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// IMPORTANT: Do NOT use config macros BOOST_CONTRACT_... in this file so lib
// .cpp does not need recompiling if config changes (recompile only user code).

#include <boost/contract/detail/checking.hpp>
#include <boost/thread/lock_guard.hpp>

namespace boost { namespace contract { namespace detail {

void checking::init_unlocked() { checking_ = true; }

void checking::init_locked() {
    boost::lock_guard<boost::mutex> lock(mutex_);
    init_unlocked();
}

void checking::done_unlocked() { checking_ = false; }

void checking::done_locked() {
    boost::lock_guard<boost::mutex> lock(mutex_);
    done_unlocked();
}

bool checking::already_unlocked() { return checking_; }
    
bool checking::already_locked() {
    boost::lock_guard<boost::mutex> lock(mutex_);
    return already_unlocked();
}

// Shared state (so should be compiled as shared lib).
boost::mutex checking::mutex_;
bool checking::checking_ = false;

} } } // namespace

#endif

