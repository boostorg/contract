
#ifndef BOOST_CONTRACT_SET_POSTCONDITION_ONLY_HPP_
#define BOOST_CONTRACT_SET_POSTCONDITION_ONLY_HPP_

/** @file */

#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/contract/aux_/debug.hpp>

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
class set_postcondition_only { // Copyable as shared * (OK also for RAII).
public:
    template<typename F>
    set_nothing postcondition(F const& f) {
        check_->set_post(f);
        return set_nothing(check_);
    }

private:
    typedef boost::contract::aux::check_pre_post<
            typename boost::contract::aux::none_if_void<R>::type>* check_ptr;
    explicit set_postcondition_only(check_ptr check) :
            check_(check) { BOOST_CONTRACT_AUX_DEBUG(check_); }
    check_ptr check_;

    // Friendship used to limit library's public API.
    friend class guard;
    friend class set_precondition_old_postcondition<R>;
    friend class set_old_postcondition<R>;
};

} } // namespace

#endif // #include guard

