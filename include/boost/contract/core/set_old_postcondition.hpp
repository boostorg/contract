
#ifndef BOOST_CONTRACT_SET_OLD_POSTCONDITION_HPP_
#define BOOST_CONTRACT_SET_OLD_POSTCONDITION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file */

#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/core/config.hpp>
#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS)
    #include <boost/contract/detail/condition/check_pre_post.hpp>
    #include <boost/contract/detail/auto_ptr.hpp>
    #include <boost/contract/detail/none.hpp>
#endif
#if !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
    #include <boost/contract/detail/debug.hpp>
#endif
#include <boost/config.hpp>

namespace boost {
    namespace contract {
        template<typename RR>
        class set_precondition_old_postcondition;
    }
}

namespace boost { namespace contract {
    
template<typename R = void>
class set_old_postcondition { // Copyable (as *).
public:
    ~set_old_postcondition() BOOST_NOEXCEPT_IF(false) {}
    
    template<typename F>
    set_postcondition_only<R> old(F const& f) {
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            BOOST_CONTRACT_DETAIL_DEBUG(check_);
            check_->set_old(f);
        #endif
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            return set_postcondition_only<R>(check_.release());
        #else
            return set_postcondition_only<R>();
        #endif
    }

    template<typename F>
    set_nothing postcondition(F const& f) {
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            BOOST_CONTRACT_DETAIL_DEBUG(check_);
            check_->set_post(f);
        #endif
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            return set_nothing(check_.release());
        #else
            return set_nothing();
        #endif
    }

private:
    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        typedef boost::contract::detail::check_pre_post<typename
                boost::contract::detail::none_if_void<R>::type> check_type;

        explicit set_old_postcondition(check_type* check) : check_(check) {}
        
        boost::contract::detail::auto_ptr<check_type> check_;
    #endif

    // Friends (used to limit library's public API).

    friend class guard;

    friend class set_precondition_old_postcondition<R>;

    template<class CC>
    friend set_old_postcondition constructor(CC* oobj);

    template<class CC>
    friend set_old_postcondition destructor(CC* oobj);
};

} } // namespace

#endif // #include guard

