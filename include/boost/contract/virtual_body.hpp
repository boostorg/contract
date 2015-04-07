
#ifndef BOOST_CONTRACT_VIRTUAL_BODY_HPP_
#define BOOST_CONTRACT_VIRTUAL_BODY_HPP_

namespace boost { namespace contract {

namespace aux {
    template< class, typename, class, typename > class function;
    template< class, typename, class, typename > class base_function;
}

// Must be efficient to pass this as value param (to limit user API verbosity).
struct virtual_body {
    /* implicit */ virtual_body ( int const ) : action(user_call) {}

    template< typename T >
    T const oldof_ ( T const& value ) const { return value; }

private:
    template< class, typename, class, typename > friend class
            boost::contract::aux::function;
    template< class, typename, class, typename > friend class
            boost::contract::aux::base_function;

    enum action_type {
        user_call,
        check_inv_only,
        check_pre_only,
        check_post_only
    };

    /* implicit */ virtual_body ( action_type const an_action ) :
            action(an_action) {}

    action_type action;
};

} } // namespace

#endif // #include guard

