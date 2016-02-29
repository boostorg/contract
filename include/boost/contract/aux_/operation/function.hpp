
#ifndef BOOST_CONTRACT_AUX_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_FUNCTION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
    #include <boost/contract/aux_/check_guard.hpp>
#endif
#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
    #include <boost/config.hpp>
    #include <exception>
#endif

namespace boost { namespace contract { namespace aux {

// Used for free function, private and protected member functions.
class function :
        public check_pre_post</* R = */ none> { // Non-copyable base.
public:
    explicit function() : check_pre_post</* R = */ none>(
            boost::contract::from_function) {}

private:
    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
        void init() /* override */ {
            if(check_guard::checking()) return;
            #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                {
                    #ifndef BOOST_CONTRACT_PRECONDITIONS_DISABLE_NOTHING
                        check_guard checking;
                    #endif
                    this->check_pre();
                }
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                this->copy_old();
            #endif
        }
    #endif

public:
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        ~function() BOOST_NOEXCEPT_IF(false) {
            this->assert_guarded();
            if(check_guard::checking()) return;
            check_guard checking;
            
            if(!std::uncaught_exception()) this->check_post(none());
        }
    #endif
};

} } } // namespace

#endif // #include guard

