
#ifndef BOOST_CONTRACT_AUX_SET_PRE_POST_HPP_
#define BOOST_CONTRACT_AUX_SET_PRE_POST_HPP_

#include <boost/contract/aux_/set/pre_only.hpp>
#include <boost/contract/aux_/set/post_only.hpp>
#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/shared_ptr.hpp>

namespace boost {
    namespace contract {
        class type;
    }
}

namespace boost { namespace contract { namespace aux { namespace set {

class pre_post {
public:
    explicit pre_post(boost::shared_ptr<boost::contract::aux::check::pre_post>
            const contract) : contract_(contract) {}

    template<typename Pre>
    boost::contract::aux::set::post_only precondition(Pre const& pre) {
        contract_->set_pre(pre);
        return boost::contract::aux::set::post_only(contract_);
    }
    
    template<typename Post>
    boost::contract::aux::set::pre_only postcondition(Post const& post) {
        contract_->set_post(post);
        return boost::contract::aux::set::pre_only(contract_);
    }

private:
    friend class boost::contract::type;
    boost::shared_ptr<boost::contract::aux::check::pre_post> contract_;
};

} } } } // namespace

#endif // #include guard

