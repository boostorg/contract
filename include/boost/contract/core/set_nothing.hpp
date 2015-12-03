
#ifndef BOOST_CONTRACT_SET_NOTHING_HPP_
#define BOOST_CONTRACT_SET_NOTHING_HPP_

/** @file */

#include <boost/contract/aux_/condition/check_base.hpp>
#include <boost/contract/aux_/auto_ptr.hpp>
#include <boost/contract/aux_/debug.hpp>
/** @cond */
#include <boost/config.hpp>
/** @endcond */

namespace boost {
    namespace contract {
        template<typename>
        class set_precondition_old_postcondition;
        
        template<typename>
        class set_old_postcondition;
        
        template<typename>
        class set_postcondition_only;
    }
}
    
namespace boost { namespace contract {

class set_nothing { // Copyable as * (OK also for RAII).
public:
    ~set_nothing() BOOST_NOEXCEPT_IF(false) {}
    
    // No set member functions here.

private:
    typedef boost::contract::aux::check_base check_type;
    explicit set_nothing(check_type* check) : check_(check) {}
    boost::contract::aux::auto_ptr<check_type> check_;

    // Friendship used to limit library's public API.
    friend class guard;

    template<typename>
    friend class set_precondition_old_postcondition;
    
    template<typename>
    friend class set_old_postcondition;

    template<typename>
    friend class set_postcondition_only;
};

} } // namespace

#endif // #include guard

