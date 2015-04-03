
#ifndef BOOST_CONTRACT_CONTROL_HPP_
#define BOOST_CONTRACT_CONTROL_HPP_

namespace boost { namespace contract {

// Must be efficient to pass this as value param (to limit user API verbosity).
struct control {
    /* implicit */ control ( int const ) : action(none) {} 

    template< typename T >
    T const oldof_ ( T const& value ) const { return value; }

private:
    template< class, class > friend struct function;

    enum action_type {
        none,
        check_inv_only,
        check_pre_only
    };

    /* implicit */ control ( action_type const an_action ) :
            action(an_action) {}

    action_type action;
};

} } // namespace

#endif // #include guard

