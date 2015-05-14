
#ifndef BOOST_CONTRACT_AUX_CHECK_PRE_POST_INV_HPP_
#define BOOST_CONTRACT_AUX_CHECK_PRE_POST_INV_HPP_

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
#include <boost/contract/aux_/call.hpp>
#include <boost/contract/aux_/type_traits/invariant.hpp>
#include <boost/contract/aux_/exception.hpp>
/** @cond */
#include <boost/mpl/bool.hpp>
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost { namespace contract { namespace aux {

template<class C>
class check_pre_post_inv : // Copyable (as shallow ptr).
        public boost::contract::aux::check_pre_post {
public:
    explicit check_pre_post_inv(boost::contract::from from, C const* obj) :
            boost::contract::aux::check_pre_post(from), obj_(obj) {}
    
    explicit check_pre_post_inv(boost::contract::from from, boost::shared_ptr<
            boost::contract::aux::call> call, C const* obj) :
        boost::contract::aux::check_pre_post(from, call), obj_(obj)
    {}

    virtual ~check_pre_post_inv() {}

protected:
    void check_entry_inv(bool static_inv_only = false) {
        if(!this->contract_call() || this->contract_call()->action ==
                boost::contract::aux::call::check_entry_inv) {
            check_inv(/* on_entry = */ true, static_inv_only);
            if(this->contract_call()) throw no_error();
        }
    }

    // If call(), can't call from dtor (as throw no_error on OK).
    void check_exit_inv(bool static_inv_only = false) {
        if(!this->contract_call() || this->contract_call()->action ==
                boost::contract::aux::call::check_exit_inv) {
            check_inv(/* on_entry = */ false, static_inv_only);
            if(this->contract_call()) throw no_error();
        }
    }

    C const* object() const { return obj_; }

private:
    void check_inv(bool on_entry, bool static_inv_only) {
        check_static_inv(on_entry, boost::mpl::bool_<boost::contract::aux::
                has_static_invariant<C>::value>());
        if(!static_inv_only) {
            check_const_inv(on_entry, boost::mpl::bool_<boost::contract::aux::
                    has_const_invariant<C>::value>());
        }
    }

    void check_static_inv(bool, boost::mpl::false_ const&) {}
    void check_static_inv(bool on_entry, boost::mpl::true_ const&) {
        try { C::BOOST_CONTRACT_CONFIG_STATIC_INVARIANT(); }
        catch(...) {
            if(on_entry) {
                boost::contract::static_entry_invariant_failed(from());
            } else {
                boost::contract::static_exit_invariant_failed(from());
            }
        }
    }
    
    void check_const_inv(bool, boost::mpl::false_ const&) {}
    void check_const_inv(bool on_entry, boost::mpl::true_ const&) {
        try { obj_->BOOST_CONTRACT_CONFIG_INVARIANT(); }
        catch(...) {
            if(on_entry) {
                boost::contract::const_entry_invariant_failed(from());
            } else {
                boost::contract::const_exit_invariant_failed(from());
            }
        }
    }

    // TODO: Add volatile inv here...

    C const* obj_;
};

} } }

#endif // #include guard

