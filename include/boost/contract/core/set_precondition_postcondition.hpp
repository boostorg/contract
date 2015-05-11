
#ifndef BOOST_CONTRACT_SET_PRECONDITION_POSTCONDITION_HPP_
#define BOOST_CONTRACT_SET_PRECONDITION_POSTCONDITION_HPP_

#include <boost/contract/core/set_precondition.hpp>
#include <boost/contract/core/set_postcondition.hpp>
#include <boost/contract/core/call.hpp>
#include <boost/contract/aux_/condition/check_pre_post.hpp>
#include <boost/shared_ptr.hpp>

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

    friend set_precondition_postcondition free_function(
            boost::contract::call const&);
    friend set_precondition_postcondition free_function();

    template<class C>
    friend set_precondition_postcondition public_member(
            boost::contract::call const&, C const*);
    
    explicit set_precondition_postcondition(boost::shared_ptr<boost::contract::
            aux::check_pre_post> check) : check_(check) {}

    boost::shared_ptr<boost::contract::aux::check_pre_post> check_;
};

} } // namespace

#endif // #include guard

