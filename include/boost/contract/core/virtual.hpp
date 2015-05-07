
#ifndef BOOST_CONTRACT_VIRTUAL_HPP_
#define BOOST_CONTRACT_VIRTUAL_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <queue>

namespace boost {
    namespace contract {
        namespace aux {
            class oldof;

            namespace function {
                template<class, class, typename>
                class public_member;
            }
            namespace check {
                template<class, class, typename>
                class subcontracted_pre_post_inv;
            }
            
            namespace test {
                class friend_;
            }
        }
    }
}

namespace boost { namespace contract {

class virtual_ : private boost::noncopyable { // To avoid copying queue.
    // No public operation (users can only assign pointer to this type to null.
//private:
public:
    // Friendship used to limit public library API.
    template<class, class, typename>
    friend class boost::contract::aux::function::public_member;
    
    template<class, class, typename>
    friend class boost::contract::aux::check::subcontracted_pre_post_inv;
    
    friend class boost::contract::aux::oldof;
    friend bool copy_oldof(virtual_* const);

    friend class boost::contract::aux::test::friend_; // For regression tests.

    enum action_enum {
        user_call, // User call if either v == null || v->action == user_call.
        copy_oldof,
        check_entry_inv,
        check_pre,
        check_post,
        check_this_post,
        check_exit_inv
    };
    
    explicit virtual_() : action_(user_call), old_values_() {}
    
    // State passed across virtual calls (friends access data members directly).
    action_enum action_;
    std::queue<boost::shared_ptr<void> > old_values_;
};

} } // namespace

#endif // #include guard

