
#ifndef BOOST_CONTRACT_SET_PRECONDITION_ONLY_HPP_
#define BOOST_CONTRACT_SET_PRECONDITION_ONLY_HPP_

#include <boost/contract/set/nothing.hpp>
#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/shared_ptr.hpp>

namespace boost {
    namespace contract {
        class type;

        namespace set {
            class precondition_postcondition;
        }
    }
}

namespace boost { namespace contract { namespace set {

class precondition_only {
public:
    template<typename Precondition>
    boost::contract::set::nothing precondition(Precondition const& f) {
        contract_->set_pre(f);
        return boost::contract::set::nothing(contract_);
    }
    
private:
    explicit precondition_only(boost::shared_ptr<boost::contract::aux::
            check::pre_post> const contract) : contract_(contract) {}

    /* implicit */ precondition_only(precondition_only const& other) :
            contract_(other.contract_) {}
    precondition_only& operator=(precondition_only const&) /* = delete */;
    precondition_only() /* = delete */;

    boost::shared_ptr<boost::contract::aux::check::pre_post> contract_;
    
    // Use friendship and deleted constructors to limit public API.
    
    friend class boost::contract::type;
    friend class boost::contract::set::precondition_postcondition;
};

} } } // namespace

#endif // #include guard

