
#ifndef BOOST_CONTRACT_SET_PRECONDITION_ONLY_HPP_
#define BOOST_CONTRACT_SET_PRECONDITION_ONLY_HPP_

#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/shared_ptr.hpp>

namespace boost { namespace contract {

class set_precondition_only { // Allow (shallow ptr) copy for `auto c = ...`.
public:
    template<typename Precondition>
    boost::contract::set_nothing precondition(Precondition const& f) {
        contract_->set_pre(f);
        return boost::contract::set_nothing(contract_);
    }
    
private:
    // Use friendship and deleted constructors to limit public API.
    friend class var;
    friend class set_precondition_postcondition;

    explicit set_precondition_only(boost::shared_ptr<boost::contract::aux::
            check::pre_post> const contract) : contract_(contract) {}

    boost::shared_ptr<boost::contract::aux::check::pre_post> contract_;
};

} } // namespace

#endif // #include guard

