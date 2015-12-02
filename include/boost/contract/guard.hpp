
#ifndef BOOST_CONTRACT_GUARD_HPP_
#define BOOST_CONTRACT_GUARD_HPP_

/** @file */

#include <boost/contract/core/set_precondition_old_postcondition.hpp>
#include <boost/contract/core/set_old_postcondition.hpp>
#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/condition/check_base.hpp>
#include <boost/contract/aux_/debug.hpp>
/** @cond */
#include <boost/noncopyable.hpp>
#include <boost/config.hpp>
/** @endcond */

// TODO: Add a test for when `guard c = ...` is missing.

namespace boost { namespace contract {

class guard { // Copyable as * (OK also for RAII).
public:
    // Following all implicit to allow syntax `guard c = ...`.
    
    template<typename R>
    /* implicit */ guard(set_precondition_old_postcondition<R> const& contract)
            : check_(contract.check_) {
        BOOST_CONTRACT_AUX_DEBUG(check_);
        check_->guard();
    }
    
    template<typename R>
    /* implicit */ guard(set_old_postcondition<R> const& contract)
            : check_(contract.check_) {
        BOOST_CONTRACT_AUX_DEBUG(check_);
        check_->guard();
    }
    
    template<typename R>
    /* implicit */ guard(set_postcondition_only<R> const& contract)
            : check_(contract.check_) {
        BOOST_CONTRACT_AUX_DEBUG(check_);
        check_->guard();
    }
    
    /* implicit */ guard(set_nothing const& contract)
            : check_(contract.check_) {
        BOOST_CONTRACT_AUX_DEBUG(check_);
        check_->guard();
    }

    ~guard() BOOST_NOEXCEPT_IF(false) { delete check_; } // Also for RAII.

private:
    boost::contract::aux::check_base* check_;
};

} } // namespace

#endif // #include guard

