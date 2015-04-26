
#ifndef BOOST_CONTRACT_SET_POSTCONDITION_ONLY_HPP_
#define BOOST_CONTRACT_SET_POSTCONDITION_ONLY_HPP_

#include <boost/contract/set/nothing.hpp>
#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/shared_ptr.hpp>

namespace boost {
    namespace contract {
        class scoped;

        template<class Class>
        boost::contract::set::postcondition_only constructor(Class* const);
        
        template<class Class>
        boost::contract::set::postcondition_only destructor(Class* const);
        
        namespace set {
            class precondition_postcondition;
        }
    }
}

namespace boost { namespace contract { namespace set {

class postcondition_only { // Allow (shallow ptr) copy for `auto c = ...`.
public:
    template<typename Postcondition>
    boost::contract::set::nothing postcondition(Postcondition const& f) {
        contract_->set_post(f);
        return boost::contract::set::nothing(contract_);
    }
    
private:
    // Use friendship and deleted constructors to limit public API.
    friend class boost::contract::scoped;
    friend class boost::contract::set::precondition_postcondition;
    
    template<class Class>
    friend postcondition_only boost::contract::constructor(Class* const);
    
    template<class Class>
    friend postcondition_only boost::contract::destructor(Class* const);

    explicit postcondition_only(boost::shared_ptr<boost::contract::aux::
            check::pre_post> const contract) : contract_(contract) {}
            
    boost::shared_ptr<boost::contract::aux::check::pre_post> contract_;
};

} } } // namespace

#endif // #include guard

