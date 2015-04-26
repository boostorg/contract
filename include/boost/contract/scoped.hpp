
#ifndef BOOST_CONTRACT_SCOPED_HPP_
#define BOOST_CONTRACT_SCOPED_HPP_

#include <boost/contract/set/precondition_postcondition.hpp>
#include <boost/contract/set/precondition_only.hpp>
#include <boost/contract/set/precondition_only.hpp>
#include <boost/contract/set/nothing.hpp>
#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/shared_ptr.hpp>

namespace boost { namespace contract {

class scoped { // Allow (shallow ptr) copy for `scoped c = ...`.
public:
    /* implicit */ scoped(boost::contract::set::precondition_postcondition
            const& c) : contract_(c.contract_) {}
    
    /* implicit */ scoped(boost::contract::set::precondition_only
            const& c) : contract_(c.contract_) {}
    
    /* implicit */ scoped(boost::contract::set::postcondition_only
            const& c) : contract_(c.contract_) {}

    /* implicit */ scoped(boost::contract::set::nothing
            const& c) : contract_(c.contract_) {}

private:
    boost::shared_ptr<boost::contract::aux::check::pre_post> contract_;
};

} } // namespace

#endif // #include guard

