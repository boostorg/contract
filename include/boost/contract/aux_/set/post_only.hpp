
#ifndef BOOST_CONTRACT_AUX_SET_POST_ONLY_HPP_
#define BOOST_CONTRACT_AUX_SET_POST_ONLY_HPP_

#include <boost/contract/aux_/set/nothing.hpp>
#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/shared_ptr.hpp>

namespace boost {
    namespace contract {
        class type;
    }
}

namespace boost { namespace contract { namespace aux { namespace set {

class post_only {
public:
    explicit post_only(boost::shared_ptr<boost::contract::aux::check::pre_post>
            const contract) : contract_(contract) {}

    template<typename Pre>
    boost::contract::aux::set::nothing postcondition(Pre const& post) {
        contract_->set_post(post);
        return boost::contract::aux::set::nothing(contract_);
    }
    
private:
    friend class boost::contract::type;
    boost::shared_ptr<boost::contract::aux::check::pre_post> contract_;
};

} } } } // namespace

#endif // #include guard

