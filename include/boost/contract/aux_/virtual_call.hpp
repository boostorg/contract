
#ifndef BOOST_CONTRACT_AUX_VIRTUAL_CALL_HPP_
#define BOOST_CONTRACT_AUX_VIRTUAL_CALL_HPP_

#include <boost/shared_ptr.hpp>
#include <deque>

namespace boost { namespace contract { namespace aux {

// Contain state/data passed across virtual function contract calls (so struct).
struct virtual_call {
    enum action_type {
        user_call, // TODO: Can I use v == 0 instead of this?
        copy_oldof,
        check_entry_inv,
        check_pre,
        check_post,
        check_exit_inv
    };
    
    action_type action;

    // TODO: Is this the most efficient STL FIFO?
    std::deque<boost::shared_ptr<void> > old_values;

    explicit virtual_call() : action(user_call), old_values() {}
};

} } } // namespace

#endif // #include guard

