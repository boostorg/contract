
#ifndef BOOST_CONTRACT_TYPE_HPP_
#define BOOST_CONTRACT_TYPE_HPP_

#include <boost/contract/aux_/set/pre_post.hpp>
#include <boost/contract/aux_/set/pre_only.hpp>
#include <boost/contract/aux_/set/pre_only.hpp>
#include <boost/contract/aux_/set/nothing.hpp>
#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/shared_ptr.hpp>

namespace boost { namespace contract {

class type { // This can be copied (as shallow smart pointer copy).
public:
    /* implicit */ type(boost::contract::aux::set::pre_post const& pre_post) :
            contract_(pre_post.contract_) {}
    
    /* implicit */ type(boost::contract::aux::set::pre_only const& pre_only) :
            contract_(pre_only.contract_) {}
    
    /* implicit */ type(boost::contract::aux::set::post_only const& post_only) :
            contract_(post_only.contract_) {}

    /* implicit */ type(boost::contract::aux::set::nothing const& nothing) :
            contract_(nothing.contract_) {}

private:
    boost::shared_ptr<boost::contract::aux::check::pre_post> contract_;
};

} } // namespace

#endif // #include guard

