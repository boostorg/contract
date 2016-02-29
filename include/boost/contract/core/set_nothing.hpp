
#ifndef BOOST_CONTRACT_SET_NOTHING_HPP_
#define BOOST_CONTRACT_SET_NOTHING_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file */

#include <boost/contract/core/config.hpp>
#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS)
    #include <boost/contract/aux_/condition/check_base.hpp>
    #include <boost/contract/aux_/auto_ptr.hpp>
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

class set_nothing { // Copyable (as *).
public:
    ~set_nothing() BOOST_NOEXCEPT_IF(false) {}
    
    // No set member functions here.

private:
    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        typedef boost::contract::aux::check_base check_type;

        explicit set_nothing(check_type* check) : check_(check) {}
        
        boost::contract::aux::auto_ptr<check_type> check_;
    #endif

    // Friends (used to limit library's public API).

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

