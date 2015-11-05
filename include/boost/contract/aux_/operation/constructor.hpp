
#ifndef BOOST_CONTRACT_AUX_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_AUX_CONSTRUCTOR_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post_inv.hpp>
#include <boost/contract/aux_/check_guard.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <exception>
/** @endcond */

namespace boost { namespace contract { namespace aux {

// Ctor subcontracting impl via C++ obj construction mechanism.
template<class C>
class constructor : public check_pre_post_inv</* R = */ none, C> {
public:
    explicit constructor(C* obj) :
        check_pre_post_inv</* R = */ none, C>(boost::contract::from_constructor,
                obj)
    {}

private:
    void init() /* override */ {
        if(check_guard::checking()) return;
        {
            check_guard checking;
            this->check_entry_static_inv();
            // No object before ctor body so check only static inv at entry.
            // Ctor pre checked by constructor_precondition.
        }
        this->copy_old();
    }

public:
    ~constructor() {
        this->assert_guarded();
        if(check_guard::checking()) return;
        check_guard checking;
        // If ctor body threw, no obj so check only static inv. Otherwise, obj
        // constructed so check static inv, non-static inv, and post.
        if(std::uncaught_exception()) {
            this->check_exit_static_inv();
        } else {
            this->check_exit_inv();
            this->check_post(none());
        }
    }
};

} } } // namespace

#endif // #include guard

