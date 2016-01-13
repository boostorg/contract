
#ifndef BOOST_CONTRACT_AUX_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_AUX_CONSTRUCTOR_HPP_

#include <boost/contract/core/config.hpp>
#if BOOST_CONTRACT_POSTCONDITIONS || BOOST_CONTRACT_INVARIANTS
    #include <boost/contract/aux_/check_guard.hpp>
    #include <exception>
#endif
#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post_inv.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/config.hpp>

namespace boost { namespace contract { namespace aux {

// Ctor subcontracting impl via C++ obj construction mechanism.
template<class C>
class constructor :
        public check_pre_post_inv</* R = */ none, C> { // Non-copyable base.
public:
    explicit constructor(C* obj) : check_pre_post_inv</* R = */ none, C>(
            boost::contract::from_constructor, obj) {}

private:
    #if BOOST_CONTRACT_ENTRY_INVARIANTS || BOOST_CONTRACT_POSTCONDITIONS
        void init() /* override */ {
            if(check_guard::checking()) return;

            #if BOOST_CONTRACT_ENTRY_INVARIANTS
                {
                    check_guard checking;
                    this->check_entry_static_inv();
                    // No object before ctor body so check only static inv at
                    // entry. Ctor pre checked by constructor_precondition.
                }
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                this->copy_old();
            #endif
        }
    #endif

public:
    #if BOOST_CONTRACT_EXIT_INVARIANTS || BOOST_CONTRACT_POSTCONDITIONS
        ~constructor() BOOST_NOEXCEPT_IF(false) {
            this->assert_guarded();
            if(check_guard::checking()) return;
            check_guard checking;
            // If ctor body threw, no obj so check only static inv. Otherwise,
            // obj constructed so check static inv, non-static inv, and post.
            bool body_threw = std::uncaught_exception();

            #if BOOST_CONTRACT_EXIT_INVARIANTS
                if(body_threw) this->check_exit_static_inv();
                else this->check_exit_inv();
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                if(!body_threw) this->check_post(none());
            #endif
        }
    #endif
};

} } } // namespace

#endif // #include guard

