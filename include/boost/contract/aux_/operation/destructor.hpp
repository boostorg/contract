
#ifndef BOOST_CONTRACT_AUX_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_AUX_DESTRUCTOR_HPP_

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post_inv.hpp>
#include <boost/contract/aux_/check_guard.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/config.hpp>
#include <exception>

namespace boost { namespace contract { namespace aux {

// Dtor subcontracting impl via C++ obj destruction mechanism.
template<class C>
class destructor :
        public check_pre_post_inv</* R = */ none, C> { // Non-copyable base.
public:
    explicit destructor(C* obj) : check_pre_post_inv</* R = */ none, C>(
            boost::contract::from_destructor, obj) {}

private:
    #if BOOST_CONTRACT_ENTRY_INVARIANTS || BOOST_CONTRACT_POSTCONDITIONS
        void init() /* override */ {
            if(check_guard::checking()) return;

            #if BOOST_CONTRACT_ENTRY_INVARIANTS
                {
                    check_guard checking;
                    // Obj exists (before dtor body), check static and non- inv.
                    this->check_entry_inv();
                    // Dtor cannot have pre because it has no parameters.
                }
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                this->copy_old();
            #endif
        }
    #endif
    
public:
    #if BOOST_CONTRACT_EXIT_INVARIANTS || BOOST_CONTRACT_POSTCONDITIONS
        ~destructor() BOOST_NOEXCEPT_IF(false) {
            this->assert_guarded();
            if(check_guard::checking()) return;
            check_guard checking;

            // If dtor body threw, obj still exists so check subcontracted
            // static and non- inv (but no post because of throw). Otherwise,
            // obj destructed so check static inv and post (even if there is no
            // obj after dtor body, this library allows dtor post, for example
            // to check static members for an instance counter class).
            // NOTE: In theory C++ destructors should not throw, but the
            // language allows for that (even if in C++11 dtors declarations are
            // implicitly noexcept(true) unless specified otherwise) so this
            // library must handle such a case.
            bool body_threw = std::uncaught_exception();
            
            #if BOOST_CONTRACT_EXIT_INVARIANTS
                if(body_threw) this->check_exit_inv();
                else this->check_exit_static_inv();
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                if(!body_threw) this->check_post(none());
            #endif
        }
    #endif
};

} } } // namespace

#endif // #include guard

