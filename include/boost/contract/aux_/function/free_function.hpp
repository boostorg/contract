
#ifndef BOOST_CONTRACT_AUX_FREE_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_FREE_FUNCTION_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
#include <boost/contract/aux_/call.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
#include <exception>
/** @endcond */

namespace boost { namespace contract { namespace aux {

// Also used for private and protected members.
template<boost::contract::from From>
class basic_free_function : public check_pre_post {
public:
    explicit basic_free_function() : check_pre_post(From) {}

    explicit basic_free_function(boost::shared_ptr<call> decl_call) :
            check_pre_post(From, decl_call) {}

private:
    void pre_available() /* override */ { check_pre(); }

    void post_available() /* override */ {
        // Throw no_error (so not in dtor).
        if(this->decl_call() && !std::uncaught_exception()) check_post();
    }
    
public:
    ~basic_free_function() {
        if(!this->decl_call() && !std::uncaught_exception()) check_post();
    }
};

typedef basic_free_function<boost::contract::from_free_function> free_function;

} } } // namespace

#endif // #include guard

