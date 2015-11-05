
#ifndef BOOST_CONTRACT_AUX_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_FUNCTION_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
#include <boost/contract/aux_/check_guard.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
#include <exception>
/** @endcond */

namespace boost { namespace contract { namespace aux {

// Used for free function, private and protected member functions.
class function : public check_pre_post</* R = */ none> {
public:
    explicit function() :
        check_pre_post</* R = */ none>(boost::contract::from_function)
    {}

private:
    void init() /* override */ {
        if(check_guard::checking()) return;
        {
            check_guard checking;
            this->check_pre();
        }
        this->copy_old();
    }

public:
    ~function() {
        this->assert_guarded();
        if(check_guard::checking()) return;
        check_guard checking;
        if(!std::uncaught_exception()) this->check_post(none());
    }
};

} } } // namespace

#endif // #include guard

