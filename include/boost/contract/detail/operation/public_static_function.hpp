
#ifndef BOOST_CONTRACT_DETAIL_PUBLIC_STATIC_FUNCTION_HPP_
#define BOOST_CONTRACT_DETAIL_PUBLIC_STATIC_FUNCTION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/condition/check_pre_post_inv.hpp>
#include <boost/contract/detail/none.hpp>
#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(OOST_CONTRACT_NO_INVARIANTS)
    #include <boost/contract/detail/check_guard.hpp>
#endif
#if !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
    #include <boost/config.hpp>
#endif
#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
    #include <exception>
#endif

namespace boost { namespace contract { namespace detail {

// No subcontracting because static so no obj and no substitution principle.
template<class C>
class public_static_function :
        public check_pre_post_inv</* R = */ none, C> { // Non-copyable base.
public:
    explicit public_static_function() :
        check_pre_post_inv</* R = */ none, C>(boost::contract::from_function,
                /* obj = */ 0)
    {}

private:
    #if !defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
        void init() /* override */ {
            if(check_guard::checking()) return;
            #if !defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) || \
                    !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
                { // Acquire check guard.
                    check_guard checking;
                    #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                        this->check_entry_static_inv();
                    #endif
                    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
  #ifndef BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION
                                this->check_pre();
                            } // Release check guard.
                        #else
                            } // Release check guard.
                            this->check_pre();
                        #endif
                    #else
                        } // Release check guard
                    #endif
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                this->copy_old();
            #endif
        }
    #endif

public:
    #if !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
        ~public_static_function() BOOST_NOEXCEPT_IF(false) {
            this->assert_guarded();
            if(check_guard::checking()) return;
            check_guard checking;

            #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                this->check_exit_static_inv();
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                if(!std::uncaught_exception()) this->check_post(none());
            #endif
        }
    #endif
};

} } } // namespace

#endif // #include guard

