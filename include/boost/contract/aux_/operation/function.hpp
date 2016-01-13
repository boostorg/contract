
#ifndef BOOST_CONTRACT_AUX_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_FUNCTION_HPP_

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
#include <boost/contract/aux_/check_guard.hpp>
#include <boost/config.hpp>
#include <exception>

namespace boost { namespace contract { namespace aux {

// Used for free function, private and protected member functions.
class function :
        public check_pre_post</* R = */ none> { // Non-copyable base.
public:
    explicit function() : check_pre_post</* R = */ none>(
            boost::contract::from_function) {}

private:
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS
        void init() /* override */ {
            if(check_guard::checking()) return;

            #if BOOST_CONTRACT_PRECONDITIONS
                {
                    check_guard checking;
                    this->check_pre();
                }
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                this->copy_old();
            #endif
        }
    #endif

public:
    #if BOOST_CONTRACT_POSTCONDITIONS
        ~function() BOOST_NOEXCEPT_IF(false) {
            this->assert_guarded();
            if(check_guard::checking()) return;
            check_guard checking;
            
            if(!std::uncaught_exception()) this->check_post(none());
        }
    #endif
};

} } } // namespace

#endif // #include guard

