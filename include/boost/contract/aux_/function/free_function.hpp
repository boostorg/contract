
#ifndef BOOST_CONTRACT_AUX_FUNCTION_FREE_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_FUNCTION_FREE_FUNCTION_HPP_

#include <boost/contract/exception.hpp>
#include <boost/contract/aux_/check/pre_post.hpp>
#include <exception>

namespace boost { namespace contract { namespace aux { namespace function {

class free_function : public boost::contract::aux::check::pre_post {
public:
    explicit free_function(boost::contract::from const from =
            boost::contract::from_free_function) :
        boost::contract::aux::check::pre_post(from)
    { entry(); }

    virtual ~free_function() { exit(); }
    
private:
    // Do nothing (not a public member so no inv to check, nor subcontracting).
    void entry() {}

    // Check pre (as soon as related functor set).
    void pre_available() /* override */ { check_pre(); }
    
    // Post always checked after body, at exit (see below).
    void post_available() /* override */ {}
    
    // If body did not throw, check post (not a public member so no inv to
    // check, nor subcontracting).
    void exit() {
        bool const body_threw = std::uncaught_exception();
        if(!body_threw) check_post();
    }
};

} } } } // namespace

#endif // #include guard

