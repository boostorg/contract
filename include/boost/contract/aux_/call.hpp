
#ifndef BOOST_CONTRACT_AUX_CALL_HPP_
#define BOOST_CONTRACT_AUX_CALL_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <queue>

namespace boost { namespace contract { namespace aux {

struct call : private boost::noncopyable { // Do not copy queue.
    enum action_enum {
        // Call always hold by ptr so null ptr (not enum) used for user-call.
        copy_oldof,
        check_entry_inv,
        check_pre,
        check_post,
        check_exit_inv
    };

    explicit call() : action() {}
    
    action_enum action;
    std::queue<boost::shared_ptr<void> > old_values;
};

} } } // namespace

#endif // #include guard

