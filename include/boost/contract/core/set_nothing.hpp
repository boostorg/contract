
#ifndef BOOST_CONTRACT_SET_NOTHING_HPP_
#define BOOST_CONTRACT_SET_NOTHING_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Used to prevent setting other contract conditions after postconditions.
*/

#include <boost/contract/core/config.hpp>
#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS)
    #include <boost/contract/detail/condition/check_base.hpp>
    #include <boost/contract/detail/auto_ptr.hpp>
#endif
#include <boost/config.hpp>

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

/**
Used to prevent setting other contract conditions after postconditions.
This class has no member function so it cannot be used to set any contract
functor.
*/
class set_nothing { // Copyable (as *).
public:
    /** Destruct this object. */
    ~set_nothing() BOOST_NOEXCEPT_IF(false) {}
    
    // No set member functions here.

/** @cond */
private:
    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        typedef boost::contract::detail::check_base check_type;

        explicit set_nothing(check_type* check) : check_(check) {}
        
        boost::contract::detail::auto_ptr<check_type> check_;
    #endif

    // Friends (used to limit library's public API).

    friend class guard;

    template<typename RR>
    friend class set_precondition_old_postcondition;
    
    template<typename RR>
    friend class set_old_postcondition;

    template<typename RR>
    friend class set_postcondition_only;
/** @endcond */
};

} } // namespace

#endif // #include guard

