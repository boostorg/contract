
#ifndef BOOST_CONTRACT_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_CONSTRUCTOR_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file */

#include <boost/contract/detail/all_core_headers.hpp>
#if !defined(BOOST_CONTRACT_NO_CONSTRUCTORS) || \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
    #include <boost/contract/detail/operation/constructor.hpp>
#endif
#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
    #include <boost/contract/detail/check_guard.hpp>
#endif

namespace boost { namespace contract {

template<class C>
set_old_postcondition<> constructor(C* obj) {
    // Must #if also on ..._PRECONDITIONS here because set_... is generic.
    #if !defined(BOOST_CONTRACT_NO_CONSTRUCTORS) || \
            !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
        return set_old_postcondition<>(
                new boost::contract::detail::constructor<C>(obj));
    #else
        return set_old_postcondition<>();
    #endif
}

template<class C> // tparam avoids multiple instance of same base in user code.
class constructor_precondition { // Copyable (no data).
public:
    constructor_precondition() {} // For user ctor overloads with no pre.

    template<typename F>
    explicit constructor_precondition(F const& f) {
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            if(boost::contract::detail::check_guard::checking()) return;
            try {
                #ifndef BOOST_CONTRACT_PRECONDITIONS_DISABLE_NOTHING
                    boost::contract::detail::check_guard checking;
                #endif
                f();
            } catch(...) { precondition_failure(from_constructor); }
        #endif
    }

    // Default copy operations (so user's derived classes can be copied, etc.).
};

} } // namespace

#endif // #include guard

