
#ifndef BOOST_CONTRACT_SET_PRECONDITION_POSTCONDITION_HPP_
#define BOOST_CONTRACT_SET_PRECONDITION_POSTCONDITION_HPP_

/** @file */

#include <boost/contract/core/set_precondition_only.hpp>
#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
/** @endcond */

// TODO: Read what's the best practise for namespace qualification and use it.

namespace boost {
    namespace contract {
        class virtual_;
    }
}

namespace boost { namespace contract {
    
template<typename R = void>
class set_precondition_postcondition { // Copyable as shared * (OK for RAII).
public:
    template<typename F>
    set_postcondition_only<R> precondition(F const& f) {
        check_->set_pre(f);
        return set_postcondition_only<R>(check_);
    }

    template<typename F>
    set_precondition_only postcondition(F const& f) {
        check_->set_post(f);
        return set_precondition_only(check_);
    }

private:
    typedef boost::shared_ptr<boost::contract::aux::check_pre_post<
            typename boost::contract::aux::none_if_void<R>::type> > check_ptr;

    explicit set_precondition_postcondition(check_ptr check) : check_(check) {}

    check_ptr check_;

    // Friendship used to limit library's public API.
    friend class guard;
    friend set_precondition_postcondition<> function();

    template<class C>
    friend set_precondition_postcondition<> public_function();

    template<class C>
    friend set_precondition_postcondition<> public_function(C*);
    
    template<class C>
    friend set_precondition_postcondition<> public_function(virtual_*, C*);

    template<typename R_, class C>
    friend set_precondition_postcondition<R_> public_function(
            virtual_*, R_&, C*);

    /* arity = 0 */
    
    template<class O, typename F, class C>
    friend set_precondition_postcondition<> public_function(virtual_*, F, C*);
    
    template<class O, typename R_, typename F, class C>
    friend set_precondition_postcondition<R_> public_function(
            virtual_*, R_&, F, C*);

    /* arity = 1 */
    
    template<class O, typename F, class C, typename A0>
    friend set_precondition_postcondition<> public_function(
            virtual_*, F, C*, A0&);

    template<class O, typename R_, typename F, class C, typename A0>
    friend set_precondition_postcondition<R_> public_function(
            virtual_*, R_&, F, C*, A0&);
    
    /* arity = 2 */
    
    template<class O, typename F, class C, typename A0, typename A1>
    friend set_precondition_postcondition<> public_function(
            virtual_*, F, C*, A0&, A1&);

    template<class O, typename R_, typename F, class C,
            typename A0, typename A1>
    friend set_precondition_postcondition<R_> public_function(
            virtual_*, R_&, F, C*, A0&, A1&);

    // TODO: Support configurable arity.
};

} } // namespace

#endif // #include guard

