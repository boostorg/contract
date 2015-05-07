
#ifndef BOOST_CONTRACT_AUX_CHECK_PRE_POST_INV_HPP_
#define BOOST_CONTRACT_AUX_CHECK_PRE_POST_INV_HPP_

#include <boost/contract/core/config.hpp>
#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/contract/aux_/exception.hpp>
#include <boost/contract/aux_/type_traits/invariant.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace contract { namespace aux { namespace check {

template<class Class>
class pre_post_inv : public boost::contract::aux::check::pre_post {
public:
    // Allow object to be 0 (i.e., no object), for static members.
    explicit pre_post_inv(boost::contract::from const& from,
            Class* const obj = 0) : 
        boost::contract::aux::check::pre_post(from),
        obj_(obj)
    {}

    virtual ~pre_post_inv() {}
    
protected:
    void check_entry_inv(bool const static_inv_only = false) {
        check_inv(/* on_entry = */ true, static_inv_only);
    }
    
    void check_exit_inv(bool const static_inv_only = false) {
        check_inv(/* on_entry = */ false, static_inv_only);
    }

    // Could return null pointer (for static members).
    Class* const object() const { return obj_; }

private:
    void check_inv(bool const on_entry, bool const static_inv_only = false) {
        check_static_inv(on_entry, boost::mpl::bool_<boost::contract::aux::
                type_traits::has_static_invariant<Class>::value>());
        if(!static_inv_only) {
            check_cv_inv(on_entry, boost::mpl::bool_<boost::contract::aux::
                    type_traits::has_const_invariant<Class>::value>());
        }
    }

    // TODO: Add const volatile invariant checking here.

    void check_static_inv(bool const on_entry, boost::mpl::false_ const&) {}
    void check_static_inv(bool const on_entry, boost::mpl::true_ const&) {
        try { Class::BOOST_CONTRACT_CONFIG_STATIC_INVARIANT(); }
        catch(...) {
            if(on_entry) {
                boost::contract::aux::static_entry_inv_failure_handler(from());
            } else {
                boost::contract::aux::static_entry_inv_failure_handler(from());
            }
        }
    }
        
    void check_cv_inv(bool const on_entry, boost::mpl::false_ const&) {}
    void check_cv_inv(bool const on_entry, boost::mpl::true_ const&) {
        typename boost::add_const<Class>::type* const const_obj = obj_;
        BOOST_CONTRACT_AUX_DEBUG(const_obj);
        try { const_obj->BOOST_CONTRACT_CONFIG_INVARIANT(); }
        catch(...) {
            if(on_entry) {
                boost::contract::aux::const_entry_inv_failure_handler(from());
            } else {
                boost::contract::aux::const_exit_inv_failure_handler(from());
            }
        }
    }

    Class* const obj_;
};

} } } } // namespace

#endif // #include guard

