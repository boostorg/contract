
#ifndef BOOST_CONTRACT_GUARD_HPP_
#define BOOST_CONTRACT_GUARD_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file */

#include <boost/contract/aux_/all_core_headers.hpp>
#include <boost/contract/aux_/condition/check_base.hpp>
#include <boost/contract/aux_/auto_ptr.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/config.hpp>

/* PRIVATE */

#if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
        BOOST_CONTRACT_INVARIANTS
    #define BOOST_CONTRACT_GUARD_CTOR_DEF_(contract_type) \
            : check_(const_cast<contract_type&>(contract).check_.release()) \
        { \
            BOOST_CONTRACT_AUX_DEBUG(check_); \
            check_->guard(); \
        }
#else
    #define BOOST_CONTRACT_GUARD_CTOR_DEF_(contract_type) {}
#endif

// Following implicit to allow syntax `guard c = ...`.
#define BOOST_CONTRACT_GUARD_CTOR_(contract_type) \
    /* implicit */ guard(contract_type const& contract) \
    BOOST_CONTRACT_GUARD_CTOR_DEF_(contract_type)

/* CODE */

namespace boost { namespace contract {

class guard { // Non-copyable (but copy ctor ~= move via ptr release).
public:
    // Following copy and implicit type conversion ctors allow `guard c = ...`.
    
    guard(guard const& other) // Copy ctor moves check_ pointer to dest.
        #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
                BOOST_CONTRACT_INVARIANTS
            : check_(const_cast<guard&>(other).check_.release())
        #endif
    {}

    template<typename R>
    BOOST_CONTRACT_GUARD_CTOR_(set_precondition_old_postcondition<R>)
    
    template<typename R>
    BOOST_CONTRACT_GUARD_CTOR_(set_old_postcondition<R>)
    
    template<typename R>
    BOOST_CONTRACT_GUARD_CTOR_(set_postcondition_only<R>)
    
    BOOST_CONTRACT_GUARD_CTOR_(set_nothing)

    ~guard() BOOST_NOEXCEPT_IF(false) {} // Allow auto_ptr dtor to throw.

private:
    guard& operator=(guard const&); // Cannot copy outside of `guard c = ...`.

    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        boost::contract::aux::auto_ptr<boost::contract::aux::check_base> check_;
    #endif
};

} } // namespace

#endif // #include guard

