
#ifndef BOOST_CONTRACT_VIRTUAL_HPP_
#define BOOST_CONTRACT_VIRTUAL_HPP_

#include <boost/contract/core/config.hpp>
/** @cond */
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <queue>
#include <stack>
/** @endcond */

namespace boost {
    namespace contract {
        namespace aux {
            template<class, typename, typename, class, typename, typename>
            class check_subcontracted_pre_post_inv;
        }
    }
}

namespace boost { namespace contract {

class virtual_ :
    private boost::noncopyable // Avoid copying queue, stack, etc.
{
    // No public API (so users cannot use it directly).
private:
    enum action_enum {
        // virtual_ always hold/passed by ptr so null ptr used for user call.
        no_action,
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

    explicit virtual_(action_enum a) :
        action_(a),
        #if BOOST_CONTRACT_POSTCONDITIONS
            result_type_name_(),
            result_optional_(),
        #endif
        failed_(false)
    {}

    action_enum action_;
    
    #if BOOST_CONTRACT_POSTCONDITIONS
        std::queue<boost::shared_ptr<void> > old_inits_;
        std::stack<boost::shared_ptr<void> > old_copies_;

        boost::any result_ptr_;
        char const* result_type_name_;
        bool result_optional_;
    #endif

    bool failed_;

    // Friendship used to limit library's public API.
    friend bool copy_old(virtual_*);
    friend class convertible_old;

    template<class, typename, typename, class, typename, typename>
    friend class boost::contract::aux::check_subcontracted_pre_post_inv;
};

} } // namespace

#endif // #include guard

