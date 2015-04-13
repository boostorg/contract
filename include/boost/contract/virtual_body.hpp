
#ifndef BOOST_CONTRACT_VIRTUAL_BODY_HPP_
#define BOOST_CONTRACT_VIRTUAL_BODY_HPP_

#include <boost/contract/aux_/function_key.hpp>

namespace boost { namespace contract {

namespace aux {
    template<boost::contract::aux::function_key, class, class, typename,
            typename> class function;
    template<class, class, typename> class base_function;
}

// Must be efficient to pass this as value param (to limit user API verbosity).
struct virtual_body {
    /* implicit */ virtual_body(int const) : action(user_call) {}

    // TODO: Fix this... how?
    template<typename T>
    T const oldof_(T const& value) const { return value; }

private:
    template<boost::contract::aux::function_key, class, class, typename,
            typename> friend class boost::contract::aux::function;
    template<class, class, typename> friend class
            boost::contract::aux::base_function;

    enum action_type {
        user_call,
        check_inv_only,
        check_static_inv_only,
        check_pre_only,
        check_post_only
    };

    /* implicit */ virtual_body(action_type const an_action) :
            action(an_action) {}

    action_type action;
};

} } // namespace

#endif // #include guard

