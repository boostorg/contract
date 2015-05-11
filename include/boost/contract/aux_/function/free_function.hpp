
#ifndef BOOST_CONTRACT_AUX_FREE_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_FREE_FUNCTION_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/call.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
#include <boost/shared_ptr.hpp>
#include <exception>

namespace boost { namespace contract { namespace aux {

class free_function : public boost::contract::aux::check_pre_post {
public:
    explicit free_function() :
        boost::contract::aux::check_pre_post(
                boost::contract::from_free_function)
    {}

    explicit free_function(boost::shared_ptr<boost::contract::aux::call> call) :
        boost::contract::aux::check_pre_post(
                boost::contract::from_free_function, call)
    {}

private:
    void pre_available() /* override */ { check_pre(); }

    void post_available() /* override */ {
        if(call()) check_post(); // Throw (so not in dtor).
    }
    
public:
    ~free_function() {
        if(!call() && !std::uncaught_exception()) { // Body didn't throw.
            check_post();
        }
    }
};

} } } // namespace

#endif // #include guard

