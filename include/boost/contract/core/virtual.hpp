
#ifndef BOOST_CONTRACT_VIRTUAL_HPP_
#define BOOST_CONTRACT_VIRTUAL_HPP_

/** @cond */
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

class virtual_ : private boost::noncopyable { // Non copyable (no queue copy).
    // No public API (so users cannot use it directly).
private:
    enum action_enum {
        // virtual_ always hold/passed by ptr so null ptr used for user call.
        no_action,
        push_old_init,
        check_entry_inv,
        check_pre,
        call_old_copy,
        push_old_copy,
        check_exit_inv,
        pop_old_copy,
        check_post,
        pop_old_init = check_post // These must be the same value.
    };

    explicit virtual_(action_enum a) : action_(a) {}

    action_enum action_;
    std::queue<boost::shared_ptr<void> > old_inits_;
    std::stack<boost::shared_ptr<void> > old_copies_;
    void* result_;

    // Friendship used to limit library's public API.
    friend bool copy_old(virtual_*);
    friend class old;

    template<class, typename, typename, class, typename, typename>
    friend class boost::contract::aux::check_subcontracted_pre_post_inv;
};

} } // namespace

#endif // #include guard

