
#ifndef BOOST_CONTRACT_AUX_PUBLIC_MEMBER_HPP_
#define BOOST_CONTRACT_AUX_PUBLIC_MEMBER_HPP_

#include <boost/contract/aux_/call.hpp>
#include <boost/contract/aux_/condition/check_subcontracted_pre_post_inv.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
#include <exception>
/** @endcond */

namespace boost { namespace contract { namespace aux {

template<class I, class C, typename A0>
class public_member : public boost::contract::aux::
        check_subcontracted_pre_post_inv<I, C, A0> {
public:
    explicit public_member(C const* obj, A0 const& a0) :
        boost::contract::aux::check_subcontracted_pre_post_inv<I, C, A0>(
                boost::contract::from_public_member, obj, a0)
    { init(); }
    
    explicit public_member(boost::shared_ptr<boost::contract::aux::call> call,
            C const* obj, A0 const& a0) :
        boost::contract::aux::check_subcontracted_pre_post_inv<I, C, A0>(
                boost::contract::from_public_member, call, obj, a0)
    { init(); }

private:
    void init() {
        this->copy_subcontracted_oldof();
        this->check_subcontracted_entry_inv();
        // Throw (so not in dtor).
        if(this->contract_call()) this->check_subcontracted_exit_inv();
    }

    void pre_available() /* override */ { this->check_subcontracted_pre(); }

    void post_available() /* override */ {
        // Body did not throw.
        if(this->contract_call() && !std::uncaught_exception()) {
            // Throw no_error (so not in dtor).
            this->check_subcontracted_post();
        }
    }
    
public:
    ~public_member() {
        // Body didn't throw.
        if(!this->contract_call() && !std::uncaught_exception()) {
            this->check_subcontracted_exit_inv();
            this->check_subcontracted_post();
        }
    }
};

} } } // namespace

#endif // #include guard

