
#ifndef BOOST_CONTRACT_AUX_PUBLIC_STATIC_MEMBER_HPP_
#define BOOST_CONTRACT_AUX_PUBLIC_STATIC_MEMBER_HPP_

#include <boost/contract/core/virtual.hpp>
#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post_inv.hpp>
#include <boost/contract/aux_/check_guard.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
#include <exception>
/** @endcond */

namespace boost { namespace contract { namespace aux {

// No subcontracting because static so no obj and no subst. principle.
template<class C>
class public_static_member : public check_pre_post_inv<none, C> {
public:
    explicit public_static_member() : check_pre_post_inv<none, C>(
            boost::contract::from_public_member, 0) {
        BOOST_CONTRACT_AUX_CHECK_GUARD_OR_RETURN
        this->check_entry_static_inv();
    }

private:
    void pre_available() /* override */ {
        BOOST_CONTRACT_AUX_CHECK_GUARD_OR_RETURN
        this->check_pre();
    }

public:
    ~public_static_member() {
        BOOST_CONTRACT_AUX_CHECK_GUARD_OR_RETURN
        this->check_exit_static_inv();
        if(!std::uncaught_exception()) this->check_post();
    }
};

} } } // namespace

#endif // #include guard

