
#ifndef BOOST_CONTRACT_VAR_HPP_
#define BOOST_CONTRACT_VAR_HPP_

/** @file */

#include <boost/contract/core/set_precondition_postcondition.hpp>
#include <boost/contract/core/set_precondition_only.hpp>
#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/condition/check_base.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost { namespace contract {

class var { // Copyable (as shallow *).
public:
    // All implicit to allow `var contract = ...`.
    
    /* implicit */ var(set_precondition_postcondition const& contract) :
            check_(contract.check_) {}

    /* implicit */ var(set_precondition_only const& contract) :
            check_(contract.check_) {}
    
    /* implicit */ var(set_postcondition_only const& contract) :
            check_(contract.check_) {}
    
    /* implicit */ var(set_nothing const& contract) :
            check_(contract.check_) {}

private:
    boost::shared_ptr<aux::check_base> check_;
};

} } // namespace

#endif // #include guard

