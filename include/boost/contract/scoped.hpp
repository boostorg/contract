
#ifndef BOOST_CONTRACT_SCOPED_HPP_
#define BOOST_CONTRACT_SCOPED_HPP_

/** @file */

#include <boost/contract/core/set_precondition_postcondition.hpp>
#include <boost/contract/core/set_precondition.hpp>
#include <boost/contract/core/set_postcondition.hpp>
#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/condition/check_nothing.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost { namespace contract {

class scoped { // Copyable (shallow shared ptr copies).
public:
    // All implicit to allow `scoped c = ...`.
    
    /* implicit */ scoped(boost::contract::set_precondition_postcondition
            const& contract) : check_(contract.check_) {}

    /* implicit */ scoped(boost::contract::set_precondition
            const& contract) : check_(contract.check_) {}
    
    /* implicit */ scoped(boost::contract::set_postcondition
            const& contract) : check_(contract.check_) {}
    
    /* implicit */ scoped(boost::contract::set_nothing
            const& contract) : check_(contract.check_) {}

private:
    boost::shared_ptr<boost::contract::aux::check_nothing> check_;
};

} } // namespace

#endif // #include guard

