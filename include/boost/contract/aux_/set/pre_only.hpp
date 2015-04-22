
#ifndef BOOST_CONTRACT_AUX_SET_PRE_ONLY_HPP_
#define BOOST_CONTRACT_AUX_SET_PRE_ONLY_HPP_

#include <boost/contract/aux_/set/nothing.hpp>
#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/shared_ptr.hpp>

namespace boost {
    namespace contract {
        class type;
    }
}

namespace boost { namespace contract { namespace aux { namespace set {

class pre_only {
public:
    explicit pre_only(boost::shared_ptr<boost::contract::aux::check::pre_post>
            const contract) : contract_(contract) {}

    template<typename Pre>
    boost::contract::aux::set::nothing precondition(Pre const& pre) {
        contract_->set_pre(pre);
        return boost::contract::aux::set::nothing(contract_);
    }
    
private:
    friend class boost::contract::type;
    boost::shared_ptr<boost::contract::aux::check::pre_post> contract_;
};

} } } } // namespace

#endif // #include guard

