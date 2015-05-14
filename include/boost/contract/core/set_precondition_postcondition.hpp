
#ifndef BOOST_CONTRACT_SET_PRECONDITION_POSTCONDITION_HPP_
#define BOOST_CONTRACT_SET_PRECONDITION_POSTCONDITION_HPP_

/** @file */

#include <boost/contract/core/set_precondition.hpp>
#include <boost/contract/core/set_postcondition.hpp>
#include <boost/contract/core/call.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost { namespace contract {

class set_precondition_postcondition {
public:
    template<typename F>
    boost::contract::set_postcondition precondition(F f) {
        check_->set_pre(f);
        return boost::contract::set_postcondition(check_);
    }

    template<typename F>
    boost::contract::set_precondition postcondition(F f) {
        check_->set_post(f);
        return boost::contract::set_precondition(check_);
    }

private: // Friendship to minimize lib's public API.
    friend class scoped;

    // TODO: Read what's the best practise for namespace qualification...

    template<class I, class C, typename A0>
    friend set_precondition_postcondition public_member(C const*, A0 const&);
    template<class C>
    friend set_precondition_postcondition public_member(
            boost::contract::call const&, C const*);
    
    friend set_precondition_postcondition protected_member();
    friend set_precondition_postcondition protected_member(
            boost::contract::call const&);
    
    friend set_precondition_postcondition private_member();
    friend set_precondition_postcondition private_member(
            boost::contract::call const&);
    
    friend set_precondition_postcondition free_function();
    friend set_precondition_postcondition free_function(
            boost::contract::call const&);
    
    explicit set_precondition_postcondition(boost::shared_ptr<boost::contract::
            aux::check_pre_post> check) : check_(check) {}

    boost::shared_ptr<boost::contract::aux::check_pre_post> check_;
};

} } // namespace

#endif // #include guard

