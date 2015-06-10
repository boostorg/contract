
#ifndef BOOST_CONTRACT_GUARD_HPP_
#define BOOST_CONTRACT_GUARD_HPP_

/** @file */

#include <boost/contract/core/set_precondition_postcondition.hpp>
#include <boost/contract/core/set_precondition_only.hpp>
#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/check/check_pre_only.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
/** @endcond */

namespace boost { namespace contract {

class guard { // Copyable as shared * (OK also for RAII).
public:
    // All implicit to allow `guard c = ...`.
    
    template<typename R>
    /* implicit */ guard(set_precondition_postcondition<R> const& contract) :
            check_(contract.check_) {}

    /* implicit */ guard(set_precondition_only const& contract) :
            check_(contract.check_) {}
    
    template<typename R>
    /* implicit */ guard(set_postcondition_only<R> const& contract) :
            check_(contract.check_) {}
    
    /* implicit */ guard(set_nothing const& contract) :
            check_(contract.check_) {}

private:
    boost::shared_ptr<boost::contract::aux::check_pre_only> check_;
};

} } // namespace

#endif // #include guard

