
#ifndef BOOST_CONTRACT_AUX_PUBLIC_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_PUBLIC_FUNCTION_HPP_

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/condition/check_subcontracted_pre_post_inv.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/contract/aux_/check_guard.hpp>
#include <boost/config.hpp>
#include <exception>

namespace boost { namespace contract { namespace aux {

template<class O, typename R, typename F, class C, typename A0, typename A1>
class public_function :
    // Non-copyable base.
    public check_subcontracted_pre_post_inv<O, R, F, C, A0, A1>
{
public:
    explicit public_function(boost::contract::virtual_* v, C* obj, R& r,
            A0& a0, A1& a1) :
        check_subcontracted_pre_post_inv<O, R, F, C, A0, A1>(
                boost::contract::from_function, v, obj, r, a0, a1)
    {}

private:
    void init() /* override */ {
        #if BOOST_CONTRACT_POSTCONDITIONS
            this->init_subcontracted_old();
        #endif
        if(!this->base_call()) {
            #if BOOST_CONTRACT_ENTRY_INVARIANTS || BOOST_CONTRACT_PRECONDITIONS\
                    || BOOST_CONTRACT_POSTCONDITIONS
                if(check_guard::checking()) return;
                {
                    check_guard checking;
                    #if BOOST_CONTRACT_ENTRY_INVARIANTS
                        this->check_subcontracted_entry_inv();
                    #endif
                    #if BOOST_CONTRACT_PRECONDITIONS
                        this->check_subcontracted_pre();
                    #endif
                }
                #if BOOST_CONTRACT_POSTCONDITIONS
                    this->copy_subcontracted_old();
                #endif
            #endif
        } else {
            #if BOOST_CONTRACT_INVARIANTS || BOOST_CONTRACT_PRECONDITIONS || \
                    BOOST_CONTRACT_POSTCONDITIONS
                #if BOOST_CONTRACT_ENTRY_INVARIANTS
                    this->check_subcontracted_entry_inv();
                #endif
                #if BOOST_CONTRACT_PRECONDITIONS
                    this->check_subcontracted_pre();
                #endif
                #if BOOST_CONTRACT_POSTCONDITIONS
                    this->copy_subcontracted_old();
                #endif
                #if BOOST_CONTRACT_EXIT_INVARIANTS
                    this->check_subcontracted_exit_inv();
                #endif
                #if BOOST_CONTRACT_POSTCONDITIONS
                    if(!std::uncaught_exception()) {
                        this->check_subcontracted_post();
                    }
                #endif
            #endif
        }
    }

public:
    ~public_function() BOOST_NOEXCEPT_IF(false) {
        this->assert_guarded();
        #if BOOST_CONTRACT_EXIT_INVARIANTS || BOOST_CONTRACT_POSTCONDITIONS
            if(!this->base_call()) {
                if(check_guard::checking()) return;
                check_guard checking;

                #if BOOST_CONTRACT_EXIT_INVARIANTS
                    this->check_subcontracted_exit_inv();
                #endif
                #if BOOST_CONTRACT_POSTCONDITIONS
                    if(!std::uncaught_exception()) {
                        this->check_subcontracted_post();
                    }
                #endif
            }
        #endif
    }
};
        
} } } // namespace

#endif // #include guard

