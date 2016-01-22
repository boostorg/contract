
#ifndef BOOST_CONTRACT_SET_NOTHING_HPP_
#define BOOST_CONTRACT_SET_NOTHING_HPP_

/** @file */

#include <boost/contract/aux_/condition/check_base.hpp>
#include <boost/contract/aux_/auto_ptr.hpp>
/** @cond */
#include <boost/config.hpp>
/** @endcond */

namespace boost {
    namespace contract {
        template<typename RR>
        class set_precondition_old_postcondition;
        
        template<typename RR>
        class set_old_postcondition;
        
        template<typename RR>
        class set_postcondition_only;
    }
}
    
namespace boost { namespace contract {

class set_nothing { // Copyable (as *).
public:
    ~set_nothing() BOOST_NOEXCEPT_IF(false) {}
    
    // No set member functions here.

private:
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        typedef boost::contract::aux::check_base check_type;
        
        explicit set_nothing(check_type* check) : check_(check) {}

        boost::contract::aux::auto_ptr<check_type> check_;
    #endif

    // Friendship used to limit library's public API.

    friend class guard;

    template<typename RR>
    friend class set_precondition_old_postcondition;
    
    template<typename RR>
    friend class set_old_postcondition;

    template<typename RR>
    friend class set_postcondition_only;
};

} } // namespace

#endif // #include guard

