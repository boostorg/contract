
#ifndef BOOST_CONTRACT_AUX_FREE_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_FREE_FUNCTION_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/call.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
#include <exception>
/** @endcond */

namespace boost { namespace contract { namespace aux {

template<boost::contract::from From>
class basic_free_function : public boost::contract::aux::check_pre_post {
public:
    explicit basic_free_function() :
            boost::contract::aux::check_pre_post(From) {}

    explicit basic_free_function(boost::shared_ptr<boost::contract::aux::call>
            call) : boost::contract::aux::check_pre_post(From, call) {}

private:
    void pre_available() /* override */ { check_pre(); }

    void post_available() /* override */ {
        if(this->contract_call() && !std::uncaught_exception()) {
            check_post(); // Throw no_error (so not in dtor).
        }
    }
    
public:
    ~basic_free_function() {
        if(!this->contract_call() && !std::uncaught_exception()) {
            check_post();
        }
    }
};

typedef basic_free_function<boost::contract::from_free_function> free_function;

} } } // namespace

#endif // #include guard

