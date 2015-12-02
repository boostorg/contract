
#ifndef BOOST_CONTRACT_AUX_PUBLIC_STATIC_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_PUBLIC_STATIC_FUNCTION_HPP_

#include <boost/contract/core/virtual.hpp>
#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post_inv.hpp>
#include <boost/contract/aux_/check_guard.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/config.hpp>
#include <exception>
/** @endcond */

namespace boost { namespace contract { namespace aux {

// No subcontracting because static so no obj and no substitution principle.
template<class C>
class public_static_function : public check_pre_post_inv</* R = */ none, C> {
public:
    explicit public_static_function() :
        check_pre_post_inv</* R = */ none, C>(boost::contract::from_function,
                /* obj = */ 0)
    {}

private:
    void init() /* override */ {
        if(check_guard::checking()) return;
        {
            check_guard checking;
            this->check_entry_static_inv();
            this->check_pre();
        }
        this->copy_old();
    }

public:
    ~public_static_function() BOOST_NOEXCEPT_IF(false) {
        this->assert_guarded();
        if(check_guard::checking()) return;
        check_guard checking;
        this->check_exit_static_inv();
        if(!std::uncaught_exception()) this->check_post(none());
    }
};

} } } // namespace

#endif // #include guard

