
#ifndef BOOST_CONTRACT_VIRTUAL_HPP_
#define BOOST_CONTRACT_VIRTUAL_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/config.hpp>
#include <boost/contract/aux_/decl.hpp>
#include <boost/noncopyable.hpp>
#if BOOST_CONTRACT_POSTCONDITIONS
    #include <boost/any.hpp>
    #include <boost/shared_ptr.hpp>
    #include <queue>
    #include <stack>
#endif

namespace boost {
    namespace contract {
        namespace aux {
            BOOST_CONTRACT_AUX_DECL_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_Z(1,
                    /* is_friend = */ 0, OO, RR, FF, CC, AArgs);
        }
    }
}

namespace boost { namespace contract {

class virtual_ : private boost::noncopyable { // Avoid copy queue, stack, etc.
    // No public API (so users cannot use it directly by mistake).

    enum action_enum {
        // virtual_ always hold/passed by ptr so null ptr used for user call.
        #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
                BOOST_CONTRACT_INVARIANTS
            no_action,
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            push_old_init,
        #endif
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            check_entry_inv,
        #endif
        #if BOOST_CONTRACT_PRECONDITIONS
            check_pre,
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            call_old_copy,
            push_old_copy,
        #endif
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            check_exit_inv,
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            pop_old_copy,
            check_post,
            pop_old_init = check_post // These must be the same value.
        #endif
    };

    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        explicit virtual_(action_enum a) :
              action_(a)
            , failed_(false)
            #if BOOST_CONTRACT_POSTCONDITIONS
                , result_type_name_()
                , result_optional_()
            #endif
        {}
    #endif

    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        action_enum action_;
        bool failed_;
    #endif
    #if BOOST_CONTRACT_POSTCONDITIONS
        std::queue<boost::shared_ptr<void> > old_inits_;
        std::stack<boost::shared_ptr<void> > old_copies_;

        boost::any result_ptr_;
        char const* result_type_name_;
        bool result_optional_;
    #endif

    // Friends (used to limit library's public API).

    friend bool copy_old(virtual_*);
    
    friend class convertible_old;

    BOOST_CONTRACT_AUX_DECL_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_Z(1,
            /* is_friend = */ 1, OO, RR, FF, CC, AArgs);
};

} } // namespace

#endif // #include guard

