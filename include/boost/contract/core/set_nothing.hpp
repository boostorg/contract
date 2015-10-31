
#ifndef BOOST_CONTRACT_SET_NOTHING_HPP_
#define BOOST_CONTRACT_SET_NOTHING_HPP_

/** @file */

#include <boost/contract/aux_/condition/check_base.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
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

// TODO: Do I need to store contracts as shared_ptr or unique_ptr is sufficient? Actually, double check all shared_ptr used in the lib anywhere (also in old_ptr, etc.) and see if unique_ptr would be sufficient there.

class set_nothing { // Copyable as shared * (OK also for RAII).
public:
    // No set member functions here.

private:
    typedef boost::shared_ptr<boost::contract::aux::check_base> check_ptr;
    explicit set_nothing(check_ptr check): check_(check) {}
    check_ptr check_;

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

