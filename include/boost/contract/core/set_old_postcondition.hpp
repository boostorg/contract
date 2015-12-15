
#ifndef BOOST_CONTRACT_SET_OLD_POSTCONDITION_HPP_
#define BOOST_CONTRACT_SET_OLD_POSTCONDITION_HPP_

/** @file */

#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/contract/aux_/auto_ptr.hpp>
#include <boost/contract/aux_/debug.hpp>
/** @cond */
#include <boost/config.hpp>
/** @endcond */

namespace boost {
    namespace contract {
        template<typename R>
        class set_precondition_old_postcondition;
    }
}

namespace boost { namespace contract {
    
template<typename R = void>
class set_old_postcondition { // Copyable (as *).
public:
    ~set_old_postcondition() BOOST_NOEXCEPT_IF(false) {}
    
    template<typename F>
    set_postcondition_only<R> old(F const& f) {
        BOOST_CONTRACT_AUX_DEBUG(check_);
        check_->set_old(f);
        return set_postcondition_only<R>(check_.release());
    }

    template<typename F>
    set_nothing postcondition(F const& f) {
        BOOST_CONTRACT_AUX_DEBUG(check_);
        check_->set_post(f);
        return set_nothing(check_.release());
    }

private:
    typedef boost::contract::aux::check_pre_post<
            typename boost::contract::aux::none_if_void<R>::type> check_type;

    explicit set_old_postcondition(check_type* check) : check_(check) {}
    
    boost::contract::aux::auto_ptr<check_type> check_;

    // Friendship used to limit library's public API.

    friend class guard;
    friend class set_precondition_old_postcondition<R>;

    template<class C>
    friend set_old_postcondition constructor(C*);

    template<class C>
    friend set_old_postcondition destructor(C*);
};

} } // namespace

#endif // #include guard

