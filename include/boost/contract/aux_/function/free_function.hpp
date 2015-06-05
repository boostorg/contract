
#ifndef BOOST_CONTRACT_AUX_FREE_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_FREE_FUNCTION_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
#include <boost/contract/aux_/check_guard.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
#include <exception>
/** @endcond */

namespace boost { namespace contract { namespace aux {

// Also used for private and protected members.
template<boost::contract::from From>
class basic_free_function : public check_pre_post</* R = */ none> {
public:
    explicit basic_free_function() : check_pre_post</* R = */ none>(From) {}

private:
    void pre_available() /* override */ {
        BOOST_CONTRACT_AUX_CHECK_GUARD_OR_RETURN
        this->check_pre();
    }

public:
    ~basic_free_function() {
        BOOST_CONTRACT_AUX_CHECK_GUARD_OR_RETURN
        if(!std::uncaught_exception()) this->check_post();
    }
};

typedef basic_free_function<boost::contract::from_free_function> free_function;

} } } // namespace

#endif // #include guard

