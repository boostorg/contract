
#ifndef BOOST_CONTRACT_AUX_PUBLIC_MEMBER_HPP_
#define BOOST_CONTRACT_AUX_PUBLIC_MEMBER_HPP_

#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/condition/check_subcontracted_pre_post_inv.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/contract/aux_/check_guard.hpp>
/** @cond */
#include <exception>
/** @endcond */

namespace boost { namespace contract { namespace aux {

template<class O, typename R, typename F, class C, typename A0>
class public_member : public check_subcontracted_pre_post_inv<O, R, F, C, A0> {
public:
    explicit public_member(boost::contract::virtual_* v, C* obj, R& r, A0& a0) :
        check_subcontracted_pre_post_inv<O, R, F, C, A0>(
                boost::contract::from_public_member, v, obj, r, a0)
    {
        BOOST_CONTRACT_AUX_SUBCONTRACTED_CHECK_GUARD_OR_RETURN
        this->copy_subcontracted_oldof();
        this->check_subcontracted_entry_inv();
        if(this->base_call()) { // Throw no_error so not in dtor.
            this->check_subcontracted_exit_inv();
        }
    }

private:
    void pre_available() /* override */ {
        BOOST_CONTRACT_AUX_SUBCONTRACTED_CHECK_GUARD_OR_RETURN
        this->check_subcontracted_pre();
    }

    void post_available() /* override */ {
        BOOST_CONTRACT_AUX_SUBCONTRACTED_CHECK_GUARD_OR_RETURN
        if(this->base_call() && !std::uncaught_exception()) {
            this->check_subcontracted_post(); // Throw no_error so not in dtor.
        }
    }
    
public:
    ~public_member() {
        BOOST_CONTRACT_AUX_SUBCONTRACTED_CHECK_GUARD_OR_RETURN
        if(!this->base_call()) {
            this->check_subcontracted_exit_inv();
            if(!std::uncaught_exception()) this->check_subcontracted_post();
        }
    }
};
        
} } } // namespace

#endif // #include guard

