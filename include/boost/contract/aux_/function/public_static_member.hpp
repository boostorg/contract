
#ifndef BOOST_CONTRACT_AUX_FUNCTION_PUBLIC_STATIC_MEMBER_HPP_
#define BOOST_CONTRACT_AUX_FUNCTION_PUBLIC_STATIC_MEMBER_HPP_

#include <boost/contract/aux_/check/pre_post_inv.hpp>
#include <exception>

namespace boost { namespace contract { namespace aux { namespace function {

template<class Class> class public_static_member :
        public boost::contract::aux::check::pre_post_inv<Class> {
public:
    explicit public_static_member() :
            boost::contract::aux::check::pre_post_inv<Class>() {
        entry();
    }
    
    ~public_static_member() { exit(); }
    
private:
    // Static members have no object so they do not participate in virtual
    // function polymorphism according to substitution principle (so no
    // subcontracting for any of the checks below).

    // Static so no object so check static inv only.
    void entry() { this->check_inv(/* static_inv_only = */ true); }

    // Check pre (as soon as related functor set).
    void pre_available() /* override */ { this->check_pre(); }
    
    // Post always checked after body, at exit (see below).
    void post_available() /* override */ {}
    
    // Static so no object and only static inv checked, plus check post but
    // only if body did not throw.
    void exit() {
        bool const body_threw = std::uncaught_exception();
        this->check_inv(/* static_inv_only = */ true);
        if(!body_threw) this->check_post();
    }
};

} } } } // namespace

#endif // #include guard

