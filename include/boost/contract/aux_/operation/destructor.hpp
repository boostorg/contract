
#ifndef BOOST_CONTRACT_AUX_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_AUX_DESTRUCTOR_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post_inv.hpp>
#include <boost/contract/aux_/check_guard.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <exception>
/** @endcond */

namespace boost { namespace contract { namespace aux {

// Dtor subcontracting impl via C++ obj destruction mechanism.
template<class C>
class destructor : public check_pre_post_inv</* R = */ none, C> {
public:
    explicit destructor(C* obj) :
        check_pre_post_inv</* R = */ none, C>(
                boost::contract::from_destructor, obj)
    {
        BOOST_CONTRACT_AUX_CHECK_GUARD_OR_RETURN
        // Obj exists (before dtor body) so check static and non-static inv.
        this->check_entry_inv();
    }

    // Dtor cannot have pre because it has no parameters.
    
    ~destructor() {
        BOOST_CONTRACT_AUX_CHECK_GUARD_OR_RETURN
        // If dtor body threw, obj still exists so check subcontracted static
        // and non-static inv (but no post because of throw). Otherwise, obj
        // destructed so check static inv and post (even if there is no obj
        // after dtor body, this library allows dtor post, for example to check
        // static members for an instance counter class).
        // NOTE: In theory C++ destructors should not throw, but the language
        // allows for that so this library must handle such a case.
        if(std::uncaught_exception()) {
            this->check_exit_inv();
        } else {
            this->check_exit_static_inv();
            this->check_post();
        }
    }
};

} } } // namespace

#endif // #include guard

