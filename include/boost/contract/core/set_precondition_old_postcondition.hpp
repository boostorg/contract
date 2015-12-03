
#ifndef BOOST_CONTRACT_SET_PRECONDITION_OLD_POSTCONDITION_HPP_
#define BOOST_CONTRACT_SET_PRECONDITION_OLD_POSTCONDITION_HPP_

/** @file */

#include <boost/contract/core/set_old_postcondition.hpp>
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
        class virtual_;
    }
}

namespace boost { namespace contract {
    
template<typename R = void>
class set_precondition_old_postcondition { // Copy as * (OK for RAII).
public:
    ~set_precondition_old_postcondition() BOOST_NOEXCEPT_IF(false) {}
    
    template<typename F>
    set_old_postcondition<R> precondition(F const& f) {
        BOOST_CONTRACT_AUX_DEBUG(check_);
        check_->set_pre(f);
        return set_old_postcondition<R>(check_.release());
    }

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
    explicit set_precondition_old_postcondition(check_type* check) :
            check_(check) {}
    boost::contract::aux::auto_ptr<check_type> check_;

    // Friendship used to limit library's public API.
    friend class guard;

    friend set_precondition_old_postcondition<> function();

    template<class C>
    friend set_precondition_old_postcondition<> public_function();

    template<class C>
    friend set_precondition_old_postcondition<> public_function(C*);
    
    template<class C>
    friend set_precondition_old_postcondition<> public_function(virtual_*, C*);

    template<typename R_, class C>
    friend set_precondition_old_postcondition<R_> public_function(
            virtual_*, R_&, C*);

    /* arity = 0 */
    
    template<class O, typename F, class C>
    friend set_precondition_old_postcondition<> public_function(
            virtual_*, F, C*);
    
    template<class O, typename R_, typename F, class C>
    friend set_precondition_old_postcondition<R_> public_function(
            virtual_*, R_&, F, C*);

    /* arity = 1 */
    
    template<class O, typename F, class C, typename A0>
    friend set_precondition_old_postcondition<> public_function(
            virtual_*, F, C*, A0&);

    template<class O, typename R_, typename F, class C, typename A0>
    friend set_precondition_old_postcondition<R_> public_function(
            virtual_*, R_&, F, C*, A0&);
    
    /* arity = 2 */
    
    template<class O, typename F, class C, typename A0, typename A1>
    friend set_precondition_old_postcondition<> public_function(
            virtual_*, F, C*, A0&, A1&);

    template<class O, typename R_, typename F, class C,
            typename A0, typename A1>
    friend set_precondition_old_postcondition<R_> public_function(
            virtual_*, R_&, F, C*, A0&, A1&);
};

} } // namespace

#endif // #include guard

