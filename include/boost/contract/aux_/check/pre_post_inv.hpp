
#ifndef BOOST_CONTRACT_AUX_CHECK_PRE_POST_INV_HPP_
#define BOOST_CONTRACT_AUX_CHECK_PRE_POST_INV_HPP_

#include <boost/contract/config.hpp>
#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/contract/aux_/type_traits/invariant.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace contract { namespace aux { namespace check {

template<class Class>
class pre_post_inv : public boost::contract::aux::check::pre_post {
public:
    // Allow object to be 0 (i.e., no object), for static members.
    explicit pre_post_inv(Class* const obj = 0) : obj_(obj) {}
    
protected:
    void check_inv(bool const static_inv_only = false) {
        check_static_inv(boost::mpl::bool_<boost::contract::aux::type_traits::
                has_static_invariant<Class>::value>());
        if(!static_inv_only) {
            check_cv_inv(boost::mpl::bool_<boost::contract::aux::type_traits::
                    has_const_invariant<Class>::value>());
        }
    }

    // Could return null pointer (for static members).
    Class* const object() const { return obj_; }

private:
    void check_static_inv(boost::mpl::false_ const&) {}
    void check_static_inv(boost::mpl::true_ const&) {
        Class::BOOST_CONTRACT_CONFIG_STATIC_INVARIANT();
    }
        
    void check_cv_inv(boost::mpl::false_ const&) {}
    void check_cv_inv(boost::mpl::true_ const&) {
        typename boost::add_const<Class>::type* const const_obj = obj_;
        BOOST_CONTRACT_AUX_DEBUG(const_obj);
        const_obj->BOOST_CONTRACT_CONFIG_INVARIANT();
    }
            
    Class* const obj_;
};

} } } } // namespace

#endif // #include guard

