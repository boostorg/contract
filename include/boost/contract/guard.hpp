
#ifndef BOOST_CONTRACT_GUARD_HPP_
#define BOOST_CONTRACT_GUARD_HPP_

/** @file */

#include <boost/contract/core/set_precondition_old_postcondition.hpp>
#include <boost/contract/core/set_old_postcondition.hpp>
#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/condition/check_base.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
/** @endcond */

namespace boost { namespace contract {

class guard { // Copyable as shared * (OK also for RAII).
public:
    // All implicit to allow `guard c = ...`.
    
    template<typename R>
    /* implicit */ guard(set_precondition_old_postcondition<R> const& contract)
            : check_(contract.check_) { check_->guard(); }
    
    template<typename R>
    /* implicit */ guard(set_old_postcondition<R> const& contract)
            : check_(contract.check_) { check_->guard(); }
    
    template<typename R>
    /* implicit */ guard(set_postcondition_only<R> const& contract)
            : check_(contract.check_) { check_->guard(); }
    
    /* implicit */ guard(set_nothing const& contract)
            : check_(contract.check_) { check_->guard(); }

private:
    boost::shared_ptr<boost::contract::aux::check_base> check_;
};

} } // namespace

#endif // #include guard

