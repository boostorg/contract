
#ifndef BOOST_CONTRACT_SET_POSTCONDITION_ONLY_HPP_
#define BOOST_CONTRACT_SET_POSTCONDITION_ONLY_HPP_

#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/shared_ptr.hpp>

namespace boost { namespace contract {

class set_postcondition_only { // Allow (shallow ptr) copy for `auto c = ...`.
public:
    template<typename Postcondition>
    boost::contract::set_nothing postcondition(Postcondition const& f) {
        contract_->set_post(f);
        return boost::contract::set_nothing(contract_);
    }
    
private:
    // Use friendship and deleted constructors to limit public API.
    friend class var;
    friend class set_precondition_postcondition;
    
    template<class Class>
    friend set_postcondition_only constructor(Class* const);
    
    template<class Class>
    friend set_postcondition_only destructor(Class* const);

    explicit set_postcondition_only(boost::shared_ptr<boost::contract::aux::
            check::pre_post> const contract) : contract_(contract) {}
            
    boost::shared_ptr<boost::contract::aux::check::pre_post> contract_;
};

} } // namespace

#endif // #include guard

