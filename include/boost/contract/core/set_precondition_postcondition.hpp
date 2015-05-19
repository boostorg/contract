
#ifndef BOOST_CONTRACT_SET_PRECONDITION_POSTCONDITION_HPP_
#define BOOST_CONTRACT_SET_PRECONDITION_POSTCONDITION_HPP_

/** @file */

#include <boost/contract/core/set_precondition_only.hpp>
#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/core/decl.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost { namespace contract {
    
// TODO: Read what's the best practise for namespace qualification...
// I can even write an example to test if concize namespace qualification
// gives problem when same func/class/typedef/etc in different namespaces.
// If so, I must always fully qualify...

class set_precondition_postcondition {
public:
    template<typename F>
    set_postcondition_only precondition(F const& f) {
        check_->set_pre(f);
        return set_postcondition_only(check_);
    }

    template<typename F>
    set_precondition_only postcondition(F const& f) {
        check_->set_post(f);
        return set_precondition_only(check_);
    }

private:
    explicit set_precondition_postcondition(boost::shared_ptr<
            boost::contract::aux::check_pre_post> check) : check_(check) {}

    boost::shared_ptr<boost::contract::aux::check_pre_post> check_;
    
    // Friendship used to limit lib's public API.

    friend class var;

    template<class C>
    friend set_precondition_postcondition public_member(decl const&, C const*);
    
    template<class, class C, typename A0>
    friend set_precondition_postcondition public_member(C const*, A0 const&);

    template<class, class C, typename A0>
    friend set_precondition_postcondition public_member(decl const&, C const*,
            A0 const&);
    
    friend set_precondition_postcondition protected_member();
    friend set_precondition_postcondition protected_member(decl const&);
    
    friend set_precondition_postcondition private_member();
    friend set_precondition_postcondition private_member(decl const&);
    
    friend set_precondition_postcondition free_function();
    friend set_precondition_postcondition free_function(decl const&);
};

} } // namespace

#endif // #include guard

