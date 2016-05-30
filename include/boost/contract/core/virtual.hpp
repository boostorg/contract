
#ifndef BOOST_CONTRACT_VIRTUAL_HPP_
#define BOOST_CONTRACT_VIRTUAL_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Facility to declare virtual public functions with contracts.
*/

#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/decl.hpp>
#include <boost/noncopyable.hpp>
#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
    #include <boost/any.hpp>
    #include <boost/shared_ptr.hpp>
    #include <queue>
    #include <stack>
#endif

namespace boost {
    namespace contract {
        namespace detail {
  BOOST_CONTRACT_DETAIL_DECL_DETAIL_CHECK_SUBCONTRACTED_PRE_POST_INV_Z(1,
                    /* is_friend = */ 0, OO, RR, FF, CC, AArgs);
        }
    }
}

namespace boost { namespace contract {

/**
Class to mark declarations of virtual public functions.
Virtual public functions (and therefore overriding public functions) contracted
using this library must have an extra parameter at the very end of their
parameter list. This parameter must be a pointer to this class and it must have
default value @c 0 (i.e., null). (This extra parameter is often named @c v in
this documentation, but any name can be used.)

This extra parameter does not alter the calling interface of the contracted
function because it is always the last parameter and it has a default value (so
it is always omitted when users call the contracted function). This extra
parameter must be passed to @RefFunc{boost::contract::public_function},
@RefMacro{BOOST_CONTRACT_OLDOF}, and all other operations of this library that
require a pointer to @RefClass{boost::contract::virtual_}. A part from that,
this class is not intended to be directly used by programmers (and that is why
this class does not have any public member and it is not copyable).

@b Rationale:   This extra parameter is internally used by this library to
                recognize virtual public functions to implement subcontracting
                (@c virtual cannot be introspected using template
                meta-programming techniques in C++).
@see @RefSect{tutorial, Tutorial}
*/
class virtual_ : private boost::noncopyable { // Avoid copy queue, stack, etc.
/** @cond */
    // No public API (so users cannot use it directly by mistake).

    enum action_enum {
        // virtual_ always hold/passed by ptr so null ptr used for user call.
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            no_action,
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            push_old_init,
        #endif
        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            check_entry_inv,
        #endif
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            check_pre,
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            call_old_copy,
            push_old_copy,
        #endif
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            check_exit_inv,
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            pop_old_copy,
            check_post,
            pop_old_init = check_post // These must be the same value.
        #endif
    };

    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        explicit virtual_(action_enum a) :
              action_(a)
            , failed_(false)
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                , result_type_name_()
                , result_optional_()
            #endif
        {}
    #endif

    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        action_enum action_;
        bool failed_;
    #endif
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        std::queue<boost::shared_ptr<void> > old_inits_;
        std::stack<boost::shared_ptr<void> > old_copies_;

        boost::any result_ptr_; // Result for virtual and overriding functions.
        char const* result_type_name_;
        bool result_optional_;
    #endif

    // Friends (used to limit library's public API).

    friend bool copy_old(virtual_*);
    
    friend class convertible_old;

    BOOST_CONTRACT_DETAIL_DECL_DETAIL_CHECK_SUBCONTRACTED_PRE_POST_INV_Z(1,
            /* is_friend = */ 1, OO, RR, FF, CC, AArgs);
/** @endcond */
};

} } // namespace

#endif // #include guard

