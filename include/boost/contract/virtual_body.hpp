
#ifndef BOOST_CONTRACT_VIRTUAL_BODY_HPP_
#define BOOST_CONTRACT_VIRTUAL_BODY_HPP_

namespace boost {
    namespace contract {
        namespace aux {
            namespace check {
                template<class, class, typename, typename>
                class subcontracted_pre_post_inv;
            }
            namespace function {
                template<class, class, typename, typename>
                class public_member;
            }
        }
    }
}

namespace boost { namespace contract {

// Must be efficient to pass this as value param (to limit user API verbosity).
class virtual_body {
public:
    /* implicit */ virtual_body(int const) : action_(user_call) {}

private:
    // Use friendship to limit public API.
    template<class, class, typename, typename>
    friend class boost::contract::aux::check::subcontracted_pre_post_inv;

    template<class, class, typename, typename>
    friend class boost::contract::aux::function::public_member;

    friend bool skip_oldof(virtual_body const);

    enum action_type {
        user_call,
        check_pre_only,
        check_post_only,
        check_entry_inv_only,
        check_exit_inv_only
    };

    /* implicit */ virtual_body(action_type const action) :
            action_(action) {}

    bool operator==(action_type const action) const {
        return action_ == action;
    }
    
    bool operator!=(action_type const action) const {
        return action_ != action;
    }

    action_type action_;
};

} } // namespace

#endif // #include guard

