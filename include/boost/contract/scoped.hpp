
#ifndef BOOST_CONTRACT_SCOPED_HPP_
#define BOOST_CONTRACT_SCOPED_HPP_

/** @file */

#include <boost/contract/core/set_precondition_postcondition.hpp>
#include <boost/contract/core/set_precondition_only.hpp>
#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/condition/check_pre_only.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost { namespace contract {

class scoped { // Copyable (as shallow *).
public:
    // All implicit to allow `scoped c = ...`.
    
    template<typename R>
    /* implicit */ scoped(set_precondition_postcondition<R> const& contract) :
            check_(contract.check_) {}

    /* implicit */ scoped(set_precondition_only const& contract) :
            check_(contract.check_) {}
    
    template<typename R>
    /* implicit */ scoped(set_postcondition_only<R> const& contract) :
            check_(contract.check_) {}
    
    /* implicit */ scoped(set_nothing const& contract) :
            check_(contract.check_) {}

private:
    boost::shared_ptr<boost::contract::aux::check_pre_only> check_;
};

} } // namespace

#endif // #include guard

