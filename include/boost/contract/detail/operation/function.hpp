
#ifndef BOOST_CONTRACT_DETAIL_FUNCTION_HPP_
#define BOOST_CONTRACT_DETAIL_FUNCTION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/condition/cond_with_post.hpp>
#if     !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <boost/contract/detail/checking.hpp>
#endif
#if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <boost/config.hpp>
    #include <exception>
#endif

namespace boost { namespace contract { namespace detail {

// Used for free function, private and protected member functions.
class function : public cond_with_post</* VR = */ none> { // Non-copyable base.
public:
    explicit function() : cond_with_post</* VR = */ none>(
            boost::contract::from_function) {}

private:
    #if     !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        void init() /* override */ {
            if(checking::already()) return;
            #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                {
                    #ifndef BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION
                        checking k;
                    #endif
                    this->check_pre();
                }
            #endif
            #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                    !defined(BOOST_CONTRACT_NO_EXCEPTS)
                this->copy_old();
            #endif
        }
    #endif

public:
    #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        ~function() BOOST_NOEXCEPT_IF(false) {
            this->assert_initialized();
            if(checking::already()) return;
            checking k;
            
            if(std::uncaught_exception()) {
                #ifndef BOOST_CONTRACT_NO_EXCEPTS
                    this->check_except();
                #endif
            } else {
                #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                    this->check_post(none());
                #endif
            }
        }
    #endif
};

} } } // namespace

#endif // #include guard

