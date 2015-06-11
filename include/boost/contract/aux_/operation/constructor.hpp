
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
    explicit constructor(C* obj) : check_pre_post_inv</* R = */ none, C>(
            boost::contract::from_constructor, obj) {
        BOOST_CONTRACT_AUX_CHECK_GUARD_OR_RETURN
        // No object before ctor body so check only static inv at entry.
        this->check_entry_static_inv();
    }

    // Ctor pre checked by constructor_precondition at start of init list.

    ~constructor() {
        BOOST_CONTRACT_AUX_CHECK_GUARD_OR_RETURN
        // If ctor body threw, no obj so check only static inv. Otherwise, obj
        // constructed so check static inv, non-static inv, and post.
        if(std::uncaught_exception()) {
            this->check_exit_static_inv();
        } else {
            this->check_exit_inv();
            this->check_post();
        }
    }
};

} } } // namespace

#endif // #include guard

