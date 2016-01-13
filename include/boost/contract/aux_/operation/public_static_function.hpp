
#ifndef BOOST_CONTRACT_AUX_PUBLIC_STATIC_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_PUBLIC_STATIC_FUNCTION_HPP_

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post_inv.hpp>
#include <boost/contract/aux_/check_guard.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/config.hpp>
#include <exception>

namespace boost { namespace contract { namespace aux {

// No subcontracting because static so no obj and no substitution principle.
template<class C>
class public_static_function :
        public check_pre_post_inv</* R = */ none, C> { // Non-copyable base.
public:
    explicit public_static_function() :
        check_pre_post_inv</* R = */ none, C>(boost::contract::from_function,
                /* obj = */ 0)
    {}

private:
    #if BOOST_CONTRACT_ENTRY_INVARIANTS || BOOST_CONTRACT_PRECONDITIONS || \
            BOOST_CONTRACT_POSTCONDITIONS
        void init() /* override */ {
            if(check_guard::checking()) return;
            #if BOOST_CONTRACT_ENTRY_INVARIANTS || BOOST_CONTRACT_PRECONDITIONS
                {
                    check_guard checking;
                    #if BOOST_CONTRACT_ENTRY_INVARIANTS
                        this->check_entry_static_inv();
                    #endif
                    #if BOOST_CONTRACT_PRECONDITIONS
                        this->check_pre();
                    #endif
                }
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                this->copy_old();
            #endif
        }
    #endif

public:
    #if BOOST_CONTRACT_EXIT_INVARIANTS || BOOST_CONTRACT_POSTCONDITIONS
        ~public_static_function() BOOST_NOEXCEPT_IF(false) {
            this->assert_guarded();
            if(check_guard::checking()) return;
            check_guard checking;

            #if BOOST_CONTRACT_EXIT_INVARIANTS
                this->check_exit_static_inv();
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                if(!std::uncaught_exception()) this->check_post(none());
            #endif
        }
    #endif
};

} } } // namespace

#endif // #include guard

