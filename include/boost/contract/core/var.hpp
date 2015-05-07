
#ifndef BOOST_CONTRACT_VAR_HPP_
#define BOOST_CONTRACT_VAR_HPP_

#include <boost/contract/core/set_precondition_postcondition.hpp>
#include <boost/contract/core/set_precondition_only.hpp>
#include <boost/contract/core/set_precondition_only.hpp>
#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/shared_ptr.hpp>

namespace boost { namespace contract {

class var { // Allow (shallow ptr) copy for `var c = ...`.
public:
    /* implicit */ var(boost::contract::set_precondition_postcondition
            const& c) : contract_(c.contract_) {}
    
    /* implicit */ var(boost::contract::set_precondition_only
            const& c) : contract_(c.contract_) {}
    
    /* implicit */ var(boost::contract::set_postcondition_only
            const& c) : contract_(c.contract_) {}

    /* implicit */ var(boost::contract::set_nothing
            const& c) : contract_(c.contract_) {}

private:
    boost::shared_ptr<boost::contract::aux::check::pre_post> contract_;
};

} } // namespace

#endif // #include guard

