
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_THREAD_VARIABLE_HPP_
#define CONTRACT_AUX_THREAD_VARIABLE_HPP_

#if CONTRACT_AUX_CONFIG_THREAD_SAFE_01
#   include <boost/thread/recursive_mutex.hpp> // Required only if thread safe.
#endif

namespace contract { namespace aux {

template<typename T>
class thread_variable {
public:
    // Both implicit and default constructors.
    /* implicit */ thread_variable(T const& value): value_(value) {}
    thread_variable(): value_(T()) {} // Default T() requires only if this used.

    // Set //

    void operator=(T const& value) { // Sync so cannot return object&.
#if CONTRACT_AUX_CONFIG_THREAD_SAFE_01
        boost::recursive_mutex::scoped_lock lock(mutex_);
#endif
        value_ = value;
    } // Release eventual lock.
    
    void operator=(T const& value) volatile { // Sync so cannot return object&.
#if CONTRACT_AUX_CONFIG_THREAD_SAFE_01
        boost::recursive_mutex::scoped_lock lock(mutex_);
#endif
        value_ = value;
    } // Release eventual lock.

    // Get //
    
    operator T() const { // Sync so must return object copy (by value).
#if CONTRACT_AUX_CONFIG_THREAD_SAFE_01
        boost::recursive_mutex::scoped_lock lock(mutex_);
#endif
        return value_;
    } // Release eventual lock.
    
    operator T() const volatile { // Sync so must return object copy (by value).
#if CONTRACT_AUX_CONFIG_THREAD_SAFE_01
        boost::recursive_mutex::scoped_lock lock(mutex_);
#endif
        return value_;
    } // Release eventual lock.

private:
    T value_;

#if CONTRACT_AUX_CONFIG_THREAD_SAFE_01
    mutable boost::recursive_mutex mutex_;
#endif
};

}} // namespace contract::aux

#endif // #include guard

