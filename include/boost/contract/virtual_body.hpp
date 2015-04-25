
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
    /* implicit */ virtual_body(int const) : action(user_call) {}

private:
    enum action_type {
        user_call,
        check_inv_only,
        check_pre_only,
        check_post_only
    };

    /* implicit */ virtual_body(action_type const an_action) :
            action(an_action) {}

    action_type action;

    // Use friendship to limit public API.
    
    template<class, class, typename, typename>
    friend class boost::contract::aux::check::subcontracted_pre_post_inv;

    template<class, class, typename, typename>
    friend class boost::contract::aux::function::public_member;

    friend bool skip_oldof(virtual_body const);
};

} } // namespace

#endif // #include guard

