
#ifndef BOOST_CONTRACT_VIRTUAL_BODY_HPP_
#define BOOST_CONTRACT_VIRTUAL_BODY_HPP_

namespace boost { namespace contract {

namespace aux {
    template<class, class, typename> class base_function;
    template<class, class, typename, typename> class basic_function;
    template<class, class, typename, typename> class public_member;
}

// Must be efficient to pass this as value param (to limit user API verbosity).
struct virtual_body {
    /* implicit */ virtual_body(int const) : action(user_call) {}

    // TODO: Fix this... how?
    template<typename T>
    T const oldof_(T const& value) const { return value; }

private:
    // TODO: See if there is a way to reduce friendship relationships (because
    // they make the impl hard to follow). These ones are necessary because
    // they are between public and private APIs of the lib. But maybe
    // the ones among some of the private APIs of the lib could be reduced...
    template<class, class, typename> friend class
            boost::contract::aux::base_function;
    template<class, class, typename, typename> friend class
            boost::contract::aux::basic_function;
    template<class, class, typename, typename> friend class
            boost::contract::aux::public_member;

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

