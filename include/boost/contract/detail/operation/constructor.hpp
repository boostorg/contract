
#ifndef BOOST_CONTRACT_DETAIL_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_DETAIL_CONSTRUCTOR_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/condition/check_pre_post_inv.hpp>
#include <boost/contract/detail/none.hpp>
#if !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
    #include <boost/contract/detail/check_guard.hpp>
#endif
#if !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
    #include <boost/config.hpp>
    #include <exception>
#endif

namespace boost { namespace contract { namespace detail {

// Ctor subcontracting impl via C++ obj construction mechanism.
template<class C>
class constructor :
        public check_pre_post_inv</* R = */ none, C> { // Non-copyable base.
public:
    explicit constructor(C* obj) : check_pre_post_inv</* R = */ none, C>(
            boost::contract::from_constructor, obj) {}

private:
    #if !defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
        void init() /* override */ {
            if(check_guard::checking()) return;

            #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                {
                    check_guard checking;
                    this->check_entry_static_inv();
                    // No object before ctor body so check only static inv at
                    // entry. Ctor pre checked by constructor_precondition.
                }
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                this->copy_old();
            #endif
        }
    #endif

public:
    #if !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
        ~constructor() BOOST_NOEXCEPT_IF(false) {
            this->assert_guarded();
            if(check_guard::checking()) return;
            check_guard checking;
            // If ctor body threw, no obj so check only static inv. Otherwise,
            // obj constructed so check static inv, non-static inv, and post.
            bool body_threw = std::uncaught_exception();

            #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                if(body_threw) this->check_exit_static_inv();
                else this->check_exit_inv();
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                if(!body_threw) this->check_post(none());
            #endif
        }
    #endif
};

} } } // namespace

#endif // #include guard

