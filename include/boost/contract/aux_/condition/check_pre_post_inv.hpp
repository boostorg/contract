
#ifndef BOOST_CONTRACT_AUX_CHECK_PRE_POST_INV_HPP_
#define BOOST_CONTRACT_AUX_CHECK_PRE_POST_INV_HPP_

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
#include <boost/contract/aux_/type_traits/invariant.hpp>
#include <boost/contract/aux_/debug.hpp>
/** @cond */
#include <boost/mpl/bool.hpp>
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost { namespace contract { namespace aux {

template<typename R, class C>
class check_pre_post_inv : public check_pre_post<R> { // Copyable (as *).
public:
    // obj can be 0 for static member functions.
    explicit check_pre_post_inv(boost::contract::from from, C* obj) :
            check_pre_post<R>(from), obj_(obj) {}
    
    virtual ~check_pre_post_inv() {}

protected:
    void check_exit_inv() { check_inv(false, false); }
    void check_entry_inv() { check_inv(true, false); }

    void check_entry_static_inv() { check_inv(true, true); }
    void check_exit_static_inv() { check_inv(false, true); }

    C* object() { return obj_; }

private:
    void check_inv(bool on_entry, bool static_inv_only) {
        check_static_inv(on_entry, boost::mpl::bool_<
                has_static_invariant<C>::value>());
        if(!static_inv_only) {
            check_const_inv(on_entry, boost::mpl::bool_<
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
        BOOST_CONTRACT_AUX_DEBUG(obj_);
        try { obj_->BOOST_CONTRACT_CONFIG_INVARIANT(); }
        catch(...) {
            if(on_entry) {
                boost::contract::const_entry_invariant_failed(from());
            } else {
                boost::contract::const_exit_invariant_failed(from());
            }
        }
    }

    // TODO: Add support for volatile member functions and class invariants.

    C* obj_;
};

} } }

#endif // #include guard

