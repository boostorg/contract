
#ifndef BOOST_CONTRACT_SET_POSTCONDITION_HPP_
#define BOOST_CONTRACT_SET_POSTCONDITION_HPP_

/** @file */

#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/core/call.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost { namespace contract {

class set_postcondition {
public:
    template<typename F>
    set_nothing postcondition(F f) {
        check_->set_post(f);
        return set_nothing(check_);
    }

private: // Friendship to minimize lib's public API.
    friend class scoped;
    friend class set_precondition_postcondition;

    template<class C>
    friend set_postcondition constructor(C const*);
    template<class C>
    friend set_postcondition constructor(boost::contract::call const&,
            C const*);

    template<class C>
    friend set_postcondition destructor(C const*);
    template<class C>
    friend set_postcondition destructor(boost::contract::call const&, C const*);

    explicit set_postcondition(boost::shared_ptr<boost::contract::aux::
            check_pre_post> check) : check_(check) {}

    boost::shared_ptr<boost::contract::aux::check_pre_post> check_;
};

} } // namespace

#endif // #include guard

