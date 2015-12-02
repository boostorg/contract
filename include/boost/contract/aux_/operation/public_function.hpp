
#ifndef BOOST_CONTRACT_AUX_PUBLIC_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_PUBLIC_FUNCTION_HPP_

#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/condition/check_subcontracted_pre_post_inv.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/contract/aux_/check_guard.hpp>
/** @cond */
#include <boost/config.hpp>
#include <exception>
/** @endcond */

namespace boost { namespace contract { namespace aux {

template<class O, typename R, typename F, class C, typename A0, typename A1>
class public_function :
        public check_subcontracted_pre_post_inv<O, R, F, C, A0, A1> {
public:
    explicit public_function(boost::contract::virtual_* v, C* obj, R& r,
            A0& a0, A1& a1) :
        check_subcontracted_pre_post_inv<O, R, F, C, A0, A1>(
                boost::contract::from_function, v, obj, r, a0, a1)
    {}

private:
    void init() /* override */ {
        this->init_subcontracted_old();
        if(!this->base_call()) {
            if(check_guard::checking()) return;
            {
                check_guard checking;
                this->check_subcontracted_entry_inv();
                this->check_subcontracted_pre();
            }
            this->copy_subcontracted_old();
        } else {
            this->check_subcontracted_entry_inv();
            this->check_subcontracted_pre();
            this->copy_subcontracted_old();
            this->check_subcontracted_exit_inv();
            if(!std::uncaught_exception()) this->check_subcontracted_post();
        }
    }

public:
    ~public_function() BOOST_NOEXCEPT_IF(false) {
        this->assert_guarded();
        if(!this->base_call()) {
            if(check_guard::checking()) return;
            check_guard checking;
            this->check_subcontracted_exit_inv();
            if(!std::uncaught_exception()) this->check_subcontracted_post();
        }
    }
};
        
} } } // namespace

#endif // #include guard

