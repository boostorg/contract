
#ifndef BOOST_CONTRACT_SET_POSTCONDITION_ONLY_HPP_
#define BOOST_CONTRACT_SET_POSTCONDITION_ONLY_HPP_

/** @file */

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/contract/aux_/auto_ptr.hpp>
#if BOOST_CONTRACT_POSTCONDITIONS
    #include <boost/contract/aux_/debug.hpp>
#endif
/** @cond */
#include <boost/config.hpp>
/** @endcond */

namespace boost {
    namespace contract {
        template<typename R>
        class set_precondition_old_postcondition;
        
        template<typename R>
        class set_old_postcondition;
    }
}

namespace boost { namespace contract {
    
template<typename R = void>
class set_postcondition_only { // Copyable (as *).
public:
    ~set_postcondition_only() BOOST_NOEXCEPT_IF(false) {}

    template<typename F>
    set_nothing postcondition(F const& f) {
        #if BOOST_CONTRACT_POSTCONDITIONS
            BOOST_CONTRACT_AUX_DEBUG(check_);
            check_->set_post(f);
        #endif
        #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
                BOOST_CONTRACT_INVARIANTS
            return set_nothing(check_.release());
        #else
            return set_nothing();
        #endif
    }

private:
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        typedef boost::contract::aux::check_pre_post<typename
                boost::contract::aux::none_if_void<R>::type> check_type;

        explicit set_postcondition_only(check_type* check) : check_(check) {}

        boost::contract::aux::auto_ptr<check_type> check_;
    #endif

    // Friendship used to limit library's public API.

    friend class guard;
    friend class set_precondition_old_postcondition<R>;
    friend class set_old_postcondition<R>;
};

} } // namespace

#endif // #include guard

