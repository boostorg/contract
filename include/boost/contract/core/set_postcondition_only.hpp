
#ifndef BOOST_CONTRACT_SET_POSTCONDITION_HPP_
#define BOOST_CONTRACT_SET_POSTCONDITION_HPP_

/** @file */

#include <boost/contract/core/set_nothing.hpp>
#include <boost/contract/core/decl.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost { namespace contract {

class set_postcondition_only {
    // Friendship used to limit lib's public API.
    friend class var;
    friend class set_precondition_postcondition;

    template<class C>
    friend set_postcondition_only constructor(C const*);

    template<class C>
    friend set_postcondition_only constructor(decl const&, C const*);

    template<class C>
    friend set_postcondition_only destructor(C const*);

    template<class C>
    friend set_postcondition_only destructor(decl const&, C const*);

public:
    template<typename F>
    set_nothing postcondition(F const& f) {
        check_->set_post(f);
        return set_nothing(check_);
    }

private:
    explicit set_postcondition_only(boost::shared_ptr<
            boost::contract::aux::check_pre_post> check) : check_(check) {}

    // TODO: Can I use unique_ptr or some other smart ptr with less overhead
    // than shared_ptr for old values, here, and everywhere?
    boost::shared_ptr<boost::contract::aux::check_pre_post> check_;
};

} } // namespace

#endif // #include guard

