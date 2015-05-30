
#ifndef BOOST_CONTRACT_AUX_PUBLIC_MEMBER_HPP_
#define BOOST_CONTRACT_AUX_PUBLIC_MEMBER_HPP_

#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/condition/check_subcontracted_pre_post_inv.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
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
        this->copy_subcontracted_oldof();
        this->check_subcontracted_entry_inv();
        if(this->base_call()) { // Throw no_error so not in dtor.
            this->check_subcontracted_exit_inv();
        }
    }

private:
    void pre_available() /* override */ { this->check_subcontracted_pre(); }

    void post_available() /* override */ {
        // Body did not throw.
        if(this->base_call() && !std::uncaught_exception()) {
            this->check_subcontracted_post(); // Throw no_error so not in dtor.
        }
    }
    
public:
    ~public_member() {
        // Body didn't throw.
        if(!this->base_call() && !std::uncaught_exception()) {
            this->check_subcontracted_exit_inv();
            this->check_subcontracted_post();
        }
    }
};

} } } // namespace

#endif // #include guard

