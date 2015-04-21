
#ifndef BOOST_CONTRACT_AUX_FREE_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_FREE_FUNCTION_HPP_

#include <boost/contract/aux_/basic_function.hpp>
#include <exception>

namespace boost { namespace contract { namespace aux {

class free_function : public boost::contract::aux::basic_function<> {
public:
    explicit free_function() { entry(); }

    ~free_function() { exit(); }
    
private:
    // Do nothing (not a public member so no inv to check, nor subcontracting).
    void entry() {}

    // Check pre (as soon as related functor set).
    void pre_available() { this->check_pre(); }
    
    // Post always checked after body, at exit (see below).
    void post_available() {}
    
    // If body did not throw, check post (not a public member so no inv to
    // check, nor subcontracting).
    void exit() {
        bool const body_threw = std::uncaught_exception();
        if(!body_threw) check_post();
    }
};

} } } // namespace

#endif // #include guard

