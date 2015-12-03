
#ifndef BOOST_CONTRACT_GUARD_HPP_
#define BOOST_CONTRACT_GUARD_HPP_

/** @file */

#include <boost/contract/core/set_precondition_old_postcondition.hpp>
#include <boost/contract/core/set_old_postcondition.hpp>
#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/condition/check_base.hpp>
#include <boost/contract/aux_/auto_ptr.hpp>
#include <boost/contract/aux_/debug.hpp>
/** @cond */
#include <boost/noncopyable.hpp>
#include <boost/config.hpp>
/** @endcond */

/* PRIVATE */

#define BOOST_CONTRACT_GUARD_CTOR_(contract_type) \
    /* implicit */ guard(contract_type const& contract) : \
            check_(const_cast<contract_type&>(contract).check_.release()) { \
        BOOST_CONTRACT_AUX_DEBUG(check_); \
        check_->guard(); \
    }

/* CODE */

namespace boost { namespace contract {

class guard { // Copyable as * (OK also for RAII).
public:
    // Following all implicit to allow syntax `guard c = ...`.
    
    template<typename R>
    BOOST_CONTRACT_GUARD_CTOR_(set_precondition_old_postcondition<R>)
    
    template<typename R>
    BOOST_CONTRACT_GUARD_CTOR_(set_old_postcondition<R>)
    
    template<typename R>
    BOOST_CONTRACT_GUARD_CTOR_(set_postcondition_only<R>)
    
    BOOST_CONTRACT_GUARD_CTOR_(set_nothing)

    ~guard() BOOST_NOEXCEPT_IF(false) {}

private:
    boost::contract::aux::auto_ptr<boost::contract::aux::check_base> check_;
};

} } // namespace

#endif // #include guard

