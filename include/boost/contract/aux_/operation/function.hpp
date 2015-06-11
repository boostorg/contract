
#ifndef BOOST_CONTRACT_AUX_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_FUNCTION_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
#include <boost/contract/aux_/check_guard.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
#include <exception>
/** @endcond */

namespace boost { namespace contract { namespace aux {

// Used for free function, private and protected member functions.
class function : public check_pre_post</* R = */ none> {
public:
    explicit function() : check_pre_post</* R = */ none>(
            boost::contract::from_function) {}

private:
    void pre_available() /* override */ {
        BOOST_CONTRACT_AUX_CHECK_GUARD_OR_RETURN
        this->check_pre();
    }

public:
    ~function() {
        BOOST_CONTRACT_AUX_CHECK_GUARD_OR_RETURN
        if(!std::uncaught_exception()) this->check_post();
    }
};

} } } // namespace

#endif // #include guard

