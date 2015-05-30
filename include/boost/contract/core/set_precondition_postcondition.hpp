
#ifndef BOOST_CONTRACT_SET_PRECONDITION_POSTCONDITION_HPP_
#define BOOST_CONTRACT_SET_PRECONDITION_POSTCONDITION_HPP_

/** @file */

#include <boost/contract/core/set_precondition_only.hpp>
#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
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
    
template<typename R>
class set_precondition_postcondition {
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
    explicit set_precondition_postcondition(boost::shared_ptr<
            boost::contract::aux::check_pre_post<R> > check) : check_(check) {}

    boost::shared_ptr<boost::contract::aux::check_pre_post<R> > check_;

    // Friendship used to limit library's public API.
    friend class scoped;

    template<typename R_, class C>
    friend set_precondition_postcondition<R_> public_member(virtual_*, R_&, C*);
    template<class O, typename R_, typename F, class C, typename A0>
    friend set_precondition_postcondition<R_> public_member(
            virtual_*, R_&, F, C*, A0&);
    // TODO: Support configurable arity.
};

} } // namespace

#endif // #include guard

